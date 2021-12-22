#include "coap-client/client.h"
#include "coap-client/coapmessage.h"
#include <iostream>
#include <mqtt_client_cpp.hpp>

int main() {

  boost::asio::io_context ioc;
  auto c = mqtt::make_sync_client(ioc, "127.0.0.1", 1883);
  c->set_client_id("cid1");
  c->set_clean_session(true);

  std::uint16_t pid_sub1;

  using packet_id_t =
      typename std::remove_reference_t<decltype(*c)>::packet_id_t;

  c->set_connack_handler(
      [&c, &pid_sub1](bool sp, mqtt::connect_return_code connack_return_code) {
        std::cout << "Connect!"
                  << "\n";

        pid_sub1 = c->subscribe("#", MQTT_NS::qos::at_most_once);

        return true;
      });

  c->set_publish_handler([&](MQTT_NS::optional<packet_id_t> packet_id,
                             MQTT_NS::publish_options pubopts,
                             MQTT_NS::buffer topic_name,
                             MQTT_NS::buffer contents) {
    std::cout << "publish received."
              << " dup: " << pubopts.get_dup() << " qos: " << pubopts.get_qos()
              << " retain: " << pubopts.get_retain() << std::endl;
    if (packet_id)
      std::cout << "packet_id: " << *packet_id << std::endl;
    std::cout << "topic_name: " << topic_name << std::endl;
    std::cout << "contents: " << contents << std::endl;

    std::string hostname = "coap.me";

    coap::Client client(hostname, 5683);
    if (client.connect() <= 0) {
      std::cout << "Failed to connect to " << hostname << "\n";
      return false;
    }

    std::string topic = std::string(topic_name);

    std::string coapCodeStr = topic.substr(0, topic.find("/"));

    std::string coapUriPath = topic.substr(topic.find("/") + 1, topic.length());

    std::cout << coapCodeStr << " " << coapUriPath << "\n";

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

    request.setOptionUriPath(std::string(coapUriPath));

    request.setPayload(std::string(contents));

    client.send(request);

    CoapMessage response = client.getResponse();

    std::cout << response << "\n";

    return true;
  });

  c->connect();
  ioc.run();

  return 0;
}