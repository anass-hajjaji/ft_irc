#include "../include/Client.hpp"

Client::Client()
{
	_clientSocket = Socket(1);
}

Client::Client(Socket socket):_clientSocket(socket)
{
	
}

Client::~Client()
{}

void Client::disconnectFromServer()
{
	_clientSocket.closeSocket();
}


Socket &Client::getClientSocket()
{
	return this->_clientSocket;
}

void Client::setClientSocket(Socket	&clientSocket)
{
	this->_clientSocket = clientSocket;
}
