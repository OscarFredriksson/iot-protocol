#include "mqtt-messages/connMsg.h"
#include "mqtt-messages/connackMsg.h"
#include "socket.h"
#include <fstream>
#include <string>
#include <vector>

#include "broker.h"

int main() {
  const int port = 1883;

  mqtt::Broker broker(port);

  broker.start();

  return 0;
}