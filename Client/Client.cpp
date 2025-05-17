#include "Client.hpp"

Client::Client()
{
	clientSocket = Socket(1);
}

Client::Client(Socket socket):clientSocket(socket)
{
	
}

Client::~Client()
{}

void Client::disconnectFromServer()
{
	clientSocket.closeSocket();
}

