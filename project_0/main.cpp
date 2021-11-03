#include <string>
#include <vector>
#include "httpserver.h"

int main() 
{
    const int port = 8080;

    HttpServer server(port);

    server.addGetHandler("/", [](HttpParamMap params){
        return HttpResponse(HttpStatusCode::OK, "hello world");
    });

    server.addGetHandler("/test", [](HttpParamMap params){
        std::cout << "id: " << params["id"] << '\n';

        return HttpResponse(HttpStatusCode::OK, "hello");
    });

    server.start();

    return 0;
}