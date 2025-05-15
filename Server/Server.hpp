#ifndef SERVER_HPP
#define SERVER_HPP

#include  "../Socket.hpp"
#include <string>
#include <vector>
#include <iostream>

class Server
{
private:
	unsigned short port;
	Socket serverSocket;
	std::vector<Socket> allClients;
	char	buffer[BUFFER_SIZE];
public:
	Server(unsigned short port);
	~Server();
	void initServer();
	void startListening();
	void acceptConnections();
	void disconnectUser(int fd);
	void receiveData();
	void sendData();
	void quitServer();
};

#endif