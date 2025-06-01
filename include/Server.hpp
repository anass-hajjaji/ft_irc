#ifndef SERVER_HPP
#define SERVER_HPP

#include  "Socket.hpp"
#include "Client.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include <string>
#include <poll.h>
#include <fcntl.h>
#include <signal.h>

#include <cstdlib>

#define MAX_CONNECTIONS 5


class Server
{
private:
	std::string							_name;
	std::string							_password;
	unsigned short						_port;
	Socket								_serverSocket;
	std::vector<Client>					_allClients;
	static std::vector<struct pollfd>	_pfds;
	char								_buffer[BUFFER_SIZE];
public:
	Server();
	Server(std::string name, std::string password, unsigned short port);
	~Server();
	void								initServer();
	void								setupServer();
	void								startListening();
	void								acceptConnection();
	void								disconnectUser(int fd);
	void								receiveData(int fd);
	void								sendData();
	static void 						quitServer();
	Socket								&getServerSocket();
	std::string 						getName();
	std::string 						getPassword();
	unsigned short						getPort();
	std::vector<Client> 				getAllClients();
	static std::vector<struct pollfd>	getPfds();
	char								*getBuffer();
	Client								*getClientByFd(int fd);
	Client								*getClientByNickName(std::string nickName);
	// void SendPrivMsg_User(const std::string &target_name, const std::string &message, Client *c);

	// anass
	// void 
	// static void commands(std::vector<std::string> &params, Client *c);
	void commands(std::vector<std::string> &params, Client *c);
	void parseMessage(char *buf, Client *c);
	void parseParams(std::vector<std::string> &params, Client *c);
	void SendPrivMsg_User(const std::string &target_name, const std::string &message, Client *c);


};

int	identify_Command(std::string cmd);
void handleNickNameCommand(std::vector<std::string> &params, Client *c);
void handleUserCommand(std::vector<std::string> &params, Client *c);
void handlePassCommand(std::vector<std::string> &params, Client *c);
std::string extractMessage(std::string m);
void signalHander(int sig);
//anass
#endif