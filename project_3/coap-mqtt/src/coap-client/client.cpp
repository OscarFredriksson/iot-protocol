#include "client.h"

coap::Client::Client(const std::string& hostname, int port)
    : socket(hostname, port) {}

int coap::Client::connect() { return socket.connect(); }

void coap::Client::send(CoapMessage request) {
  socket.send(request.serialize());
}

CoapMessage coap::Client::getResponse() {
  CoapMessage response;

  std::vector<char> raw_response = socket.receive();

  if (!raw_response.empty())
    response.deserialize(raw_response);

  return response;
}