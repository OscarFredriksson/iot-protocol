#pragma once

#include "baseMsg.h"
#include <iostream>
#include <vector>

namespace mqtt {
enum ReturnCode {
  ConnectionAccepted = 0x00,
  UnnacceptableVersion,
  IdentifierRejected,
  ServerUnavailable,
  BadUsrNameOrPwd,
  NotAuthorized
};
class ConnackMsg : public BaseMsg {
private:
  ReturnCode returnCode;

public:
  ConnackMsg(ReturnCode returnCode);

  std::vector<char> serialize();
};
} // namespace mqtt