#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Socket.hpp"

class Client
{
private:
	Socket		_clientSocket;
	std::string _nickName;
	std::string _username;
	std::string _realName;
	std::string	_password;
public:
	Client();
	Client(Socket _clientSocket);
	~Client();
	void		disconnectFromServer();
	Socket		&getClientSocket();
	std::string &getNickName() const;
	std::string &getUserName() const;
	std::string &getRealName() const;
	std::string	&getPassword() const;
	void		setPassword(std::string &value);
	void		setNickName(std::string &value);
	void		setRealName(std::string &value);
	void		setUserName(std::string &value);
	void		setClientSocket(Socket	&clientSocket);
};
#endif