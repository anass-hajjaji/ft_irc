#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../Socket.hpp"

class Client
{
private:
	Socket	clientSocket;
public:
	Client();
	Client(Socket clientSocket);
	~Client();
	void disconnectFromServer();;
};
#endif