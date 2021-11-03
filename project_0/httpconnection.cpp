#include "httpconnection.h"

HttpConnection::HttpConnection(const int port):
    Socket(port)
{

}

HttpRequest HttpConnection::receive() {
    std::string msg = Socket::receive();
    
    std::vector<std::string> msgSections = splitStr(msg, ' ');

    const std::string type = msgSections[0];
    
    auto  split_url = splitStr(msgSections[1], '?');
    const std::string url = split_url[0];

    auto params = std::map<std::string, std::string>();

    if(split_url.size() > 1){
        auto split_params = splitStr(split_url[1], '&');
        for(int i = 0; i < split_params.size(); i++){
            auto split_param = splitStr(split_params[i], '=');

            params.insert(std::make_pair(split_param[0], split_param[1]));
        }
    }

    HttpRequest request(type, url, params);

    return request;
}

void HttpConnection::respond(HttpStatusCode statusCode, const std::string& body){
    respond(HttpResponse(statusCode, body));
}

void HttpConnection::respond(HttpResponse response) {
    Socket::respond(
        "HTTP/1.1 " + 
        getStatusCodeString(response.statusCode) + 
        " \r\n\r\n" + 
        response.body + 
        "\r\n");
}

std::string HttpConnection::getStatusCodeString(HttpStatusCode statusCode) {
    switch(statusCode){
        case HttpStatusCode::OK:
            return "200 OK";
        default:
        case HttpStatusCode::NOT_FOUND:
            return "404 Not Found";
    }
}

std::vector<std::string> HttpConnection::splitStr(const std::string& str, char delimiter) 
{
    size_t start = 0;
    size_t end;

    std::vector<std::string> ret;

    for(;(end = str.find(delimiter, start)) != std::string::npos; start = end + 1) 
    {
        std::string part = str.substr(start, end - start);
        ret.push_back(part);
    }

    ret.push_back(str.substr(start));
    return ret;
}