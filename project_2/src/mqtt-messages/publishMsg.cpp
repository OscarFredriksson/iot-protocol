#include "publishMsg.h"

std::ostream& mqtt::operator<<(std::ostream& os, const mqtt::PublishMsg& rhs) {
  os << static_cast<mqtt::Header>(rhs) << "\n";

  os << "----Publish Message---\n";
  os << "Topic Length: " << rhs.topicLength << rhs.delimiter;
  os << "Topic: " << rhs.topic << rhs.delimiter;

  return os;
}

int mqtt::PublishMsg::deserialize(std::vector<char> msg) {
  if (!Header::deserialize(msg))
    return -1;

  topicLength = static_cast<int>((msg[2] << 8) | (msg[3] & 0x00ff));

  MsgIterator msgIt = msg.begin() + 4;

  const auto topicStartIt = msgIt;

  for (; msgIt < topicStartIt + topicLength; msgIt++) {
    topic += *msgIt;
  }

  packetId = static_cast<uint16_t>((*msgIt << 8) | (*(msgIt + 1) & 0x00ff));

  return 1;
}

std::string mqtt::PublishMsg::getTopic() { return topic; }
