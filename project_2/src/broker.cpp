#include "broker.h"
#include "mqtt-messages/connAckMsg.h"
#include "mqtt-messages/connMsg.h"
#include "mqtt-messages/publishMsg.h"
#include "mqtt-messages/subAckMsg.h"
#include "mqtt-messages/subMsg.h"

mqtt::Broker::Broker(const int port) : socket(port) {}

int mqtt::Broker::handleConnect(const std::vector<char>& msg) {
  mqtt::ConnMsg connMsg;

  if (!connMsg.deserialize(msg)) {
    std::cerr << "Failed to deserialize Connection Message\n";
    return 0;
  }

  std::cout << connMsg << "\n";

  mqtt::ConnAckMsg connAckMsg(mqtt::ConnectionAccepted);

  std::cout << connAckMsg << "\n";

  socket.respond(connAckMsg.serialize());

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
  mqtt::Header pingReqMsg;

  if (!pingReqMsg.deserialize(msg)) {
    std::cerr << "Failed to deserialize Publish Message\n";
    return 0;
  }

  std::cout << pingReqMsg << "\n";

  mqtt::Header pingRespMsg(mqtt::PINGRESP);

  std::cout << pingRespMsg << "\n";

  socket.respond(pingRespMsg.serialize());

  return 1;
}

int mqtt::Broker::handleSubscribe(const std::vector<char>& msg) {
  mqtt::SubMsg subMsg;

  if (!subMsg.deserialize(msg)) {
    std::cerr << "Failed to deserialize Subscribe Message\n";
    return 0;
  }

  std::cout << subMsg << "\n";

  mqtt::SubAckMsg subAckMsg(subMsg.getPacketId(), mqtt::SuccessQoS0);

  return 1;
}

int mqtt::Broker::handleUnsubscribe(const std::vector<char>& msg) { return 1; }

int mqtt::Broker::handleDisconnect(const std::vector<char>& msg) {
  mqtt::Header disconnectMsg;

  if (!disconnectMsg.deserialize(msg)) {
    std::cerr << "Failed to deserialize Disconnect Message\n";
    return 0;
  }

  std::cout << disconnectMsg << "\n";

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
    case mqtt::SUBSCRIBE:
      if (!handleSubscribe(msg))
        return 0;
      break;
    case mqtt::UNSUBSCRIBE:
      if (!handleUnsubscribe(msg))
        return 0;
      break;
    case mqtt::DISCONNECT:
      handleDisconnect(msg);
      return 0;
    default:
      std::cout << "Message type " << msgType << " not supported yet.\n";
      break;
    }
  }
}