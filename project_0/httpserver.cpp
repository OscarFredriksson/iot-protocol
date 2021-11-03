#include "httpserver.h"

HttpServer::HttpServer(const int port):
    httpConnection(port)
{

}

void HttpServer::addGetHandler(const std::string& url, std::function<HttpResponse(HttpParamMap)> handler)
{
    getHandlers.insert({url, handler});
}

void HttpServer::start() 
{
    while(true){ 
        if(!httpConnection.connect()){
            std::cout << "failed to connect\n";
            return;
        }

        HttpRequest msg = httpConnection.receive();

        std::cout << msg.url << "\n";

        auto handler = getHandlers[msg.url];

        HttpResponse response = handler(msg.params);

        httpConnection.respond(response);
        httpConnection.close();
    }
}

