#include <string>
#include <vector>
#include <fstream>
#include "httpserver.h"
 
int main() 
{
    const int port = 8080;
    const std::string filename = "sensors.json";

    HttpServer server(port);

    server.addGetHandler("/", [](ParamMap urlParams){
        std::string helloWorldHTML = "<h1>Hello World</h1>";

        return HttpResponse(HttpStatusCode::OK, helloWorldHTML, HttpContentType::html);
    });

    server.addGetHandler("/sensor", [filename](ParamMap urlParams){
        std::ifstream i(filename);
        JsonObj j;
        i >> j;
        i.close();

        if(!urlParams.count("id"))
            return HttpResponse(HttpStatusCode::BAD_REQUEST, "missing id parameter");

        std::string id = urlParams["id"];

        JsonObj sensor = j[id];

        return HttpResponse(HttpStatusCode::OK, sensor.dump(), HttpContentType::json);
    });


    server.addPostHandler("/sensor", [filename](ParamMap urlParams, JsonObj jsonBody){
        if(!jsonBody.contains("id"))
            return HttpResponse(HttpStatusCode::BAD_REQUEST, "missing id parameter");

        std::string id = std::to_string(static_cast<int>(jsonBody["id"]));

        std::ifstream i(filename);
        JsonObj j;
        i >> j;
        i.close();

        if(j.contains(id))
             return HttpResponse(HttpStatusCode::CONFLICT, "Sensor already exists"); 

        j[id]["values"] = nullptr;

        std::ofstream o(filename);
        o << std::setw(4) << j << std::endl;

        return HttpResponse(HttpStatusCode::CREATED, "Sensor with id '" + id + "' added.");
    });

    server.start();

    return 0;
}