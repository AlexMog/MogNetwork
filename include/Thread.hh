#ifndef THREAD_HH_
#define THREAD_HH_

#include <pthread.h>
#include <exception>
#include "IThreadListener.hh"

class Thread
{
public:
  Thread(IThreadListener* threadListener);
  virtual ~Thread();

public:
  void start();
  void stop();
  void join();

public:
  void setThreadListener(IThreadListener* threadListener);
  pthread_t getThreadDatas() const;

private:
  IThreadListener* _threadListener;
  pthread_t _thread;
};

class ThreadException : public std::exception
{
public:
  ThreadException(const char *, const char *, int);
  virtual ~ThreadException() throw();

public:
  virtual const char*what() const throw();

private:
  std::string _msg;
};

#endif
