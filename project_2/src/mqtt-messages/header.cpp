#include "header.h"

mqtt::Header::Header(
  mqtt::MessageType messageType, 
  bool duplicate = 0, 
  mqtt::QosLevel qosLevel = AtMostOnce, 
  bool retain = 0, 
  int remainingLength = 0):
  messageType(messageType), 
  duplicate(duplicate), 
  qosLevel(qosLevel), 
  retain(retain), 
  remainingLength(remainingLength)
{

}

int mqtt::Header::deserialize(const std::vector<char>& msg) 
{
  messageType = static_cast<MessageType>((msg[0] & 0b11110000) >> 4);
  duplicate = static_cast<bool>((msg[0] & 0b00001000) >> 3);
  qosLevel = static_cast<QosLevel>((msg[0] & 0b00000110) >> 1);
  retain = static_cast<bool>(msg[0] & 0b00000001);
  remainingLength = static_cast<int>(msg[1]);

  return 1;
}

std::ostream& operator<<(std::ostream& os, const mqtt::MessageType& rhs)
{
  os << int(rhs) << " (";

  switch(rhs){
    case mqtt::CONNECT: 
      os << "CONNECT";
      break;
    case mqtt::CONNACK: 
      os << "CONNACK";
      break;
    case mqtt::PUBLISH: 
      os << "PUBLISH";
      break;
    case mqtt::PUBACK: 
      os << "PUBACK";
      break;
    case mqtt::PUBREC: 
      os << "PUBREC";
      break;
    case mqtt::PUBREL: 
      os << "PUBREL";
      break;
    case mqtt::PUBCOMP: 
      os << "PUBCOMP";
      break;
    case mqtt::SUBSCRIBE: 
      os << "SUBSCRIBE";
      break;
    case mqtt::SUBACK: 
      os << "SUBACK";
      break;
    case mqtt::UNSUBSCRIBE: 
      os << "UNSUBSCRIBE";
      break;
    case mqtt::UNSUBACK: 
      os << "UNSUBACK";
      break;
    case mqtt::PINGREQ: 
      os << "PINGREQ";
      break;
    case mqtt::PINGRESP: 
      os << "PINGRESP";
      break;
    case mqtt::DISCONNECT: 
      os << "DISCONNECT";
      break;
  }

  os << ")";

  return os;
}

std::ostream& operator<<(std::ostream& os, const mqtt::QosLevel& rhs)
{
  os << int(rhs) << " (";

  switch(rhs){
    case mqtt::AtMostOnce:
      os << "At Most Once";
      break;
    case mqtt::AtLeastOnce:
      os << "At Least Once";
      break;
    case mqtt::ExactlyOnce:
      os << "Exactly Once";
      break;
  }

  os << ")";

  return os;
}


std::ostream& mqtt::operator<<(std::ostream& os, const mqtt::Header& rhs)
{
  std::string delimiter = "  ";

  os << "----Header----\n";
  os << "Message Type: " << rhs.messageType << delimiter;
  os << "Duplicate: " << rhs.duplicate << delimiter;
  os << "QoS Level: " << rhs.qosLevel << delimiter;
  os << "Retain: " << rhs.retain << "\n";
  os << "Remaining length: " << rhs.remainingLength << "\n";

  return os;
}