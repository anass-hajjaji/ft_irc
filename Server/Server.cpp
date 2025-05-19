#include "../include/Server.hpp"

std::vector<pollfd> Server::_pfds;

Server::Server():_name("default"),_password("defaut"),_port(8080)
{}

Server::Server(std::string name, std::string password, unsigned short port):_name(name), _password(password), _port(port)
{
}

Server::~Server()
{
}

void Server::setupServer()
{
	struct pollfd pfd;
	int opt = 1;
	int ret;


	_serverSocket = Socket();
	_serverSocket.setSocketAdress(AF_INET, _port, INADDR_ANY);
	ret = setsockopt(_serverSocket.getSocketFd(), SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	if (ret < 0)
		throw std::runtime_error("failed to set options for server socket!");
	ret = bind(_serverSocket.getSocketFd(), (struct sockaddr*)&_serverSocket.getSocketAddress(), sizeof(_serverSocket.getSocketAddress()));
	if (ret < 0)
		throw std::runtime_error("failed to bind the server socket to a local address!");
	_serverSocket.setIpAddress(inet_ntoa(_serverSocket.getSocketAddress().sin_addr));
	startListening();
	pfd.fd = _serverSocket.getSocketFd();
	pfd.events = POLL_IN;
	_pfds.push_back(pfd);
}

void Server::initServer()
{
	int ret;

	setupServer();
	while (true)
	{
		ret = poll(_pfds.data(), _pfds.size(), -1);
		if (!ret)
			throw std::runtime_error("Timeout for poll, no file descriptors have been selected!");
		if (ret < 0)
			throw std::runtime_error("Poll system call has failed!");
		if (_pfds[0].revents & POLL_IN)
		{
			acceptConnection();
		}
		for (size_t i = 1; i < _pfds.size(); i++)
		{
			if (_pfds[i].revents & POLL_IN)
				receiveData(i);
		}
	}
}

void Server::startListening()
{
	int ret;

	ret = listen(_serverSocket.getSocketFd(), MAX_CONNECTIONS);
	if (ret < 0)
		throw std::runtime_error("failed to listen for connections!");
	std::cout << "Server is listening on " << _serverSocket.getIpAddress() << ":"  << _port << std::endl;
}

void Server::receiveData(int i)
{
	ssize_t bytes;
	std::memset(_buffer, 0, sizeof(_buffer));
	bytes = recv(_pfds[i].fd, _buffer, sizeof(_buffer), 0);
	if (!bytes)
	{
		std::cout << "client has gracefully closed the connection" << std::endl;
		close(_pfds[i].fd);
		_pfds.erase(_pfds.begin() + i);
	}
	if (bytes < 0)
		throw std::runtime_error("failed to receive a new message!");
	std::cout << "received the message: " << _buffer;
}

Socket &Server::getServerSocket()
{
	return this->_serverSocket;
}

void Server::acceptConnection()
{
	int fd;
	struct pollfd pfd;

	Socket c(1);
	socklen_t len = sizeof(c.getSocketAddress());
	fd = accept(_serverSocket.getSocketFd(), (sockaddr *)&c.getSocketAddress(), &len);
	if (fd < 0)
		throw std::runtime_error("failed to accept a new connection!");
	c.setSocketFd(fd);
	if (fcntl(fd, F_SETFL, O_NONBLOCK) < 0)
		throw std::runtime_error("failed to make a file non-blocking");
	c.setIpAddress(inet_ntoa(c.getSocketAddress().sin_addr));
	Client newClient(c);
	_allClients.push_back(newClient);

	pfd.fd = fd;
	pfd.events = POLL_IN;
	pfd.revents = 0;
	_pfds.push_back(pfd);
	std::cout << "new client is connected on host: "  << c.getIpAddress() << std::endl;
}

void Server::quitServer()
{
	std::cout << "closing all connections" << std::endl;
	for (std::vector<struct pollfd>::iterator p = _pfds.begin(); p != _pfds.end(); p++)
	{
		close(p->fd);
	}
	exit(-1);
}

void signalHander(int sig)
{
	(void)sig;
	Server::quitServer();
}
