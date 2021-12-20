#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

class Socket {
public:
  const std::string hostname;
  const int port;

  Socket(const std::string& hostname, const int port);

  int connect();

  std::vector<char> receive();

  void send(const std::string& msg);

  void send(const std::vector<char>& msg);

  void close();

private:
  int sockfd;
};