#include "Server.hpp"

//CHECK FOR FAILURES

Server::Server(unsigned short port):port(port)
{
	initServer();
}

Server::~Server()
{}

void Server::initServer()
{
	serverSocket = Socket();
	serverSocket.setSocketAdress(AF_INET, port, INADDR_ANY);
	bind(serverSocket.getSocketFd(), (struct sockaddr*)&serverSocket.getSocketAddress(), sizeof(serverSocket.getSocketAddress()));
	startListening();
}

void Server::startListening()
{
	listen(serverSocket.getSocketFd(), 5);
	std::cout << "Server listening on port " << port << std::endl;
}