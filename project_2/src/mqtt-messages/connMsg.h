#include <iostream>
#include <string>
#include <vector>

#include "header.h"

namespace mqtt {
class ConnMsg{
public:

  Header header;

  int remainingLength;
  int nameLength;
  std::string protocolName = "";
  int version;

  int keepAlive;

  int clientIdLength;
  std::string clientId = "";

  int deserialize(const std::vector<char>& msg);

  friend std::ostream& operator<<(std::ostream& os, const ConnMsg& rhs);
};
}