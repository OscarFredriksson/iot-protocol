#include "socket.h"
#include <arpa/inet.h>
#include <stdio.h>
// #include <errno.h>

Socket::Socket(const std::string& hostname, const int port)
    : hostname(hostname), port(port) {}

static inline unsigned int My_Psk_Client_Cb(WOLFSSL* ssl, const char* hint,
                                            char* identity,
                                            unsigned int id_max_len,
                                            unsigned char* key,
                                            unsigned int key_max_len) {
  (void)ssl;
  (void)hint;
  (void)key_max_len;

  std::cout << "Callback!\n";
  std::cout << "hint: " << hint << " identity: " << identity << " id_max_len "
            << id_max_len << " key: " << key << " key_max_len: " << key_max_len
            << "\n";

  /* identity is OpenSSL testing default for openssl s_client, keep same*/
  strncpy(identity, "oscar", id_max_len);

  /* test key n hex is 0x1a2b3c4d , in decimal 439,041,101, we're using
   * unsigned binary */

  // if (wolfSSL_GetVersion(ssl) < WOLFSSL_TLSV1_3) {
  //   std::cout << ":D\n";

  // 0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15
  // 64 65 4f 36 67 52 34 67 52 73 62 5a 4f 61 76 69
  key[0] = 0x64;
  key[1] = 0x65;
  key[2] = 0x4f;
  key[3] = 0x36;
  key[4] = 0x67;
  key[5] = 0x52;
  key[6] = 0x34;
  key[7] = 0x67;
  key[8] = 0x52;
  key[9] = 0x73;
  key[10] = 0x62;
  key[11] = 0x5a;
  key[12] = 0x4f;
  key[13] = 0x61;
  key[14] = 0x76;
  key[15] = 0x69;

  return 16;

  // } else {
  //   std::cout << "hmm\n";
  //   int i;
  //   int b = 0x01;
  //   for (i = 0; i < 32; i++, b += 0x22) {
  //     if (b >= 0x100)
  //       b = 0x01;
  //     key[i] = b;
  //   }
  //   return 32; /* length of key in octets or 0 for error */
  // }
}

