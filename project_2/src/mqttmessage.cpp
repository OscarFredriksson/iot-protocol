#include "mqttmessage.h"

std::ostream& operator<<(std::ostream& os, const MqttMessage& rhs)
{
  os << "Message Type: " << rhs.messageType << "\n";
  os << "Duplicate: " << rhs.duplicate << "\n";
  os << "QoS Level: " << rhs.qosLevel << "\n";
  os << "Retain: " << rhs.retain << "\n";

  return os;
}

int MqttMessage::deserialize(const std::vector<char>& msg) 
{
  messageType = static_cast<MqttMessageType>((msg[0] & 0b11110000) >> 4);
  duplicate = static_cast<bool>((msg[0] & 0b00001000) >> 3);
  qosLevel = static_cast<MqttQosLevel>((msg[0] & 0b00000110) >> 1);
  retain = static_cast<bool>(msg[0] & 0b00000001);

  return 1;
}