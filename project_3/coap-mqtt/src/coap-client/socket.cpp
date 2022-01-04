#include "socket.h"
#include "constants.h"
#include <arpa/inet.h>
#include <iostream>
#include <stdio.h>
// #include <errno.h>

Socket::Socket(const std::string& hostname, const int port)
    : hostname(hostname), port(port) {}

inline unsigned int Socket::My_Psk_Client_Cb(WOLFSSL* ssl, const char* hint,
                                             char* identity,
                                             unsigned int id_max_len,
                                             unsigned char* key,
                                             unsigned int key_max_len) {
  (void)ssl;
  (void)hint;
  (void)key_max_len;

  strncpy(identity, USER_IDENTITY.c_str(), id_max_len);

  for (int i = 0; i < PSK_STR.length(); i++) {
    key[i] = PSK_STR[i];
  }

  return PSK_STR.length();
}

int Socket::connect() {

  wolfSSL_Init();

  if ((ctx = wolfSSL_CTX_new(wolfDTLSv1_2_client_method())) == NULL) {
    std::cerr << "wolfSSL_CTX_new error.\n";
    return 1;
  }

  wolfSSL_CTX_set_psk_client_callback(ctx, My_Psk_Client_Cb);

  /* creat wolfssl object after each tcp connect */
  if ((ssl = wolfSSL_new(ctx)) == NULL) {
    std::cout << "wolfSSL_new error.\n";
    return -1;
  }

  sockaddr_in addr_in;
  addr_in.sin_family = AF_INET;
  addr_in.sin_port = htons(port);

  if (inet_pton(AF_INET, hostname.c_str(), &addr_in.sin_addr) < 1) {
    printf("Error and/or invalid IP address");
    return -1;
  }

  wolfSSL_dtls_set_peer(ssl, &addr_in, sizeof(addr_in));

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  if (sockfd == 0) {
    std::cerr << "socket failed\n";
    return -1;
  }

  if (wolfSSL_set_fd(ssl, sockfd) != WOLFSSL_SUCCESS) {
    std::cerr << "Failed to set file descriptor for wolfSSL.\n";
    return -1;
  }

  if (wolfSSL_connect(ssl) != SSL_SUCCESS) {
    int err1 = wolfSSL_get_error(ssl, 0);
    printf("err = %d, %s\n", err1, wolfSSL_ERR_reason_error_string(err1));
    printf("SSL_connect failed\n");
    return 0;
  }

  // /* associate the file descriptor with the session */
  // if (wolfSSL_set_fd(ssl, sockfd) != WOLFSSL_SUCCESS) {
  //   std::cerr << "Failed to set file descriptor for wolfSSL.\n";
  //   return -1;
  // }

  std::cout << "Connected!\n";
  return 1;
}

std::vector<char> Socket::receive() {

  int msgSize = 2048;
  char msg[msgSize];

  int byteCount = wolfSSL_read(ssl, msg, msgSize);

  if (byteCount < 0) {
    std::cout << byteCount << "\n";
    printf("Client: Server Terminated Prematurely!\n");
    return std::vector<char>();
  }

  // Convert the char array to a vector that is as long as the number of read
  // bytes
  return std::vector<char>(msg, msg + byteCount);
  ;
}

void Socket::send(const std::vector<char>& msg) {

  int writeReturn = wolfSSL_write(ssl, msg.data(), msg.size());
  //   std::cout << "Write Return code: " << std::dec << writeReturn << "\n";
  if (writeReturn != msg.size())
    printf("Write Error to Server\n");
}

void Socket::close() {
  if (ssl)
    wolfSSL_free(ssl); // Free the wolfSSL object

  ::close(sockfd); // Close the socket

  if (ctx)
    wolfSSL_CTX_free(ctx); // Free the wolfSSL context object

  wolfSSL_Cleanup();
}