int Socket::connect() {
  //   const SSL_METHOD* method = DTLS_method();
  //   SSL_CTX* ctx = SSL_CTX_new(method);

  //   SSL* ssl = SSL_new(ctx);

  //   if (ssl == nullptr) {
  //     std::cout << "SSL_new() failed\n";
  //   }

  //   wolfSSL_CTX_set_cipher_list(WOLFSSL_STATIC_PSK);

  wolfSSL_Init();

  if ((ctx = wolfSSL_CTX_new(wolfDTLSv1_2_client_method())) == NULL) {
    std::cerr << "wolfSSL_CTX_new error.\n";
    return 1;
  }

  wolfSSL_CTX_set_psk_client_callback(ctx, My_Psk_Client_Cb);
  //   wolfSSL_CTX_set_psk_client_tls13_callback(ctx, My_Psk_Client_Cb);

  /* creat wolfssl object after each tcp connect */
  if ((ssl = wolfSSL_new(ctx)) == NULL) {
    std::cout << "wolfSSL_new error.\n";
    return -1;
  }

  //   wolfSSL_set_psk_client_tls13_callback(ssl, My_Psk_Client_Cb);

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

  //   addrinfo* first_addr = nullptr;

  //   getaddrinfo(hostname.c_str(), std::to_string(port).c_str(), 0,
  //   &first_addr);

  int connectReturn = wolfSSL_connect(ssl);

  std::cout << "Connect Return: " << connectReturn << "\n";

  if (connectReturn != SSL_SUCCESS) {
    int err1 = wolfSSL_get_error(ssl, 0);
    printf("err = %d, %s\n", err1, wolfSSL_ERR_reason_error_string(err1));
    printf("SSL_connect failed\n");
    return 0;
  }

  //   for (addrinfo* addr_it = first_addr; addr_it != nullptr;
  //        addr_it = addr_it->ai_next) {

  //     if (::connect(sockfd, addr_it->ai_addr, sizeof(addr_in)) < 0) {
  //       std::cerr << "ERROR connecting\n";
  //       continue;
  //     }

  /* associate the file descriptor with the session */
  if (wolfSSL_set_fd(ssl, sockfd) != WOLFSSL_SUCCESS) {
    std::cerr << "Failed to set file descriptor for wolfSSL.\n";
    return -1;
  }

  //   char sendline[256] = "Hello Server"; /* string to send to the server */
  //   char recvline[256];                  /* string received from the server
  //   */

  //   /* write string to the server */
  //   int writeReturn = wolfSSL_write(ssl, sendline, 256);
  //   std::cout << "Write Return code: " << writeReturn << "\n";
  //   if (writeReturn != sizeof(sendline)) {
  //     printf("Write Error to Server\n");
  //     return -1;
  //   }

  //   /* check if server ended before client could read a response  */
  //   if (wolfSSL_read(ssl, recvline, 256) < 0) {
  //     printf("Client: Server Terminated Prematurely!\n");
  //     return -1;
  //   }

  //   /* show message from the server */
  //   printf("Server Message: %s\n", recvline);

  //   if (fgets(sendline, 256, stdin) != NULL) {

  //     /* Send sendLine to the server */
  //     if ((wolfSSL_write(ssl, sendline, strlen(sendline))) !=
  //     strlen(sendline)) {
  //       printf("SSL_write failed");
  //     }

  //     /* n is the # of bytes received */
  //     int n = wolfSSL_read(ssl, recvline, sizeof(recvline) - 1);

  //     if (n < 0) {
  //       int readErr = wolfSSL_get_error(ssl, 0);
  //       std::cout << "Read error: " << (int)readErr << "\n";
  //       // if (readErr != SSL_ERROR_WANT_READ) {
  //       //   printf("wolfSSL_read failed");
  //       // }
  //     }

  //     /* Add a terminating character to the generic server message */
  //     recvline[n] = '\0';
  //     fputs(recvline, stdout);
  //   }

  std::cout << "Connected!\n";
  return 1;
  //   }

  // Got through the loop without succesfully connecting to any of the hosts,
  // return failure
  return -1;
}

std::vector<char> Socket::receive() {

  int msgSize = 1024;
  char msg[msgSize];

  int byteCount = wolfSSL_read(ssl, msg, msgSize);

  if (byteCount < 0) {
    std::cout << byteCount << "\n";
    printf("Client: Server Terminated Prematurely!\n");
    return std::vector<char>();
  }

  /* show message from the server */
  //   printf("Server Message: %s\n", msg);

  // Receive a response into a fixed size style char array
  //   int byteCount = read(sockfd, msg, msgSize);

  // Convert the char array to a vector that is as long as the number of read
  // bytes
  return std::vector<char>(msg, msg + byteCount);
}

// void Socket::send(const std::string& msg) {
//   /* write string to the server */
//   if (wolfSSL_write(ssl, msg.data(), msg.length()) != msg.length()) {
//     printf("Write Error to Server\n");
//     return;
//   }
//   //   ::send(sockfd, msg.c_str(), msg.size(), 0);
// }

void Socket::send(const std::vector<char>& msg) {
  std::cout << "sending!\n";

  int writeReturn = wolfSSL_write(ssl, msg.data(), msg.size());
  std::cout << "Write Return code: " << writeReturn << "\n";
  //   if(writeReturn != msg.size()) {
  //     printf("Write Error to Server\n");
  //     return;
  //   }
  //   ::send(sockfd, msg.data(), msg.size(), 0);
}

void Socket::close() {
  if (ssl)
    wolfSSL_free(ssl); /* Free the wolfSSL object              */
  ::close(sockfd);     /* Close the socket   */
  if (ctx)
    wolfSSL_CTX_free(ctx); /* Free the wolfSSL context object          */
  wolfSSL_Cleanup();
}