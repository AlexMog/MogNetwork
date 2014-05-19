//
// IActionObject.hh for TCP in /home/alexmog/projets/cpp_server_client_class/TCP_version/server
// 
// Made by Moghrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Fri Apr  4 17:52:24 2014 Moghrabi Alexandre
// Last update Mon May 19 19:43:34 2014 Moghrabi Alexandre
//

#ifndef ICLIENTLISTENER_HH_
# define ICLIENTLISTENER_HH_

# include "Packet.hh"
# include "ServerClient.hh"

class IClientListener
{
public:
  virtual ~IClientListener() {}

public:
  virtual void onOrder(ServerClient& client, Packet& packet) = 0;
  virtual void onDisconnect(ServerClient& client) = 0;
  virtual void onOpen(ServerClient& client) = 0;
  
};

#endif // !CLIENTLISTENER_HH_
