#ifndef SERVER_HH_
#define SERVER_HH_

#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <list>
#include "ServerClient.hh"
#include "IClientListener.hh"
#include "Packet.hh"

class Server
{
public:
  Server(int port);
  ~Server();

public:
  std::list<ServerClient>& getClients();

public:
  void sendPacketToClient(ServerClient& client, const Packet& packet);
  void sendPacketToAllClients(const Packet& packet);
  void init();
  void start();
  void close();

public:
  void setClientListener(IClientListener *clientListener);

private:
  int addClient(int *socket);
  void interpreteClient(ServerClient& client);
  void interpreteOrder(Packet& packet, ServerClient& client);

private:
  int _ServerSocket;
  std::list<ServerClient> _clients;
  int _port;
  IClientListener *_clientListener;
};

#endif
