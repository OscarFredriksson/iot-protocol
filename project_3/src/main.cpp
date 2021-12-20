#include "coap-client/client.h"
#include "coap-client/coapmessage.h"
#include <iostream>
// #include <mqtt_client_cpp.hpp>

int main() {

  // boost::asio::io_context ioc;
  // auto c = mqtt::make_sync_client(ioc, "127.0.0.1", 1883);
  // c->set_client_id("cid1");
  // c->set_clean_session(true);

  // c->set_connack_handler(
  //     [](bool sp, mqtt::connect_return_code connack_return_code) {
  //       std::cout << "CONNECT!!!"
  //                 << "\n";
  //       return true;
  //     });

  // c->connect();
  // ioc.run();

  std::string hostname = "coap.me";

  coap::Client client(hostname, 5683);
  if (client.connect() <= 0) {
    std::cout << "Failed to connect to " << hostname << "\n";
    return -1;
  }

  CoapMessage request(CoapCode::GET, 1337);

  request.setOptionUriPath("test");

  client.send(request);

  CoapMessage response = client.getResponse();

  std::cout << response << "\n";

  return 0;
}