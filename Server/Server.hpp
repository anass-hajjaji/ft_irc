#ifndef SERVER_HPP
#define SERVER_HPP

#include  "../Socket.hpp"
#include "../Client/Client.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include <poll.h>
#include <fcntl.h>
#define PASSWORD "test"
#define MAX_CONNECTIONS 5

class Server
{
private:
	std::string name;
	std::string password;
	unsigned short port;
	Socket serverSocket;
	std::vector<Client> allClients;
	std::vector<struct pollfd> pfds;
	char	buffer[BUFFER_SIZE];
public:
	Server(std::string name, std::string password, unsigned short port);
	~Server();
	void initServer();
	void setupServer();
	void startListening();
	void acceptConnection();
	void disconnectUser(int fd);
	void receiveData();
	void sendData();
	void quitServer();
	Socket &getServerSocket();
};

#endif