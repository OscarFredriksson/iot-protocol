#include "socket.h"
#include <unordered_map>

typedef std::unordered_map<std::string, std::string> ParamMap;

enum HttpStatusCode{
    OK, //200
    NOT_FOUND, //404
    METHOD_NOT_ALLOWED //405 
};

enum HttpRequestType{
    GET,
    POST,
    UNKOWN
};
struct HttpRequest {
    HttpRequestType type;
    std::string url;
    ParamMap urlParams;
    ParamMap headers;
    ParamMap bodyParams;
};

struct HttpResponse {
    HttpResponse(){}

    HttpResponse(HttpStatusCode statusCode, const std::string& body = ""):
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

    HttpRequestType parseRequestType(const std::string& typeStr);

    ParamMap parseHeaders(const std::string& msg);

    ParamMap parseURLEncodedBody(const std::string& msg);

    ParamMap parseParamStr(const std::string& paramStr);

    std::vector<std::string> splitStr(const std::string& str, const std::string& delimiter);
};