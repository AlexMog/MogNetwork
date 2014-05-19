#ifndef SERVEREXCEPTION_HH_
# define SERVEREXCEPTION_HH_

# include <string>
# include <exception>

class ServerException : public std::exception
{
public:
  ServerException(const std::string& msg);
  virtual ~ServerException() throw() {}

public:
  virtual const char* what() const throw();

private:
  std::string _msg;
};

#endif
