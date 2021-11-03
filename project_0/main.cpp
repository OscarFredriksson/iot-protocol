#include <string>
#include <vector>
#include "socket.h"

std::vector<std::string> split(std::string str, char delimiter) 
{
    size_t start = 0;
    size_t end;

    std::vector<std::string> ret;

    for(;(end = str.find(delimiter, start)) != std::string::npos; start = end + 1) 
    {
        std::string part = str.substr(start, end - start);
        ret.push_back(part);
    }

    ret.push_back(str.substr(start));
    return ret;
}

int main() 
{
    const int port = 8080;

    Socket socket(port);

    

    while(true){ 
        if(!socket.connect()){
            std::cout << "failed to connect\n";
            return 1;
        }

        std::string msg = socket.receive();
        std::cout << msg << "\n";

        const std::string html = "<body><h1>Hello World!</h1></body>";

        socket.respond("HTTP/1.1 200 OK \r\n\r\n"+html+"\r\n");
        socket.close();
    }

    return 0;
}