#include "include/Client.hpp"
#include "include/Server.hpp"
#include <cstdlib> // Add this line

int main(int argc, char **argv)
{
	unsigned short port;
	if (argc != 3)
	{
		std::cerr << "insuficiant number of args" << std::endl;
		_exit(1);
	}
	std::string password(argv[2]);
	port = std::atoi(argv[1]);

	signal(SIGINT, signalHander);
	Server s("test", password, port);

	try
	{
		s.initServer();
	}
	catch (std::exception &e)
	{
		std::cout << "error: " << e.what() << std::endl;
	}
	s.quitServer();
}
