#pragma once

#include <iostream>
#include <vector>

#include "header.h"

namespace mqtt {
enum ReturnCode {
  ConnectionAccepted = 0x00,
  UnnacceptableVersion,
  IdentifierRejected,
  ServerUnavailable,
  BadUsrNameOrPwd,
  NotAuthorized
};
class ConnackMsg : public Header {
private:
  ReturnCode returnCode;

public:
  ConnackMsg(ReturnCode returnCode);

  std::vector<char> serialize();
};
} // namespace mqtt