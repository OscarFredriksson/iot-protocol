#include "subAckMsg.h"

mqtt::SubAckMsg::SubAckMsg(uint16_t packetId, SubReturnCode returnCode)
    : packetId(packetId), returnCode(returnCode) {}

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
  os << "Packet ID: " << rhs.packetId << rhs.delimiter;
  os << "Return Code: " << rhs.returnCode << "\n";
  return os;
}
