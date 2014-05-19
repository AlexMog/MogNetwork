#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include "ServerClient.hh"
#include "Server.hh"

ServerClient::ServerClient(int socket, Server *server)
{
  _socket = socket;
  _server = server;
}

ServerClient::~ServerClient() {

}

int ServerClient::getSocket() const
{
  return (_socket);
}

void ServerClient::disconnect()
{
  close(_socket);
  _waitingPacket = WaitingPacket();
  for (std::list<ServerClient>::iterator it = _server->getClients().begin();
       it != _server->getClients().end(); ++it)
    if (it->getSocket() == _socket) {
      _server->getClients().erase(it);
      break;
    }
}

bool ServerClient::readSize(std::size_t size, char *data, std::size_t& received)
{
  int n = 0;

  if ((n = recv(_socket, static_cast<char*>(data), static_cast<int>(size), 0)) <= 0)
    return (true);
  received = n;
  return (false);
}

bool ServerClient::readPacket(Packet& packet)
{
  bool ret = false;
  uint32_t size = 0;
  std::size_t received = 0;
  char buffer[1024];

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
  // Réception des data du packet
  while (_waitingPacket.data.size() < size)
    {
      std::size_t toGet = std::min(static_cast<std::size_t>(size - _waitingPacket.data.size()), sizeof(buffer));
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

bool ServerClient::sendSize(const void* data, unsigned int size)
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

bool ServerClient::sendPacket(const Packet& packet)
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

ServerClient::WaitingPacket::WaitingPacket() :
  size(0),
  received(0),
  data() {}
