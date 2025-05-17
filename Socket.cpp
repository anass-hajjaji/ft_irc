#include "Socket.hpp"

Socket::Socket()
{
	socketFd = socket(AF_INET, SOCK_STREAM, 0);
	//implement error handling;
}

Socket::Socket(int type)
{
	if (!type)
		socketFd =  socket(AF_INET, SOCK_STREAM, 0);
}

Socket::~Socket(){}

int	Socket::getSocketFd()
{
	return this->socketFd;
}

void Socket::closeSocket()
{
	close(this->socketFd);
}

void Socket::setSocketFd(int fd)
{
	this->socketFd = fd;
}

struct sockaddr_in &Socket::getSocketAddress()
{
	return this->socketAdress;
}

void Socket::setSocketAdress(sa_family_t family, in_port_t &port, u_int32_t addr)
{
	this->socketAdress.sin_family = family;
	this->socketAdress.sin_port = htons(port);
	this->socketAdress.sin_addr.s_addr = addr;
}

void Socket::setHostName(std::string hostName)
{
	this->hostName = hostName;
}

std::string Socket::getHostName()
{
	return this->hostName;
}