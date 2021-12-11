#pragma once

#include <iostream>
#include <string>
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

enum QosLevel { AtMostOnce = 0x00, AtLeastOnce = 0x01, ExactlyOnce = 0x02 };

using MsgIterator = std::vector<char>::const_iterator;

class BaseMsg {
protected:
  MessageType messageType;
  bool duplicate;
  QosLevel qosLevel;
  bool retain;
  uint8_t remainingLength;

  const std::string delimiter = "  ";

public:
  BaseMsg() = default;

  BaseMsg(MessageType messageType, bool duplicate = false,
          QosLevel qosLevel = AtMostOnce, bool retain = false,
          int remainingLength = 0);

  int deserialize(const std::vector<char>& msg);

  std::vector<char> serialize();

  friend std::ostream& operator<<(std::ostream& os, const MessageType& rhs);
  friend std::ostream& operator<<(std::ostream& os, const QosLevel& rhs);
  friend std::ostream& operator<<(std::ostream& os, const BaseMsg& rhs);
};
} // namespace mqtt