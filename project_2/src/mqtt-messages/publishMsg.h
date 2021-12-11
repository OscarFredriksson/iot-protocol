#include <iostream>
#include <string>
#include <vector>

#include "baseMsg.h"

namespace mqtt {
class PublishMsg : public BaseMsg {
protected:
  int topicNameLength;
  std::string topicName = "";

public:
  int deserialize(std::vector<char> msg);

  friend std::ostream& operator<<(std::ostream& os, const PublishMsg& rhs);
};
} // namespace mqtt