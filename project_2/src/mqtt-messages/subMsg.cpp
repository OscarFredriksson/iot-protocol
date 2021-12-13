#include "subMsg.h"

mqtt::SubMsg::SubMsg(const mqtt::Header& header) : mqtt::Header(header) {}

uint16_t mqtt::SubMsg::getPacketId() { return packetId; }

int mqtt::SubMsg::getTopicLength() { return topicLength; }

std::string mqtt::SubMsg::getTopic() { return topic; }

int mqtt::SubMsg::deserialize(const std::vector<char>& remainingBytes) {
  // if (!Header::deserialize(msg))
  //   return 0;

  packetId = static_cast<uint16_t>((remainingBytes[0] << 8) |
                                   (remainingBytes[1] & 0x00ff));
  topicLength =
      static_cast<int>((remainingBytes[2] << 8) | (remainingBytes[3] & 0x00ff));

  mqtt::MsgIterator msgIt = remainingBytes.begin() + 4;

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