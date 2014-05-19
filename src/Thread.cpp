#include <pthread.h>
#include <iostream>
#include <string>
#include <sstream>
#include <exception>

#include "Thread.hh"

Thread::Thread(IThreadListener* threadListener)
{
  _threadListener = threadListener;
}

Thread::~Thread()
{

}

void Thread::start()
{

  if (pthread_create(&_thread, NULL,  _threadListener->getFunc(), _threadListener->getData()))
    throw ThreadException("Thread creation failed.", __FILE__, __LINE__);
}

void Thread::stop()
{
  if (pthread_cancel(_thread))
    throw ThreadException("Thread cannot be cancelled.", __FILE__, __LINE__);
}

void Thread::join()
{
  if (pthread_join(_thread, NULL))
    throw ThreadException("Thread cannot be joined.", __FILE__, __LINE__);
}

void Thread::setThreadListener(IThreadListener* threadListener)
{
  _threadListener = threadListener;
}

pthread_t Thread::getThreadDatas() const
{
  return (_thread);
}

ThreadException::ThreadException(const char *msg, const char *file, int line)
{
  std::ostringstream os;

  os << "Error in file '" << file << "' on line " << line << " : " << msg;
  _msg = os.str();
}

ThreadException::~ThreadException() throw() {}

const char *ThreadException::what() const throw()
{
  return (_msg.c_str());
}
