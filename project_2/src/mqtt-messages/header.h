#pragma once

#include <iostream>
#include <vector>

namespace mqtt {
enum MessageType {
  CONNECT = 1,
  CONNACK,
  PUBLISH,
  PUBACK,
  PUBREC,
  PUBREL,
  PUBCOMP,
  SUBSCRIBE,
  SUBACK,
  UNSUBSCRIBE,
  UNSUBACK,
  PINGREQ,
  PINGRESP,
  DISCONNECT
};

enum QosLevel {
  AtMostOnce = 0,
  AtLeastOnce,
  ExactlyOnce
};

class Header
{
private:
  MessageType messageType; 
  bool duplicate;
  QosLevel qosLevel;
  bool retain;
  int remainingLength;

public:
  Header() = default;

  Header(MessageType messageType, bool duplicate, QosLevel qosLevel, bool retain, int remainingLength);

  int deserialize(const std::vector<char>& msg);

  friend std::ostream& operator<<(std::ostream& os, const MessageType& rhs);
  friend std::ostream& operator<<(std::ostream& os, const QosLevel& rhs);
  friend std::ostream& operator<<(std::ostream& os, const Header& rhs);
};
}