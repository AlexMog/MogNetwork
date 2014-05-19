//
// IThreadListener.hh for thread in /home/alexmog/projets/projets/cpp_nibbler/network/server-core
// 
// Made by Moghrabi Alexandre
// Login   <alexmog@epitech.net>
// 
// Started on  Sun Apr  6 14:03:33 2014 Moghrabi Alexandre
// Last update Sun Apr  6 16:02:04 2014 Moghrabi Alexandre
//

#ifndef ITHREADLISTENER_HH_
# define ITHREADLISTENER_HH_

typedef void *(*fntPtr)(void *);

class IThreadListener
{
public:
  virtual ~IThreadListener() {}

public:
  virtual fntPtr getFunc() const = 0;
  virtual void* getData() const = 0;
};

#endif // ITHREADLISTENER_HH_
