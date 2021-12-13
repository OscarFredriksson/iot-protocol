#include <iostream>
#include <string>
#include <vector>

#include "header.h"

namespace mqtt {
class PublishMsg : public Header {
protected:
  int topicLength;
  std::string topic = "";
  uint16_t packetId;

public:
  int deserialize(std::vector<char> msg);

  std::string getTopic();

  friend std::ostream& operator<<(std::ostream& os, const PublishMsg& rhs);
};
} // namespace mqtt