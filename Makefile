srcs = main.cpp Server/Server.cpp Client/Client.cpp Socket.cpp
objs = $(srcs:.cpp=.o)
cc = c++
flags = -Werror -Wall -Wextra -std=c++98
header = Server/Server.hpp Client/Client.hpp Socket.hpp
name = irc

%.o : %.cpp
	${cc} $(flags) -c $< -o $@

all : ${name}

${name} : ${objs} ${header}
	${cc} ${flags} ${objs} -o ${name}

clean:
	rm -f ${objs}

fclean: clean
	rm -f ${name}

re: fclean all
