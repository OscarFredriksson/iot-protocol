#pragma once

#include <iostream>
#include <vector>

#include "header.h"

namespace mqtt {
class SubMsg : public Header {
private:
  int packetId;
  int topicLength;
  std::string topic = "";

public:
  int deserialize(const std::vector<char>& msg);
};
} // namespace mqtt