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

    HttpConnection(const int port);

    Request receive();

    void respond(StatusCode statusCode, const std::string& body = "");

private:
    std::string getStatusCodeString(StatusCode statusCode);

    std::vector<std::string> splitStr(const std::string& str, char delimiter);
};