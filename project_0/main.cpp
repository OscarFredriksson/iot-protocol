#include <string>
#include <vector>
#include "httpserver.h"

int main() 
{
    const int port = 8080;

    HttpServer server(port);

    server.addGetHandler("/", [](){
        std::cout << "handler works \n";

        return HttpConnection::Response(HttpConnection::OK, "hello world");
    });

    server.addGetHandler("/hello", [](){
        std::cout << "handler for different url!\n";

        return HttpConnection::Response(HttpConnection::OK, "hello");
    });

    server.start();

    return 0;
}