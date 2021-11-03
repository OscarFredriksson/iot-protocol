#include "socket.h"
#include <map>

typedef std::map<std::string, std::string> HttpParamMap;

enum HttpStatusCode{
    OK,
    NOT_FOUND 
};
struct HttpRequest {
    HttpRequest(const std::string& type, const std::string& url, const HttpParamMap& params):
            type(type), url(url), params(params){}

    std::string type;
    std::string url;
    HttpParamMap params;
};

struct HttpResponse {
    HttpResponse(HttpStatusCode statusCode, const std::string& body):
        statusCode(statusCode), body(body) {}

    HttpStatusCode statusCode;
    std::string body;
};

class HttpConnection: public Socket 
{
public:
    HttpConnection(const int port);

    HttpRequest receive();

    void respond(HttpResponse response);

    void respond(HttpStatusCode statusCode, const std::string& body = "");

private:
    std::string getStatusCodeString(HttpStatusCode statusCode);

    std::vector<std::string> splitStr(const std::string& str, char delimiter);
};