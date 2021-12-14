#include "broker.h"

int main() {
  const int port = 1883;
  mqtt::Broker broker(port);
  broker.start();
  return 0;
}