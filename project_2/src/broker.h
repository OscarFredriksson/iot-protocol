#include <set>
#include <unordered_map>
#include <vector>

#include "mqtt-messages/connAckMsg.h"
#include "mqtt-messages/connMsg.h"
#include "mqtt-messages/header.h"
#include "mqtt-messages/publishMsg.h"
#include "mqtt-messages/subAckMsg.h"
#include "mqtt-messages/subMsg.h"
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

  MessageType getMessageType(const std::vector<char>& msg);

  int handleConnect(const std::vector<char>& msg, Socket* socket);
  int handlePingReq(const std::vector<char>& msg, Socket* socket);
  int handleSubscribe(const std::vector<char>& msg, Socket* socket);
  int handleUnsubscribe(const std::vector<char>& msg, Socket* socket);
  int handlePublish(const std::vector<char>& msg, Socket* socket);
  int handleDisconnect(const std::vector<char>& msg, Socket* socket);
};
} // namespace mqtt
