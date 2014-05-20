//
// ServerListener.cpp for Client in 
// 
// Made by Moghrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Mon May 19 22:30:14 2014 Moghrabi Alexandre
// Last update Tue May 20 13:26:27 2014 Moghrabi Alexandre
//

#include "ServerListener.hh"

ServerListener::ServerListener() {}

ServerListener::~ServerListener() {}

void ServerListener::onOrder(Packet& packet)
{
  char datas[1024];

  packet >> datas;
  std::cout << datas << std::endl;
}

void ServerListener::onDisconnect()
{
  std::cout << "Disconnected by the server." << std::endl;
}
