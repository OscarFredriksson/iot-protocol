#include <string>
#include <vector>
#include <fstream>
#include "socket.h"
#include "mqttmessage.h"

int main() 
{
    const int port = 1883;

    Socket socket(port);

    if(!socket.connect()){
        std::cout << "failed to connect\n";
        return 0;
    }

    std::vector<char> msg = socket.receive();

    if(msg.empty()) return 0;

    MqttMessage mqttMessage;

    mqttMessage.deserialize(msg);

    std::cout << mqttMessage << "\n";

    return 0;
}