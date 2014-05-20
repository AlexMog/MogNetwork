//
// Packet.hh for packet in /home/alexmog/projets/projets/cpp_nibbler/network/server
// 
// Made by Moghrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Fri Apr  4 21:38:40 2014 Moghrabi Alexandre
// Last update Tue May 20 13:04:07 2014 Moghrabi Alexandre
//

#ifndef PACKET_HH_
# define PACKET_HH_

#include <iostream>
#include <string>
#include <vector>
#include <arpa/inet.h>

class Packet
{
public:
  Packet();
  ~Packet();

  // Reading operators
public:
  Packet& operator>>(uint32_t&		data);
  Packet& operator>>(int&		data);
  Packet& operator>>(float&		data);
  Packet& operator>>(double&		data);
  Packet& operator>>(char*		data);
  Packet& operator>>(std::string&	data);

  // Insert operators
public:
  Packet& operator<<(uint32_t		data);
  Packet& operator<<(int		data);
  Packet& operator<<(float		data);
  Packet& operator<<(double		data);
  Packet& operator<<(const char*       	data);
  Packet& operator<<(const std::string&	data);

  // Main functions
public:
  void push(const void *data, unsigned int size);
  void clear();
  const void* getData() const;
  unsigned int getDataSize() const;

private:
  bool verifySize(unsigned int size);

private:
  std::vector<char>			_data;
  unsigned int				_readerPos;
};

#endif // !PACKET_HH_
