#include "Server.hpp"

//CHECK FOR FAILURES

Server::Server(std::string name, std::string password, unsigned short port):name(name), password(password), port(port)
{
}

Server::~Server()
{
}

void Server::setupServer()
{
	struct pollfd pfd;
	int opt = 1;
	
	serverSocket = Socket();
	serverSocket.setSocketAdress(AF_INET, port, INADDR_ANY);
	setsockopt(serverSocket.getSocketFd(),SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
	bind(serverSocket.getSocketFd(), (struct sockaddr*)&serverSocket.getSocketAddress(), sizeof(serverSocket.getSocketAddress()));
	serverSocket.setHostName(inet_ntoa(serverSocket.getSocketAddress().sin_addr));
	startListening();
	pfd.fd = serverSocket.getSocketFd();
	pfd.events = POLL_IN;
	pfds.push_back(pfd);
}

void Server::initServer()
{
	setupServer();
	while (true)
	{
		poll(pfds.data(), pfds.size(), -1);
		if (pfds[0].revents & POLL_IN)
		{
			acceptConnection();
		}
		for (size_t i = 1; i < pfds.size(); i++)
		{
			if (pfds[i].revents & POLL_IN)
			{
				std::memset(buffer, 0, sizeof(buffer));
				recv(pfds[i].fd, buffer, sizeof(buffer), 0);
				std::cout << "received the message: " << buffer << std::endl;
				send(pfds[i].fd, buffer, sizeof(buffer), 0);
			}
		}
	}
}

void Server::startListening()
{
	listen(serverSocket.getSocketFd(), MAX_CONNECTIONS);
	std::cout << "Server listening on " << serverSocket.getHostName() << ":"  << port << std::endl;
}

Socket &Server::getServerSocket()
{
	return this->serverSocket;
}

void Server::acceptConnection()
{
	int fd;

	Socket c(1);
	fd = accept(serverSocket.getSocketFd(), (sockaddr *)&c.getSocketAddress(), (socklen_t *)sizeof(c.getSocketAddress()));
	c.setSocketFd(fd);
	fcntl(fd, F_SETFL, O_NONBLOCK);
	
	Client newClient(c);
	allClients.push_back(newClient);

	pfds[pfds.size()].fd = fd;
	pfds[pfds.size()].events = POLL_IN;
	std::cout << "new client is connected on host: "  << inet_ntoa(c.getSocketAddress().sin_addr) << std::endl;
}

void Server::quitServer()
{
	for (std::vector<struct pollfd>::iterator p = pfds.begin(); p != pfds.end(); p++)
	{
		close(p->fd);
	}
}
