#include <iostream>
#include <vector>

enum MqttMessageType {
  CONNECT = 1,
  CONNACK,
  PUBLISH,
  PUBACK,
  PUBREC,
  PUBREL,
  PUBCOMP,
  SUBSCRIBE,
  SUBACK,
  UNSUBSCRIBE,
  UNSUBACK,
  PINGREQ,
  PINGRESP,
  DISCONNECT
};

enum MqttQosLevel {
  AtMostOnce = 0,
  AtLeastOnce,
  ExactlyOnce
};

class MqttMessage
{
public:
  MqttMessageType messageType; 
  bool duplicate;
  MqttQosLevel qosLevel;
  bool retain;

  int deserialize(const std::vector<char>& msg);

  friend std::ostream& operator<<(std::ostream& os, const MqttMessage& rhs);
};