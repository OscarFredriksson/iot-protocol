#include <string>
#include <vector>
#include "httpserver.h"

int main() 
{
    const int port = 8080;

    HttpServer server(port);

    server.addGetHandler("/", [](ParamMap urlParams){
        return HttpResponse(HttpStatusCode::OK, "hello world");
    });

    server.addGetHandler("/test", [](ParamMap urlParams){
        std::cout << "id: " << urlParams["id"] << '\n';

        return HttpResponse(HttpStatusCode::OK, "hello");
    });

    server.addPostHandler("/test", [](ParamMap urlParams, ParamMap bodyParams){
        
        std::cout << "id: " << bodyParams["id"] << "\n";

        return HttpResponse(HttpStatusCode::OK, "hello");
    });

    server.start();

    return 0;
}