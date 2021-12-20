#include "client.h"

coap::Client::Client(const std::string& hostname, int port)
    : socket(hostname, port) {}

int coap::Client::connect() { return socket.connect(); }

void coap::Client::send(CoapMessage request) {
  socket.send(request.serialize());
}

CoapMessage coap::Client::getResponse() {
  CoapMessage response;
  response.deserialize(socket.receive());

  return response;
}