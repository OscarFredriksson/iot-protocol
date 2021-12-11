#include "connackMsg.h"

mqtt::ConnackMsg::ConnackMsg(mqtt::ReturnCode returnCode)
    : returnCode(returnCode), BaseMsg(CONNACK) {}

std::vector<char> mqtt::ConnackMsg::serialize() {
  std::vector<char> msg = BaseMsg::serialize();

  msg.push_back(char(0x02));
  msg.push_back(char(0x00));

  msg.push_back(char(returnCode));

  return msg;
}