#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../Socket.hpp"

class Client
{
private:
	Socket clientSocket;
public:
	Client(/* args */);
	~Client();
	void connectToServer();
	void sendData();
	void receiveData();
	void disconnectFromServer();
};
#endif