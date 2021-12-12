#include "connMsg.h"

int mqtt::ConnMsg::deserialize(const std::vector<char>& msg) {
  if (!Header::deserialize(msg))
    return 0;

  nameLength = static_cast<int>((msg[2] << 8) | (msg[3] & 0x00ff));

  MsgIterator msgIt = msg.begin() + 4;

  const auto protocolNameStartIt = msgIt;

  for (; msgIt < protocolNameStartIt + 4; msgIt++) {
    protocolName += *msgIt;
  }

  version = *msgIt++;

  if ((*msgIt++ & 0b00000001)) {
    std::cerr << "ERROR: Corrupt message, reserved flag is not false\n";
    return 0;
  }

  keepAlive = static_cast<int>((*msgIt << 8) | (*(msgIt + 1) & 0x00ff));

  msgIt += 2;

  clientIdLength = static_cast<int>((*msgIt << 8) | (*(msgIt + 1) & 0x00ff));
  msgIt += 2;

  const auto clientIdStartIt = msgIt;
  for (; msgIt < clientIdStartIt + clientIdLength; msgIt++) {
    clientId += *msgIt;
  }

  return 1;
}

std::ostream& mqtt::operator<<(std::ostream& os, const mqtt::ConnMsg& rhs) {
  os << static_cast<Header>(rhs) << "\n";

  os << "----Connect Message----\n";
  os << "Protocol Name Length: " << rhs.nameLength << rhs.delimiter;
  os << "Protocol Name: " << rhs.protocolName << rhs.delimiter;
  os << "Version: " << rhs.version << rhs.delimiter;
  os << "Keep Alive: " << rhs.keepAlive << "\n";
  os << "Client ID Length: " << rhs.clientIdLength << rhs.delimiter;
  os << "Client ID: " << rhs.clientId << "\n";

  return os;
}