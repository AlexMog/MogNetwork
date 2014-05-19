//
// main.cpp for main in 
// 
// Made by Moghrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Mon May 19 22:25:42 2014 Moghrabi Alexandre
// Last update Mon May 19 22:32:23 2014 Moghrabi Alexandre
//

#include <exception>
#include <mog-network/Client.hh>
#include "ServerListener.hh"

int main()
{
  int ret = 0;
  // Connect to localhost:4242
  Client client("localhost", 4242);
  ServerListener serverListener;
  Packet packet;

  client.setServerListener(&serverListener);

  try {
    packet << "Hello world!";
    client.init();
    client.sendPacket(packet);
    client.start();
    client.disconnect();
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    ret = 1;
  }
  return (ret);
}
