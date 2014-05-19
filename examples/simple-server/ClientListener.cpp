//
// ClientListener.cpp for ClientListener in 
// 
// Made by Moghrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Mon May 19 22:17:43 2014 Moghrabi Alexandre
// Last update Mon May 19 22:20:58 2014 Moghrabi Alexandre
//

#include "ClientListener.hh"

ClientListener::ClientListener() {}

ClientListener::~ClientListener() {}

// Called when a client sends something
void ClientListener::onOrder(ServerClient& client, Packet& packet)
{
  char datas[1024];

  // Getting the datas
  packet >> datas;
  std::cout << "Received: " << datas << std::endl;
}

// Called when a client disconnects
void ClientListener::onDisconnect(ServerClient& client)
{
  std::cout << "Client disconnected." << std::endl;
}

// Called when a client connects
void ClientListener::onOpen(ServerClient& client)
{
  std::cout << "New client connected!" << std::endl;
}
