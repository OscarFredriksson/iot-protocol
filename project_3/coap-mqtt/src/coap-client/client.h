#pragma once

#include "coapmessage.h"
#include "socket.h"

namespace coap {
class Client {
private:
  Socket socket;

public:
  Client(const std::string& hostname, int port);

  int connect();

  void send(CoapMessage request);

  CoapMessage getResponse();
};
} // namespace coap