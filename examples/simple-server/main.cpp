/*
** main.c for simple-server in 
** 
** Made by Moghrabi Alexandre
** Login   <alexmog@epitech.net>
** 
** Started on  Mon May 19 22:10:43 2014 Moghrabi Alexandre
// Last update Mon May 19 22:23:23 2014 Moghrabi Alexandre
*/

#include <exception>
#include <mog-network/Server.hh>
#include "ClientListener.hh"

int main()
{
  int ret = 0;
  // 4242 is the port that we are going to use.
  Server server(4242);
  ClientListener clientListener;

  server.setClientListener(&clientListener);
  try {
    server.init();
    server.start();
    server.close();
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    ret = 1;
  }
  return (ret);
}
