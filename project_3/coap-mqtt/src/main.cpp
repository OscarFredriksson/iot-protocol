#include "coap-client/client.h"
#include "coap-client/coapmessage.h"
#include <iostream>
// #include <mqtt_client_cpp.hpp>

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

int main() {

  //------------WORKS------------------
  // WOLFSSL* ssl = NULL;
  // WOLFSSL_CTX* ctx = NULL;

  // wolfSSL_Init();

  // if ((ctx = wolfSSL_CTX_new(wolfDTLSv1_2_client_method())) == NULL) {
  //   std::cerr << "wolfSSL_CTX_new error.\n";
  //   return 1;
  // }

  // wolfSSL_CTX_set_psk_client_callback(ctx, My_Psk_Client_Cb);

  // /* creat wolfssl object after each tcp connect */
  // if ((ssl = wolfSSL_new(ctx)) == NULL) {
  //   std::cout << "wolfSSL_new error.\n";
  //   return -1;
  // }

  // auto cipher = wolfSSL_get_cipher(ssl);
  // std::cout << cipher << "\n";

  // std::string hostname = "192.168.183.120";
  // int port = 5684;

  // sockaddr_in addr_in;
  // addr_in.sin_family = AF_INET;
  // addr_in.sin_port = htons(port);

  // addrinfo* first_addr = nullptr;

  // getaddrinfo(hostname.c_str(), std::to_string(port).c_str(), 0,
  // &first_addr);

  // if (inet_pton(AF_INET, hostname.c_str(), &addr_in.sin_addr) < 1) {
  //   printf("Error and/or invalid IP address");
  //   return 1;
  // }

  // wolfSSL_dtls_set_peer(ssl, &addr_in, sizeof(addr_in));

  // int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  // if (sockfd == 0) {
  //   std::cerr << "socket failed\n";
  //   return -1;
  // }

  // // /* associate the file descriptor with the session */
  // if (wolfSSL_set_fd(ssl, sockfd) != WOLFSSL_SUCCESS) {
  //   std::cerr << "Failed to set file descriptor for wolfSSL.\n";
  //   return -1;
  // }

  // if (wolfSSL_connect(ssl) != SSL_SUCCESS) {
  //   int err1 = wolfSSL_get_error(ssl, 0);
  //   printf("err = %d, %s\n", err1, wolfSSL_ERR_reason_error_string(err1));
  //   printf("SSL_connect failed\n");
  //   return 0;
  // }

  // char sendline[1024] = "Hello Server"; /* string to send to the server */
  // char recvline[1024];                  /* string received from the server*/

  // // /* write string to the server */
  // int writeReturn = wolfSSL_write(ssl, sendline, 1024);
  // std::cout << "Write Return code: " << writeReturn << "\n";
  // if (writeReturn != sizeof(sendline)) {
  //   printf("Write Error to Server\n");
  //   return -1;
  // }

  // // /* check if server ended before client could read a response  */
  // if (wolfSSL_read(ssl, recvline, 1024) < 0) {
  //   printf("Client: Server Terminated Prematurely!\n");
  //   return -1;
  // }

  // // /* show message from the server */
  // printf("Server Message: %s\n", recvline);
  // }
  // boost::asio::io_context ioc;
  // auto c = mqtt::make_sync_client(ioc, "127.0.0.1", 1883);
  // c->set_client_id("cid1");
  // c->set_clean_session(true);

  // std::uint16_t pid_sub1;

  // using packet_id_t =
  //     typename std::remove_reference_t<decltype(*c)>::packet_id_t;

  // c->set_connack_handler(
  //     [&c, &pid_sub1](bool sp, mqtt::connect_return_code
  //     connack_return_code)
  //     {
  //       std::cout << "Connect!"
  //                 << "\n";

  //       pid_sub1 = c->subscribe("#", MQTT_NS::qos::at_most_once);

  //       return true;
  //     });

  // c->set_publish_handler([&](MQTT_NS::optional<packet_id_t> packet_id,
  //                            MQTT_NS::publish_options pubopts,
  //                            MQTT_NS::buffer topic_name,
  //                            MQTT_NS::buffer contents) {
  //   std::cout << "publish received."
  //             << " dup: " << pubopts.get_dup() << " qos: " <<
  //             pubopts.get_qos()
  //             << " retain: " << pubopts.get_retain() << std::endl;
  //   if (packet_id)
  //     std::cout << "packet_id: " << *packet_id << std::endl;
  //   std::cout << "topic_name: " << topic_name << std::endl;
  //   std::cout << "contents: " << contents << std::endl;

  std::string hostname = "192.168.183.120";

  coap::Client client(hostname, 5684);
  if (client.connect() <= 0) {
    std::cout << "Failed to connect to " << hostname << "\n";
    return 0;
  }

  // std::string topic = std::string(topic_name);

  // std::string coapCodeStr = topic.substr(0, topic.find("/"));

  // std::string coapUriPath = topic.substr(topic.find("/") + 1,
  // topic.length());

  std::string coapCodeStr = "PUT";

  CoapCode coapCode;

  if (coapCodeStr == "GET")
    coapCode = CoapCode::GET;
  else if (coapCodeStr == "POST")
    coapCode = CoapCode::POST;
  else if (coapCodeStr == "PUT")
    coapCode = CoapCode::PUT;
  else if (coapCodeStr == "DELETE")
    coapCode = CoapCode::DELETE;

  CoapMessage request(coapCode, 1337);

  std::string coapUriPath = "15001/65536";

  request.setOptionUriPath(coapUriPath);
  request.setPayload("{ \"3311\": [{ \"5851\": 10 }] }");

  std::cout << request << "\n";

  client.send(request);

  CoapMessage response = client.getResponse();

  std::cout << response << "\n";

  //   return true;
  // });

  // c->connect();
  // ioc.run();

  return 0;
}