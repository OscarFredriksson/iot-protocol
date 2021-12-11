#include "broker.h"
#include "mqtt-messages/baseMsg.h"

mqtt::Broker::Broker(const int port) : socket(port) {}

int mqtt::Broker::handleConnect(const std::vector<char>& msg) {
  mqtt::ConnMsg connMsg;

  if (!connMsg.deserialize(msg)) {
    std::cerr << "Failed to deserialize Connection Message\n";
    return 0;
  }

  std::cout << connMsg << "\n";

  mqtt::ConnackMsg connackMsg(mqtt::ConnectionAccepted);

  std::cout << connackMsg << "\n";

  socket.respond(connackMsg.serialize());

  return 1;
}

int mqtt::Broker::handlePublish(const std::vector<char>& msg) {
  mqtt::PublishMsg publishMsg;

  if (!publishMsg.deserialize(msg)) {
    std::cerr << "Failed to deserialize Publish Message\n";
    return 0;
  }

  std::cout << publishMsg << "\n";

  return 1;
}

int mqtt::Broker::handlePingReq(const std::vector<char>& msg) {
  mqtt::BaseMsg pingReqMsg;

  if (!pingReqMsg.deserialize(msg)) {
    std::cerr << "Failed to deserialize Publish Message\n";
    return 0;
  }

  std::cout << pingReqMsg << "\n";

  mqtt::BaseMsg pingRespMsg(mqtt::PINGRESP);

  socket.respond(pingRespMsg.serialize());

  return 1;
}

mqtt::MessageType mqtt::Broker::getMessageType(const std::vector<char>& msg) {

  return static_cast<mqtt::MessageType>((msg[0] & 0b11110000) >> 4);
}

int mqtt::Broker::start() {

  if (!socket.connect()) {
    std::cout << "failed to connect\n";
    return 0;
  }

  while (true) {
    std::vector<char> msg = socket.receive();

    if (msg.empty())
      return 0;

    mqtt::MessageType msgType = getMessageType(msg);

    switch (msgType) {
    case mqtt::CONNECT:
      if (!handleConnect(msg))
        return 0;
      break;
    case mqtt::PUBLISH:
      if (!handlePublish(msg))
        return 0;
      break;
    case mqtt::PINGREQ:
      if (!handlePingReq(msg))
        return 0;
      break;
    default:
      // std::cout << "Message type " << msgType << " not supported yet.\n";
      break;
    }
  }
}