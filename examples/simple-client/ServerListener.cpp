//
// ServerListener.cpp for Client in 
// 
// Made by Moghrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Mon May 19 22:30:14 2014 Moghrabi Alexandre
// Last update Mon May 19 22:31:19 2014 Moghrabi Alexandre
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
