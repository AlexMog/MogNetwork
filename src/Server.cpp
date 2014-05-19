#include <iostream>
#include <list>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include "Server.hh"
#include "ServerClient.hh"
#include "ServerException.hh"

Server::Server(int port)
{
  _port = port;
  _clientListener = NULL;
}

Server::~Server()
{
  
}

void Server::init()
{
  struct sockaddr_in sin;
  int y = 1;

  _ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
  memset(&sin, 0, sizeof(sin));
  std::cout << "Creation de la socket..." << std::endl;
  if(_ServerSocket == -1)
    throw ServerException("Socket: ");

  /* Set the REUSEADDR Option */
  if (setsockopt(_ServerSocket, SOL_SOCKET, SO_REUSEADDR, &y, sizeof(int)) == -1)
    throw ServerException("Setsockopt: ");

  sin.sin_addr.s_addr = htonl(INADDR_ANY);
  sin.sin_port = htons(_port);
  sin.sin_family = AF_INET;
  std::cout << "Bindage de la socket..." << std::endl;
  if(bind(_ServerSocket,(struct sockaddr *) &sin, sizeof(sin)) == -1)
    throw ServerException("Bind: ");
  std::cout << "Listen sur la socket..." << std::endl;
  if(listen(_ServerSocket, 42) == -1)
    throw ServerException("Listen: ");
}

void Server::start()
{
  fd_set rdfs;
  int max = _ServerSocket;

  std::cout << "Serveur lancé!" << std::endl;
  while (true)
    {
      FD_ZERO(&rdfs);
      FD_SET(STDIN_FILENO, &rdfs);

      FD_SET(_ServerSocket, &rdfs);
      for (std::list<ServerClient>::iterator it = _clients.begin();
	   it != _clients.end(); ++it)
	FD_SET(it->getSocket(), &rdfs);
      
      if (select(max + 1, &rdfs, NULL, NULL, NULL) == -1)
	throw ServerException("Select: ");

      if (FD_ISSET(STDIN_FILENO, &rdfs))
	break;
      else if (FD_ISSET(_ServerSocket, &rdfs))
	{
	  int csock;
	  if (addClient(&csock) != -1)
	    {
	      max = (csock > max ? csock : max);
	      FD_SET(csock, &rdfs);
	    }
	  else
	    ::close(csock);
	}
      else
	{
	  for (std::list<ServerClient>::iterator it = _clients.begin();
	       it != _clients.end(); ++it)
	    if (FD_ISSET(it->getSocket(), &rdfs)) {
	      interpreteClient(*it);
	      break;
	    }
	}
    }
}

void Server::interpreteClient(ServerClient &client)
{
  Packet packet;

  /* déco */
  if (client.readPacket(packet))
    {
      if (_clientListener != NULL)
	_clientListener->onDisconnect(client);
      client.disconnect();
    }
  else
    interpreteOrder(packet, client);
}

void Server::interpreteOrder(Packet &packet, ServerClient &client)
{
  if (_clientListener != NULL)
    _clientListener->onOrder(client, packet);
}

int Server::addClient(int *csock)
{
  sockaddr_in csin;
  memset(&csin, 0, sizeof(csin));
  socklen_t sinsize = sizeof(csin);

  *csock = accept(_ServerSocket, (sockaddr *)&csin, &sinsize);
  if (*csock == -1)
    {
      std::cerr << "Error while connecting with a client." << std::endl;
      return (-1);
    }

  ServerClient client(*csock, this);
  if (_clientListener != NULL)
    _clientListener->onOpen(client);
  _clients.push_front(client);
  
  return (0);
}

void Server::close()
{
  std::list<ServerClient>::iterator it;
  for (it = _clients.begin();
       it != _clients.end(); ++it) {
    ::close(it->getSocket());
  }
  ::close(_ServerSocket);
}

void Server::sendPacketToAllClients(const Packet& packet)
{
  for (std::list<ServerClient>::iterator it = _clients.begin();
       it != _clients.end(); ++it)
    it->sendPacket(packet);
}

void Server::sendPacketToClient(ServerClient& client, const Packet& packet)
{
  client.sendPacket(packet);
}

std::list<ServerClient> &Server::getClients()
{
  return (_clients);
}

void Server::setClientListener(IClientListener *clientListener)
{
  _clientListener = clientListener;
}
