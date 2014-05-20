//
// Client.cpp for Mog-Network in 
// 
// Made by Moghrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Tue May 20 13:22:00 2014 Moghrabi Alexandre
// Last update Tue May 20 13:24:40 2014 Moghrabi Alexandre
//

#include <iostream>
#include <string>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include "ClientException.hh"
#include "Client.hh"

Client::Client(const std::string& ip, int port)
{
  _ip = ip;
  _port = port;
  _serverListener = NULL;
  _disconnected = false;
}

Client::~Client()
{  
}

void Client::init()
{
  _socket = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in sin;
  memset(&sin, 0, sizeof(sockaddr_in));
  struct hostent *hostinfo;

  if (_socket == -1)
    throw ClientException("Socket: ");

  hostinfo = gethostbyname(_ip.c_str());
  if (hostinfo == NULL)
    throw ClientException("Gethostbyname: ");

  sin.sin_addr = *(struct in_addr *)hostinfo->h_addr;
  sin.sin_port = htons(_port);
  sin.sin_family = AF_INET;
  if (connect(_socket, (struct sockaddr *)&sin, sizeof(struct sockaddr)) == -1)
    throw ClientException("Connect: ");
}

void Client::disconnect()
{
  if (!_disconnected)
    close(_socket);
  _disconnected = true;
}

void Client::start()
{
  fd_set rdfs;

  while (true)
    {
      FD_ZERO(&rdfs);

      FD_SET(_socket, &rdfs);

      if (select(_socket + 1, &rdfs, NULL, NULL, NULL) == -1)
	throw ClientException("Select: ");

      else if (FD_ISSET(_socket, &rdfs))
	{
	  Packet packet;
	  if (readPacket(packet))
	    {
	      if (_serverListener != NULL)
		_serverListener->onDisconnect();
	      break;
	    }
	  interpretePacket(packet);
	}
    }
}

bool Client::readSize(unsigned int size, void* data, unsigned int& received)
{
  int n = 0;

  if ((n = recv(_socket, static_cast<char*>(data), static_cast<int>(size), 0)) <= 0)
    return (true);
  received = n;
  return (false);
}

bool Client::readPacket(Packet& packet)
{
  uint32_t size = 0;
  unsigned int received = 0;
  char buffer[1024];
  bool ret = false;

  packet.clear();
  // Reception de la taille du packet
  if (_waitingPacket.received < sizeof(_waitingPacket.size))
    {
      while (_waitingPacket.received < sizeof(_waitingPacket.size))
	{
	  char* data = reinterpret_cast<char*>(&_waitingPacket.size) + _waitingPacket.received;
	  ret = readSize(sizeof(uint32_t) - _waitingPacket.received, data, received);
	  _waitingPacket.received += received;
	  if (ret)
	    return (ret);
	}
    }
  size = ntohl(_waitingPacket.size);

  // Reception des data du packet
  while (_waitingPacket.data.size() < size)
    {
      unsigned int toGet = std::min(static_cast<long unsigned int>(size - _waitingPacket.data.size()), sizeof(buffer));
      ret = readSize(toGet, buffer, received);
      if (ret)
        return (ret);
      
      if (received > 0)
        {
          _waitingPacket.data.resize(_waitingPacket.data.size() + received);
          char* start = &_waitingPacket.data[0] + _waitingPacket.data.size() - received;
          memcpy(start, buffer, received);
        }
    }

  if (!_waitingPacket.data.empty())
    packet.push(&_waitingPacket.data[0], _waitingPacket.data.size());

  _waitingPacket = WaitingPacket();

  return (ret);
}

void Client::interpretePacket(Packet& packet)
{
  if (_serverListener != NULL)
    _serverListener->onOrder(packet);
}

bool Client::sendSize(const void* data, unsigned int size)
{
  int sent = 0;
  int toSend = static_cast<int>(size);

  for (int i = 0; i < toSend; i += sent)
    {
      sent = send(_socket, static_cast<const char*>(data) + i, toSend - i, 0);
      if (sent < 0)
	return (true);
    }
  return (false);
}

bool Client::sendPacket(const Packet& packet)
{
  unsigned int size = 0;
  size = packet.getDataSize();
  const void* data = packet.getData();

  uint32_t packetSize = htonl(static_cast<uint32_t>(size));
  std::vector<char> toSend(sizeof(packetSize) + size);
  memcpy(&toSend[0], &packetSize, sizeof(packetSize));
  if (size > 0)
    memcpy(&toSend[0] + sizeof(packetSize), data, size);
  
  return (sendSize(&toSend[0], toSend.size()));
}

void Client::setServerListener(IServerListener* serverListener)
{
  _serverListener = serverListener;
}

Client::WaitingPacket::WaitingPacket() :
  size(0),
  received(0),
  data() {}
