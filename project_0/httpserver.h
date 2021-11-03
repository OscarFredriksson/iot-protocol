#include "httpconnection.h"
#include <map>

class HttpServer
{
public:
    HttpServer(const int port);

    void addGetHandler(const std::string& url, std::function<HttpResponse(ParamMap)> handler);

    void addPostHandler(const std::string&url, std::function<HttpResponse(ParamMap, ParamMap)> handler);

    void start();

private:
    HttpConnection httpConnection;

    std::map<std::string, std::function<HttpResponse(ParamMap)>> getHandlers;
    std::map<std::string, std::function<HttpResponse(ParamMap, ParamMap)>> postHandlers;
};