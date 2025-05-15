#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../Socket.hpp"

class Client
{
private:
	Socket	clientSocket;
	char	buffer[BUFFER_SIZE];
public:
	Client(Socket server);
	~Client();
	void connectToServer(Socket server);
	void sendData();
	void receiveData();
	void disconnectFromServer();
};
#endif