#include <iostream>
#include <vector>

#include "header.h"

namespace mqtt {
class UnsubMsg : public Header {
protected:
  uint16_t packetId;
  int topicLength;
  std::string topic = "";

public:
  UnsubMsg(const Header& header);

  std::string getTopic();

  int deserialize(const std::vector<char>& remainingBytes);

  friend std::ostream& operator<<(std::ostream& os, const UnsubMsg& rhs);
};
} // namespace mqtt