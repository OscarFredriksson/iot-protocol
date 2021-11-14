#include <string>
#include <vector>
#include <fstream>
#include "socket.h"
#include "coapmessage.h"

bool isNumber(const std::string &str) 
{
    for(auto c: str) {
        if(!std::isdigit(c))
            return false;
    }

    return true;
}

CoapCode userInputGetCode() 
{
    
    std::cout << "Type (1) for GET, (2) for POST, (3) for PUT or (4) for DELETE:\n";

    while(true) 
    {
        std::string input;
        std::getline(std::cin, input);
 
        if(input == "1") return CoapCode::GET;
        else if(input == "2") return CoapCode::POST;
        else if(input == "3") return CoapCode::PUT;
        else if(input == "4") return CoapCode::DELETE;
        else std::cout << "Invalid Input, try again:\n";
    }
}

uint16_t userInputGetMsgId() 
{
    std::cout << "Type an id for your message (numbers only, 0 to 65535):\n";

    while(true) 
    {
        std::string input;
        std::getline(std::cin, input);
        
        if(!isNumber(input)){
            std::cout << "Invalid input, needs to be a number.\n";
            std::cout << "Try again:\n";
            continue;
        } else {
            int input_num = std::stoi(input);

            if(input_num < 0 || input_num > 65535) {
                std::cout << "Invalid input, needs to be a number between 0 and 65535.\n";
                std::cout << "Try again:\n";
                continue;
            }

            return static_cast<uint16_t>(input_num);
        }

    }
}

std::string userInputGetPath() 
{
    std::cout << "Type a path for your request:\n";

    std::string input;
    std::getline(std::cin, input);
        
    return input;
}

int main() 
{
    const std::string hostname = "coap.me";
    const int port = 5683;

    Socket socket(hostname, port);

    CoapCode code = userInputGetCode();    

    uint16_t messageId = userInputGetMsgId();

    std::string path = userInputGetPath();

    CoapMessage msg(code, messageId, path);

    std::cout << msg << "\n";

    if(socket.connect() <= 0)
        std::cout << "Failed to connect to " << hostname << "\n";

    socket.send(msg.serialize());

    std::cout << "Message Response:\n";
    std::cout << socket.receive() << "\n";

    return 0;
}