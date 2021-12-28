#include "coap-client/client.h"
#include "coap-client/coapmessage.h"
#include "coap-client/constants.h"
#include <iostream>
#include <mqtt_client_cpp.hpp>
#include <random>

std::string getTopicLampId(const std::string& topic) {
  if (topic == "lamp1")
    return "65536";
  else
    throw "Unkown topic";
}

int getRandomMessageId() {
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<int> dist(1, 65535);

  return dist(mt);
}

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
        std::cout << "Connect!\n";

        pid_sub1 = c->subscribe("lamp1", MQTT_NS::qos::at_most_once);

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

    coap::Client client(GATEWAY_IP, 5684);
    if (client.connect() <= 0) {
      std::cout << "Failed to connect to " << GATEWAY_IP << "\n";
      return false;
    }

    CoapMessage request(CoapCode::PUT, getRandomMessageId());

    std::string coapUriPath =
        "15001/" + getTopicLampId(std::string(topic_name));

    request.setOptionUriPath(coapUriPath);
    request.setPayload("{ \"3311\": [" + std::string(contents) + "] }");

    std::cout << request << "\n";

    client.send(request);

    CoapMessage response = client.getResponse();

    std::cout << response << "\n";

    return true;
  });

  c->connect();
  ioc.run();

  return 0;
}