#pragma once

#include <iostream>
#include <vector>

#include "header.h"

namespace mqtt {
class SubMsg : public Header {
protected:
  uint16_t packetId;
  int topicLength;
  std::string topic = "";

public:
  uint16_t getPacketId();

  int getTopicLength();

  std::string getTopic();

  int deserialize(const std::vector<char>& msg);

  friend std::ostream& operator<<(std::ostream& os, const SubMsg& rhs);
};
} // namespace mqtt