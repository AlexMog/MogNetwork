//
// ServerException.cpp for server in /home/alexmog/projets/cpp_server_client_class/TCP_version/server
// 
// Made by Moghrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Fri Apr  4 19:54:59 2014 Moghrabi Alexandre
// Last update Mon May 19 21:08:12 2014 Moghrabi Alexandre
//

#include <string>
#include <errno.h>
#include <string.h>
#include "ClientException.hh"

ClientException::ClientException(const std::string& msg) : _msg(msg)
{
}

const char* ClientException::what() const throw()
{
  std::string ret(_msg + strerror(errno));
  return (ret.c_str());
}
