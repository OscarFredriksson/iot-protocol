#include "subAckMsg.h"

mqtt::SubAckMsg::SubAckMsg(uint16_t packetId, mqtt::SubReturnCode returnCode)
    : packetId(packetId), returnCode(returnCode), Header(mqtt::SUBACK) {}

std::vector<char> mqtt::SubAckMsg::serialize() {
  std::vector<char> msg = mqtt::Header::serialize();

  msg.push_back(char(3));
  msg.push_back(char(packetId >> 8));
  msg.push_back(char(packetId & 0xff));
  msg.push_back(char(returnCode));

  return msg;
}

std::ostream& mqtt::operator<<(std::ostream& os,
                               const mqtt::SubReturnCode& rhs) {
  os << rhs << " (";

  switch (rhs) {
  case mqtt::SuccessQoS0:
    os << "Success QoS 0";
    break;
  case mqtt::SuccessQoS1:
    os << "Success QoS 1";
    break;
  case mqtt::SuccessQoS2:
    os << "Success QoS 2";
    break;
  case mqtt::Failure:
    os << "Failure";
    break;
  }

  os << ")";

  return os;
}

std::ostream& mqtt::operator<<(std::ostream& os, const mqtt::SubAckMsg& rhs) {
  os << static_cast<Header>(rhs) << "\n";

  os << "----Subscribe Ack Message----\n";
  os << "Packet Id: " << rhs.packetId << rhs.delimiter;
  // os << "Return Code: " << rhs.returnCode << "\n";
  return os;
}
