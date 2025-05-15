#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#define BUFFER_SIZE  1024
class Socket
{
	private:
		int socketFd;
		struct sockaddr_in socketAdress;
	public:
		Socket();
		~Socket();
		int	getSocketFd();
		struct sockaddr_in getSocketAddress();
		void closeSocket();
		void setSocketAdress(sa_family_t family, in_port_t &port, u_int32_t addr);
};

#endif