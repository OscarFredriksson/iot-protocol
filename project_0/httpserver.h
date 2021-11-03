#include "httpconnection.h"
#include <map>

class HttpServer
{
public:
    HttpServer(const int port);

    void addGetHandler(const std::string& url, std::function<HttpResponse(HttpParamMap)> handler);

    void start();

private:
    HttpConnection httpConnection;

    std::map<std::string, std::function<HttpResponse(HttpParamMap)>> getHandlers;
};