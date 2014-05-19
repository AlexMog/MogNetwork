#ifndef CLIENT_HH_
#define CLIENT_HH_

#include <iostream>
#include <string>
#include <vector>
#include "Packet.hh"
#include "IServerListener.hh"
#include "ClientException.hh"

class Client
{
public:
  Client(const std::string& ip, int port);
  ~Client();

public:
  bool sendSize(const void* data, std::size_t size);
  bool sendPacket(const Packet& packet);
  bool readSize(std::size_t size, void* buffer, std::size_t& recived);
  bool readPacket(Packet& packet);
  void init();
  void disconnect();
  void start();
  void interpretePacket(Packet& packet);
  void setServerListener(IServerListener* serverListener);

private:
  int _socket;
  std::string _ip;
  int _port;
  IServerListener* _serverListener;
  bool _disconnected;
  struct WaitingPacket
  {
    WaitingPacket();
    uint32_t		size;
    std::size_t		received;
    std::vector<char>	data;
  };
  WaitingPacket _waitingPacket;
};

#endif
