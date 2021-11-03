#include "httpserver.h"

HttpServer::HttpServer(const int port):
    httpConnection(port)
{

}

void HttpServer::addGetHandler(const std::string& url, std::function<HttpConnection::Response(void)> handler)
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

        HttpConnection::Request msg = httpConnection.receive();

        std::cout << msg.url << "\n";

        auto handler = getHandlers[msg.url];

        HttpConnection::Response response = handler();

        // const std::string html = "<body><h1>Hello World!</h1></body>";

        httpConnection.respond(response);
        httpConnection.close();
    }
}

