#include <memory>
#include <set>
#include <unordered_map>
#include <vector>

#include "mqtt-messages/connAckMsg.h"
#include "mqtt-messages/connMsg.h"
#include "mqtt-messages/header.h"
#include "mqtt-messages/publishMsg.h"
#include "mqtt-messages/subAckMsg.h"
#include "mqtt-messages/subMsg.h"
#include "mqtt-messages/unsubMsg.h"
#include "socket.h"

namespace mqtt {
class Broker {

public:
  Broker(const int port);

  int start();

private:
  const int port;
  std::unordered_map<std::string, std::set<Socket*>> subscribers;

  int handleClient(Socket* socket);

  int handleConnect(const mqtt::Header& header,
                    const std::vector<char>& remainingBytes, Socket* socket);
  int handlePingReq(const mqtt::Header& header, Socket* socket);
  int handleSubscribe(const mqtt::Header& header,
                      const std::vector<char>& remainingBytes, Socket* socket);
  int handleUnsubscribe(const mqtt::Header& header,
                        const std::vector<char>& remainingBytes,
                        Socket* socket);
  int handlePublish(const mqtt::Header& header,
                    const std::vector<char>& remainingBytes, Socket* socket);
  int handleDisconnect(const mqtt::Header& header, Socket* socket);
};
} // namespace mqtt
