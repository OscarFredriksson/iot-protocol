#include "broker.h"

mqtt::Broker::Broker(const int port) : port(port) {}

int mqtt::Broker::handleConnect(const std::vector<char>& msg, Socket* socket) {
  mqtt::ConnMsg connMsg;

  if (!connMsg.deserialize(msg)) {
    std::cerr << "Failed to deserialize Connection Message\n";
    return 0;
  }

  std::cout << connMsg << "\n";

  mqtt::ConnAckMsg connAckMsg(mqtt::ConnectionAccepted);

  std::cout << connAckMsg << "\n";

  socket->send(connAckMsg.serialize());

  return 1;
}

int mqtt::Broker::handlePingReq(const std::vector<char>& msg, Socket* socket) {
  mqtt::Header pingReqMsg;

  if (!pingReqMsg.deserialize(msg)) {
    std::cerr << "Failed to deserialize Publish Message\n";
    return 0;
  }

  std::cout << pingReqMsg << "\n";

  mqtt::Header pingRespMsg(mqtt::PINGRESP);

  std::cout << pingRespMsg << "\n";

  std::vector<char> serializedMsg = pingRespMsg.serialize();
  serializedMsg.push_back(char(0x00));

  socket->send(serializedMsg);

  return 1;
}

int mqtt::Broker::handleSubscribe(const std::vector<char>& msg,
                                  Socket* socket) {
  mqtt::SubMsg subMsg;

  if (!subMsg.deserialize(msg)) {
    std::cerr << "Failed to deserialize Subscribe Message\n";
    return 0;
  }

  std::cout << subMsg << "\n";

  subscribers[subMsg.getTopic()].insert(socket);

  mqtt::SubAckMsg subAckMsg(subMsg.getPacketId(), mqtt::SuccessQoS0);

  std::cout << subAckMsg << "\n";

  socket->send(subAckMsg.serialize());

  return 1;
}

int mqtt::Broker::handleUnsubscribe(const std::vector<char>& msg,
                                    Socket* socket) {
  return 1;
}

int mqtt::Broker::handlePublish(const std::vector<char>& msg, Socket* socket) {
  mqtt::PublishMsg publishMsg;

  if (!publishMsg.deserialize(msg)) {
    std::cerr << "Failed to deserialize Publish Message\n";
    return 0;
  }

  std::cout << publishMsg << "\n";

  std::string topic = publishMsg.getTopic();

  std::set<Socket*> topicSubs = subscribers[topic];

  std::cout << "Subscribers: " << topicSubs.size() << "\n";

  for (auto sub : topicSubs) {
    sub->send(msg);
  }

  return 1;
}

int mqtt::Broker::handleDisconnect(const std::vector<char>& msg,
                                   Socket* socket) {
  mqtt::Header disconnectMsg;

  if (!disconnectMsg.deserialize(msg)) {
    std::cerr << "Failed to deserialize Disconnect Message\n";
    return 0;
  }

  std::cout << disconnectMsg << "\n";

  socket->close();

  return 1;
}

mqtt::MessageType mqtt::Broker::getMessageType(const std::vector<char>& msg) {

  return static_cast<mqtt::MessageType>((msg[0] & 0b11110000) >> 4);
}

int mqtt::Broker::handleClient(Socket* socket) {
  while (true) {
    std::vector<char> msg = socket->receive();

    if (msg.empty())
      return 0;

    mqtt::MessageType msgType = getMessageType(msg);

    switch (msgType) {
    case mqtt::CONNECT:
      if (!handleConnect(msg, socket))
        std::cerr << "Failed to handle connect.\n";
      break;
    case mqtt::PUBLISH:
      if (!handlePublish(msg, socket))
        std::cerr << "Failed to handle publish.\n";
      break;
    case mqtt::PINGREQ:
      if (!handlePingReq(msg, socket))
        std::cerr << "Failed to handle ping request.\n";
      break;
    case mqtt::SUBSCRIBE:
      if (!handleSubscribe(msg, socket))
        std::cerr << "Failed to handle subscribe.\n";
      break;
    case mqtt::UNSUBSCRIBE:
      if (!handleUnsubscribe(msg, socket))
        std::cerr << "Failed to handle unsubscribe.\n";
      break;
    case mqtt::DISCONNECT:
      handleDisconnect(msg, socket);
      return 1;
    default:
      std::cout << "Message type " << msgType << " not supported yet.\n";
      break;
    }
  }
}

int mqtt::Broker::start() {

  while (true) {
    Socket* socket = new Socket(port);

    if (!socket->connect()) {
      std::cout << "failed to connect\n";
      return 0;
    }

    handleClient(socket);
  }
}