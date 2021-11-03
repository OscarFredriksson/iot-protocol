#include <string>
#include <vector>
#include "httpconnection.h"

int main() 
{
    const int port = 8080;

    HttpConnection http(port);

    while(true){ 
        if(!http.connect()){
            std::cout << "failed to connect\n";
            return 1;
        }

        HttpConnection::Request msg = http.receive();
        std::cout << msg.type << " " << msg.url << "\n";

        const std::string html = "<body><h1>Hello World!</h1></body>";

        http.respond(HttpConnection::OK, html);
        http.close();
    }

    return 0;
}