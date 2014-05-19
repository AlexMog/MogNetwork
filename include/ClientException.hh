#ifndef CLIENTEXCEPTION_HH_
# define CLIENTEXCEPTION_HH_

# include <string>
# include <exception>

class ClientException : public std::exception
{
public:
  ClientException(const std::string& msg);
  virtual ~ClientException() throw() {}

public:
  virtual const char* what() const throw();

private:
  std::string _msg;
};

#endif
