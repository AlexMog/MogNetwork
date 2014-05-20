BINDIR=		bin/

LIBNAME=	mog-network

NAME=		lib$(LIBNAME).so

SRCDIR=		src/

INCNAME=	$(LIBNAME)

INCDIR=		/usr/include/

LIBDIR=		/usr/lib/

SRC=		$(SRCDIR)Server.cpp		\
		$(SRCDIR)ServerClient.cpp	\
		$(SRCDIR)ServerException.cpp	\
		$(SRCDIR)Packet.cpp		\
		$(SRCDIR)Thread.cpp		\
		$(SRCDIR)Client.cpp		\
		$(SRCDIR)ClientException.cpp

OBJ=		$(SRC:.cpp=.o)

RM=		rm -f

CC=		g++

CP=		cp

CXXFLAGS=	-W -Wall -Wextra -I./include/ -fPIC

all:		$(NAME)

$(NAME):	$(OBJ)
		mkdir -p bin
		$(CC) --shared -o $(BINDIR)$(NAME) $(OBJ) -pthread

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(BINDIR)$(NAME)

install:
		$(CP) $(BINDIR)$(NAME) $(LIBDIR)
		mkdir -p $(INCDIR)$(LIBNAME)
		$(CP) ./include/* $(INCDIR)$(LIBNAME)/

uninstall:
		$(RM) $(LIBDIR)$(NAME)
		$(RM) -r $(INCDIR)$(INCNAME)

re:		fclean $(NAME)
