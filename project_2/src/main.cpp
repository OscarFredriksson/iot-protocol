#include <string>
#include <vector>
#include <fstream>
#include "socket.h"
#include "mqtt-messages/header.h"
#include "mqtt-messages/connMsg.h"

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

    mqtt::ConnMsg connMsg;

    if(!connMsg.deserialize(msg)) {
        std::cerr << "Failed to deserialize Connection Message\n";
        return 0;
    }

    std::cout << connMsg << "\n";

    return 0;
}