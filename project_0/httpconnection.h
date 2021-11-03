#include "socket.h"

class HttpConnection: public Socket 
{
public:
    enum StatusCode{
        OK,
        NOT_FOUND 
    };

    struct Request {
        Request(const std::string& type, const std::string& url):
            type(type), url(url){}

        std::string type;
        std::string url;
    };

    struct Response {
        Response(StatusCode statusCode, const std::string& body):
            statusCode(statusCode), body(body) {}

        StatusCode statusCode;
        std::string body;
    };

    HttpConnection(const int port);

    Request receive();

    void respond(HttpConnection::Response response);

    void respond(StatusCode statusCode, const std::string& body = "");

private:
    std::string getStatusCodeString(StatusCode statusCode);

    std::vector<std::string> splitStr(const std::string& str, char delimiter);
};