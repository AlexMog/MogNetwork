//
// ServerListener.hh for serverListener in 
// 
// Made by Moghrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Mon May 19 22:28:45 2014 Moghrabi Alexandre
// Last update Mon May 19 22:30:04 2014 Moghrabi Alexandre
//

#ifndef SERVERLISTENER_HH_
# define SERVERLISTENER_HH_

# include <mog-network/IServerListener.hh>

class ServerListener : public IServerListener
{
public:
  ServerListener();
  ~ServerListener();

public:
  void onOrder(Packet& packet);
};

#endif /* !SERVERLISTENER_HH_ */
