srcs = 
objs = ${srcs:.cpp=.o} 
cc = c++
flags = -Werror -Wall -Warning -std=98
header = 
name = 

%.o : %.cpp
	${cc} ${flags} -c $< -o $@

${name} : all

all : ${header}
	${cc} ${flags} ${objs} -o ${name}

clean:
	rm ${objs}

fclean: clean
	rm ${name}

re: fclean all