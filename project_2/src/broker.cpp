#include "broker.h"

mqtt::Broker::Broker(const int port) : port(port) {}

int mqtt::Broker::handleConnect(const mqtt::Header& header,
                                const std::vector<char>& remainingBytes,
                                Socket* socket) {
  mqtt::ConnMsg connMsg(header);

  if (!connMsg.deserialize(remainingBytes)) {
    std::cerr << "Failed to deserialize Connection Message\n";
    return 0;
  }

  std::cout << connMsg << "\n";

  mqtt::ConnAckMsg connAckMsg(mqtt::ConnectionAccepted);

  std::cout << connAckMsg << "\n";

  socket->send(connAckMsg.serialize());

  return 1;
}

int mqtt::Broker::handlePingReq(const mqtt::Header& header, Socket* socket) {

  std::cout << header << "\n";

  mqtt::Header pingRespMsg(mqtt::PINGRESP);

  std::cout << pingRespMsg << "\n";

  std::vector<char> serializedMsg = pingRespMsg.serialize();

  socket->send(serializedMsg);

  return 1;
}

int mqtt::Broker::handleSubscribe(const mqtt::Header& header,
                                  const std::vector<char>& remainingBytes,
                                  Socket* socket) {
  mqtt::SubMsg subMsg(header);

  if (!subMsg.deserialize(remainingBytes)) {
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

int mqtt::Broker::handleUnsubscribe(const mqtt::Header& header,
                                    const std::vector<char>& remainingBytes,
                                    Socket* socket) {
  mqtt::UnsubMsg unsubMsg(header);

  if (!unsubMsg.deserialize(remainingBytes)) {
    std::cerr << "Failed to deserialize Unsubscribe Message\n";
    return 0;
  }

  std::cout << unsubMsg << "\n";

  std::set<Socket*>& topicSubs = subscribers[unsubMsg.getTopic()];

  if (topicSubs.contains(socket)) {
    topicSubs.erase(socket);
    if (topicSubs.empty())
      subscribers.erase(unsubMsg.getTopic());
  }

  return 1;
}

int mqtt::Broker::handlePublish(const mqtt::Header& header,
                                const std::vector<char>& remainingBytes,
                                Socket* socket) {
  mqtt::PublishMsg publishMsg(header);

  if (!publishMsg.deserialize(remainingBytes)) {
    std::cerr << "Failed to deserialize Publish Message\n";
    return 0;
  }

  std::cout << publishMsg << "\n";

  std::string topic = publishMsg.getTopic();

  std::set<Socket*> topicSubs = subscribers[topic];

  std::cout << "Subscribers: " << topicSubs.size() << "\n";

  std::vector<char> fullMsg = header.serialize();

  fullMsg.insert(fullMsg.end(), remainingBytes.begin(), remainingBytes.end());

  for (auto sub : topicSubs) {
    sub->send(fullMsg);
  }

  return 1;
}

int mqtt::Broker::handleDisconnect(const mqtt::Header& header, Socket* socket) {

  std::cout << header << "\n";

  socket->close();

  return 1;
}

int mqtt::Broker::handleClient(Socket* socket) {
  while (true) {
    std::vector<char> bytes = socket->receive(2);

    if (bytes.empty())
      return 0;

    mqtt::Header header;
    if (!header.deserialize(bytes)) {
      std::cerr << "Failed to deserialize Disconnect Message\n";
      continue;
    }

    std::vector<char> remainingBytes =
        socket->receive(header.getRemainingLength());

    mqtt::MessageType msgType = header.getMessageType(); // getMessageType(msg);

    switch (msgType) {
    case mqtt::CONNECT:
      if (!handleConnect(header, remainingBytes, socket))
        std::cerr << "Failed to handle connect.\n";
      break;
    case mqtt::PUBLISH:
      if (!handlePublish(header, remainingBytes, socket))
        std::cerr << "Failed to handle publish.\n";
      break;
    case mqtt::PINGREQ:
      if (!handlePingReq(header, socket))
        std::cerr << "Failed to handle ping request.\n";
      break;
    case mqtt::SUBSCRIBE:
      if (!handleSubscribe(header, remainingBytes, socket))
        std::cerr << "Failed to handle subscribe.\n";
      break;
    case mqtt::UNSUBSCRIBE:
      if (!handleUnsubscribe(header, remainingBytes, socket))
        std::cerr << "Failed to handle unsubscribe.\n";
      break;
    case mqtt::DISCONNECT:
      handleDisconnect(header, socket);
      delete socket;
      return 1;
    default:
      std::cout << "Message type " << msgType << " not supported yet.\n";
      return 1;
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