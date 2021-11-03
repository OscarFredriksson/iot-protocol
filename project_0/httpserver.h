#include "httpconnection.h"
#include <map>

class HttpServer
{
public:
    HttpServer(const int port);

    void addGetHandler(const std::string& url, std::function<HttpConnection::Response(void)> handler);

    void start();

private:
    HttpConnection httpConnection;

    std::map<std::string, std::function<HttpConnection::Response(void)>> getHandlers;
};