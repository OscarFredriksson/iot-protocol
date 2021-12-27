#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
// #include <openssl/err.h>
// #include <openssl/ssl.h>
#include <stdlib.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>
#include <wolfssl/options.h>
#include <wolfssl/ssl.h>

#define WOLFSSL_STATIC_PSK

class Socket {
public:
  const std::string hostname;
  const int port;

  Socket(const std::string& hostname, const int port);

  int connect();

  std::vector<char> receive();

  // void send(const std::string& msg);

  void send(const std::vector<char>& msg);

  void close();

private:
  int sockfd;

  WOLFSSL* ssl = NULL;
  WOLFSSL_CTX* ctx = NULL;
};