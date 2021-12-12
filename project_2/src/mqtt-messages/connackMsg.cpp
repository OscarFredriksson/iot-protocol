#include "connackMsg.h"

mqtt::ConnackMsg::ConnackMsg(mqtt::ReturnCode returnCode)
    : returnCode(returnCode), Header(CONNACK) {}

std::vector<char> mqtt::ConnackMsg::serialize() {
  std::vector<char> msg = Header::serialize();

  msg.push_back(char(0x02));
  msg.push_back(char(0x00));

  msg.push_back(char(returnCode));

  return msg;
}