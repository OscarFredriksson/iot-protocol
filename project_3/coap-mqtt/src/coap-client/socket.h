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
  const static std::string psk_str;

  const std::string hostname;
  const int port;

  Socket(const std::string& hostname, const int port);

  int connect();

  std::vector<char> receive();

  // void send(const std::string& msg);

  void send(const std::vector<char>& msg);

  void close();

private:
  static inline unsigned int My_Psk_Client_Cb(WOLFSSL* ssl, const char* hint,
                                              char* identity,
                                              unsigned int id_max_len,
                                              unsigned char* key,
                                              unsigned int key_max_len);

  int sockfd;

  WOLFSSL* ssl = NULL;
  WOLFSSL_CTX* ctx = NULL;
};