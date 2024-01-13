NAME	=		pmerge
CXX		=		c++	
CXXFLAG	=		-g -fsanitize=address -Wall -Wextra -Werror
SRCS	=		${shell find . -name "*.cpp"}


${NAME}:
	${CXX} ${CXXFLAG} ${SRCS} -o ${NAME}

fclean:
	rm -f ${NAME}	

re: fclean ${NAME}



