#include "subMsg.h"

uint16_t mqtt::SubMsg::getPacketId() { return packetId; }

int mqtt::SubMsg::getTopicLength() { return topicLength; }

std::string getTopic() { return topic; }

int mqtt::SubMsg::deserialize(const std::vector<char>& msg) {
  if (!Header::deserialize(msg))
    return 0;

  packetId = static_cast<uint16_t>((msg[2] << 8) | (msg[3] & 0x00ff));
  topicLength = static_cast<int>((msg[4] << 8) | (msg[5] & 0x00ff));

  mqtt::MsgIterator msgIt = msg.begin() + 6;

  mqtt::MsgIterator topicStartIt = msgIt;
  for (; msgIt < topicStartIt + topicLength; msgIt++) {
    topic += *msgIt;
  }

  return 1;
}

std::ostream& mqtt::operator<<(std::ostream& os, const mqtt::SubMsg& rhs) {
  os << static_cast<Header>(rhs) << "\n";

  os << "----Subscribe Message----\n";
  os << "Packet ID: " << rhs.packetId << rhs.delimiter;
  os << "Topic Length: " << rhs.topicLength << rhs.delimiter;
  os << "Topic: " << rhs.topic << rhs.delimiter;

  os << "\n";

  return os;
}