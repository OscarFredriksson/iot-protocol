#include "publishMsg.h"

std::ostream& mqtt::operator<<(std::ostream& os, const mqtt::PublishMsg& rhs) {
  os << static_cast<mqtt::BaseMsg>(rhs) << "\n";

  os << "----Publish Message---\n";
  os << "Topic Name Length: " << rhs.topicNameLength << rhs.delimiter;
  os << "Topic Name: " << rhs.topicName << rhs.delimiter;

  return os;
}

int mqtt::PublishMsg::deserialize(std::vector<char> msg) {
  if (!BaseMsg::deserialize(msg))
    return -1;

  topicNameLength = static_cast<int>((msg[2] << 8) | (msg[3] & 0x00ff));

  MsgIterator msgIt = msg.begin() + 4;

  const auto topicNameStartIt = msgIt;

  for (; msgIt < topicNameStartIt + topicNameLength; msgIt++) {
    topicName += *msgIt;
  }

  return 1;
}
