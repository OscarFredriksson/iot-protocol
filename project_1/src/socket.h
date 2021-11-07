#include <iostream>
#include <unistd.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <netdb.h>
#include <sys/types.h>
#include <string>
#include <vector>

class Socket 
{
public:
    Socket(const std::string& hostname, const int port);

    int connect();

    std::string receive();

    void send(const std::string& msg);

    void close();

private:
    const std::string hostname;
    const int port;
    
    int sockfd;
    // int newsockfd;
    // sockaddr_in addr_in; 
    // sockaddr* addr;
    // int addrlen;
    // hostent *server;
};