#include "httpconnection.h"

HttpConnection::HttpConnection(const int port):
    Socket(port)
{

}

HttpRequest HttpConnection::receive() {
    std::string msg = Socket::receive();

    std::cout << msg << "\n";

    auto split_msg = splitStr(msg, " ");

    HttpRequest request;

    request.type = parseRequestType(split_msg[0]);
    
    request.headers = parseHeaders(msg);

    if(request.headers["Content-Type"] == "application/x-www-form-urlencoded"){
        request.bodyParams = parseURLEncodedBody(msg);
    }

    auto split_url = splitStr(split_msg[1], "?");
    request.url = split_url[0]; 

    if(split_url.size() > 1) request.urlParams = parseParamStr(split_url[1]);

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
        case HttpStatusCode::METHOD_NOT_ALLOWED:
            return "405 Method Not Allowed";
        default:
        case HttpStatusCode::NOT_FOUND:
            return "404 Not Found";
    }
}

HttpRequestType HttpConnection::parseRequestType(const std::string& typeStr) {
    if      (typeStr == "GET")      return HttpRequestType::GET;
    else if (typeStr == "POST")     return HttpRequestType::POST;
    else if (typeStr == "PUT")      return HttpRequestType::PUT;
    else if (typeStr == "DELETE")   return HttpRequestType::DELETE;
    
    return HttpRequestType::UNKOWN;
}

ParamMap HttpConnection::parseHeaders(const std::string& msg) {
    auto params = ParamMap();

    auto rows = splitStr(msg, "\n");

    for(int i = 1; (i < rows.size() && rows[i] != "\r"); i++){        
        auto split_row = splitStr(rows[i], ": ");
        
        std::string param_value = split_row[1];

        if(!param_value.empty() && param_value[param_value.size() - 1] == '\r'){
            param_value.erase(param_value.size() - 1);
        }
        params.insert(std::make_pair(split_row[0], param_value));
    }

    return params;
}

ParamMap HttpConnection::parseURLEncodedBody(const std::string& msg) {
    std::string body = msg.substr(msg.find_last_of("\r\n") + 1); 

    return parseParamStr(body);
}

ParamMap HttpConnection::parseParamStr(const std::string& paramStr) {
    auto params = ParamMap();

    auto split_params = splitStr(paramStr, "&");
    
    for(int i = 0; i < split_params.size(); i++){
        auto split_param = splitStr(split_params[i], "=");

        params.insert(std::make_pair(split_param[0], split_param[1]));
    }

    return params;
}

std::vector<std::string> HttpConnection::splitStr(const std::string& str, const std::string& delimiter) 
{
    size_t start = 0;
    size_t end;

    std::vector<std::string> ret;

    for(;(end = str.find(delimiter, start)) != std::string::npos; start = end + delimiter.length()) 
    {
        std::string part = str.substr(start, end - start);
        ret.push_back(part);
    }

    ret.push_back(str.substr(start));
    return ret;
}