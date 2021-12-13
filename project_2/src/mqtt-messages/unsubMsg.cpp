#include "unsubMsg.h"

mqtt::UnsubMsg::UnsubMsg(const Header& header) : mqtt::Header(header) {}

std::string mqtt::UnsubMsg::getTopic() { return topic; }

int mqtt::UnsubMsg::deserialize(const std::vector<char>& remainingBytes) {

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

std::ostream& mqtt::operator<<(std::ostream& os, const mqtt::UnsubMsg& rhs) {
  os << static_cast<Header>(rhs) << "\n";

  os << "----Unsubscribe Message----\n";
  os << "Packet ID: " << rhs.packetId << rhs.delimiter;
  os << "Topic Length: " << rhs.topicLength << rhs.delimiter;
  os << "Topic: " << rhs.topic << rhs.delimiter;

  os << "\n";

  return os;
}