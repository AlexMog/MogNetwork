//
// Packet.cpp for packet in /home/alexmog/projets/projets/cpp_nibbler/network/server
// 
// Made by Moghrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Fri Apr  4 21:48:49 2014 Moghrabi Alexandre
// Last update Tue May 20 13:03:32 2014 Moghrabi Alexandre
//

#include <string.h>
#include "Packet.hh"

Packet::Packet() : _readerPos(0) {}

Packet::~Packet() {}

void Packet::push(const void* data, unsigned int size)
{
  unsigned int actualSize;

  if (data && (size > 0))
    {
      actualSize = _data.size();
      _data.resize(actualSize + size);
      memcpy(&_data[actualSize], data, size);
    }
}
void Packet::clear()
{
  _data.clear();
  _readerPos = 0;
}

const void* Packet::getData() const
{
  return (!_data.empty() ? &_data[0] : NULL);
}

Packet& Packet::operator>>(uint32_t& data)
{
  if (verifySize(sizeof(data)))
    {
      data = ntohl(*reinterpret_cast<const uint32_t*>(&_data[_readerPos]));
      _readerPos += sizeof(data);
    }
  return (*this);
}

Packet& Packet::operator>>(int& data)
{
  if (verifySize(sizeof(data)))
    {
      data = *reinterpret_cast<const int*>(&_data[_readerPos]);
      _readerPos += sizeof(data);
    }
  return (*this);
}

Packet& Packet::operator>>(float& data)
{
  if (verifySize(sizeof(data)))
    {
      data = *reinterpret_cast<const float*>(&_data[_readerPos]);
      _readerPos += sizeof(data);
    }
  return (*this);
}

Packet& Packet::operator>>(double& data)
{
  if (verifySize(sizeof(data)))
    {
      data = *reinterpret_cast<const double*>(&_data[_readerPos]);
      _readerPos += sizeof(data);
    }
  return (*this);
}

Packet& Packet::operator>>(char* data)
{
  uint32_t size = 0;
  *this >> size;
  
  if (size > 0 && verifySize(size))
    {
      memcpy(data, &_data[_readerPos], size);
      data[size] = '\0';
      _readerPos += size;
    }
  return (*this);
}
 
Packet& Packet::operator>>(std::string& data)
{
  uint32_t size = 0;
  *this >> size;
  
  data.clear();
  if (size > 0 && verifySize(size))
    {
      data.assign(_data[_readerPos], size);
      _readerPos += size;
    }
  return (*this);
}

Packet& Packet::operator<<(uint32_t data)
{
  uint32_t write = htonl(data);
  push(&write, sizeof(write));
  return (*this);
}

Packet& Packet::operator<<(int data)
{
  push(&data, sizeof(data));
  return (*this);
}

Packet& Packet::operator<<(const char* data)
{
  uint32_t size = strlen(data);
  *this << size;
  push(data, size * sizeof(char));
  return (*this);
}

Packet& Packet::operator<<(const std::string& data)
{
  uint32_t size = data.size();
  *this << size;

  if (size > 0)
    push(data.c_str(), size * sizeof(std::string::value_type));
  return (*this);
}

bool Packet::verifySize(unsigned int size)
{
  return (_readerPos + size <= _data.size());
}

unsigned int Packet::getDataSize() const
{
  return (_data.size());
}
