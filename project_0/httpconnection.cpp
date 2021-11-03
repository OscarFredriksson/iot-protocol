#include "httpconnection.h"

HttpConnection::HttpConnection(const int port):
    Socket(port)
{

}

HttpConnection::Request HttpConnection::receive() {
    std::string msg = Socket::receive();
    
    std::vector<std::string> msgSections = splitStr(msg, ' ');

    Request request(msgSections[0], msgSections[1]);

    return request;
}

void HttpConnection::respond(HttpConnection::StatusCode statusCode, const std::string& body){
    respond(HttpConnection::Response(statusCode, body));
}

void HttpConnection::respond(HttpConnection::Response response) {
    Socket::respond("HTTP/1.1 " + getStatusCodeString(response.statusCode) + " \r\n\r\n"+ response.body + "\r\n");
}

std::string HttpConnection::getStatusCodeString(HttpConnection::StatusCode statusCode) {
    switch(statusCode){
        case HttpConnection::StatusCode::OK:
            return "200 OK";
        case HttpConnection::StatusCode::NOT_FOUND:
            return "404 Not Found";
        default:
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