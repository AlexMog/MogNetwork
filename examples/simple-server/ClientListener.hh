//
// ClientListener.hh for ClientListener in 
// 
// Made by Moghrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Mon May 19 22:14:59 2014 Moghrabi Alexandre
// Last update Mon May 19 22:17:06 2014 Moghrabi Alexandre
//

#ifndef CLIENTLISTENER_HH_
# define CLIENTLISTENER_HH_

# include <mog-network/IClientListener.hh>

class ClientListener : public IClientListener
{
public:
  ClientListener();
  ~ClientListener();

public:
  void onOrder(ServerClient& client, Packet& packet);
  void onDisconnect(ServerClient& client);
  void onOpen(ServerClient& client);
};

#endif /* !CLIENTLISTENER_HH_ */
