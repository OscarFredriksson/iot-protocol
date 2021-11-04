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
        
        return HttpResponse(HttpStatusCode::OK, "hello, id: " + urlParams["id"]);
    });

    server.addPostHandler("/test", [](ParamMap urlParams, ParamMap bodyParams){
        
        return HttpResponse(HttpStatusCode::OK, "id: " + bodyParams["id"]);
    });

    server.start();

    return 0;
}