#include "subMsg.h"

int mqtt::SubMsg::deserialize(const std::vector<char>& msg) {
  if (!Header::deserialize(msg))
    return 0;

  packetId = static_cast<int>((msg[2] << 8) | (msg[3] & 0x00ff));
  topicLength = static_cast<int>((msg[4] << 8) | (msg[5] & 0x00ff));

  mqtt::MsgIterator msgIt = msg.begin() + 6;

  mqtt::MsgIterator topicStartIt = msgIt;
  for (; msgIt < topicStartIt + topicLength; msgIt++) {
    topic += *msgIt;
  }

  return 1;
}