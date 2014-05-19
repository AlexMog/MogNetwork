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
  bool readSize(std::size_t size, char *buffer, std::size_t&);
  bool readPacket(Packet& packet);
  void disconnect();

private:
  int _socket;
  Server *_server;
  struct WaitingPacket
  {
    WaitingPacket();
    std::size_t size;
    std::size_t received;
    std::vector<char> data;
  };
  WaitingPacket _waitingPacket;
};

#endif
