#ifndef SERVERCLIENT_HH_
#define SERVERCLIENT_HH_

#include <iostream>
#include <string>
#include <vector>

#include "Packet.hh"

class Server;

class ServerClient
{
public:
  ServerClient(int socket, Server *server);
  ~ServerClient();
  int getSocket() const;
  bool sendPacket(const Packet& packet);
  bool sendSize(const void* data, unsigned int size);
  bool readSize(unsigned int size, char *buffer, unsigned int&);
  bool readPacket(Packet& packet);
  void disconnect();

private:
  int _socket;
  Server *_server;
  struct WaitingPacket
  {
    WaitingPacket();
    unsigned int size;
    unsigned int received;
    std::vector<char> data;
  };
  WaitingPacket _waitingPacket;
};

#endif
