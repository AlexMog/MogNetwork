//
// IActionObject.hh for TCP in /home/alexmog/projets/cpp_server_client_class/TCP_version/server
// 
// Made by Moghrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Fri Apr  4 17:52:24 2014 Moghrabi Alexandre
// Last update Sun Apr  6 18:00:01 2014 Moghrabi Alexandre
//

#ifndef ISERVERLISTENER_HH_
# define ISERVERLISTENER_HH_

# include "Packet.hh"

class IServerListener
{
public:
  virtual ~IServerListener() {}

public:
  virtual void onOrder(Packet& packet) = 0;
  
};

#endif // !IACTIONOBJECT_HH_
