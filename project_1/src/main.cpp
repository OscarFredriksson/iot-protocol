#include <string>
#include <vector>
#include <fstream>
#include "socket.h"

int main() 
{
    const std::string hostname = "coap.me";
    const int port = 5683;

    Socket socket(hostname, port);

    std::string msg = {
        0x40,
        0x01, 
        0x04, 
        static_cast<char>(0xd2),  
        static_cast<char>(0xb4),
        0x74, 
        0x65, 
        0x73, 
        0x74,
    };

    if(socket.connect() <= 0)
        std::cout << "Failed to connect to " << hostname << "\n";

    socket.send(msg);
    std::cout << socket.receive() << "\n";

    return 0;
}