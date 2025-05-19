#include "../include/Client.hpp"

Client::Client()
{
	_clientSocket = Socket(1);
}

Client::Client(Socket socket):_clientSocket(socket), _isAuthenticated(false)
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

std::string Client::getNickName() const
{
	return this->_nickName;
}

std::string Client::getUserName() const
{
	return this->_username;
}

std::string Client::getRealName() const
{
	return this->_realName;
}

void Client::setNickName(std::string &value)
{
	_nickName = value;
}

void Client::setUserName(std::string &value)
{
	_username = value;
}

void Client::setRealName(std::string &value)
{
	_realName = value;
}

void Client::setPassword(std::string &value)
{
	_password = value;
}