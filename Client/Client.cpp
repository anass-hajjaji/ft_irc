#include "Client.hpp"

Client::Client(Socket server)
{
	clientSocket = Socket();
	connectToServer(server);
}

Client::~Client()
{}

void Client::connectToServer(Socket server)
{
	connect(server.getSocketFd(), (struct sockaddr*)&server.getSocketAddress(), sizeof(server.getSocketAddress()));
}

void Client::disconnectFromServer()
{
	clientSocket.closeSocket();
}