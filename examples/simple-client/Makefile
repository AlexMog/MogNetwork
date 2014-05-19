NAME=		client

SRC=		main.cpp		\
		ServerListener.cpp

OBJ=		$(SRC:.cpp=.o)

RM=		rm -f

CC=		g++

CXXFLAGS=	-W -Wall -Wextra -g3

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) -lmog-network

all:		$(NAME);

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean $(NAME)
