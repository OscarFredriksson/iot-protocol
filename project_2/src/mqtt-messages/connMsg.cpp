#include "connMsg.h"

int mqtt::ConnMsg::deserialize(const std::vector<char>& msg){

  if(!header.deserialize(msg)) return -1;

  nameLength = static_cast<int>((msg[2] << 8) | (msg[3] & 0x00ff));

  std::vector<char>::const_iterator byteIt = msg.begin() + 4;

  const auto protocolNameStartIt = byteIt;

  for(; byteIt < protocolNameStartIt + 4; byteIt++){
    protocolName += *byteIt;
  }

  version = *byteIt++;

  if((*byteIt++ & 0b00000001)){
    std::cerr << "ERROR: Corrupt message, reserved flag is not false\n";
    return -1;
  }

  keepAlive = static_cast<int>((*byteIt << 8) | (*(byteIt+1) & 0x00ff));

  byteIt += 2;


  clientIdLength = static_cast<int>((*byteIt << 8) | (*(byteIt+1) & 0x00ff));
  byteIt += 2;

  const auto clientIdStartIt = byteIt;
  for(; byteIt < clientIdStartIt + clientIdLength; byteIt++){
    clientId += *byteIt;
  }

  return 1;
}

std::ostream& mqtt::operator<<(std::ostream& os, const mqtt::ConnMsg& rhs)
{
  std::string delimiter = "  ";

  os << "----Connect Message----" << "\n";
  os << "Protocol Name Length: " << rhs.nameLength << delimiter;
  os << "Protocol Name: " << rhs.protocolName << delimiter;
  os << "Version: " << rhs.version << delimiter;
  os << "Keep Alive: " << rhs.keepAlive << "\n";
  os << "Client ID Length: " << rhs.clientIdLength << delimiter;
  os << "Client ID: " << rhs.clientId << "\n";

  return os;
}