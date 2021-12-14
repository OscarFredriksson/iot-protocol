#include "broker.h"

int main() {
  const int port = 1883;
  mqtt::Broker broker(port);
  roker.start();
  return 0;
}