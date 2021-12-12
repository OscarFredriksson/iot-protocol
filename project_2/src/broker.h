#include <vector>

#include "mqtt-messages/connMsg.h"
#include "mqtt-messages/connackMsg.h"
#include "mqtt-messages/publishMsg.h"

#include "socket.h"

namespace mqtt {
class Broker {

public:
  Broker(const int port);

  int start();

private:
  Socket socket;

  MessageType getMessageType(const std::vector<char>& msg);

  int handleConnect(const std::vector<char>& msg);
  int handlePublish(const std::vector<char>& msg);
  int handlePingReq(const std::vector<char>& msg);
  int handleSubscribe(const std::vector<char>& msg);
  int handleUnsubscribe(const std::vector<char>& msg);
  int handleDisconnect(const std::vector<char>& msg);
};
} // namespace mqtt
