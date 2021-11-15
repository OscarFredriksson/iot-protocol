#include "socket.h"
#include <stdio.h>
#include <arpa/inet.h>
// #include <errno.h>

Socket::Socket(const std::string& hostname, const int port):
    hostname(hostname), port(port) 
{

}

int Socket::connect() 
{
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    // Creating socket file descriptor 
    if (sockfd == 0) { 
        std::cerr << "socket failed\n"; 
        return -1; 
    } 
 
    hostent* server = gethostbyname(hostname.c_str());
    
    if(server == NULL) {
        std::cerr << "ERROR, no such host\n";
        return -1;
    }

    sockaddr_in addr_in;
    addr_in.sin_family = AF_INET;
    addr_in.sin_port = htons(port);

    

    addrinfo* first_addr = NULL;
    
    getaddrinfo(hostname.c_str(), std::to_string(port).c_str(), 0, &first_addr);

    for (addrinfo* addr_it = first_addr; addr_it; addr_it = addr_it->ai_next) {
        
        
        
        if (::connect(sockfd, addr_it->ai_addr, sizeof(addr_in)) < 0) { 
            std::cerr << "ERROR connecting\n";
            continue;
        }  

        return 1;    
    }

    // Got through the loop without succesfully connecting to any of the hosts, return failure
    return -1;
}

std::vector<char> Socket::receive()
{
    int msgSize = 1024;
    char msg[msgSize]; 
    int byteCount = read(sockfd, msg, msgSize);

    return std::vector<char>(msg, msg + byteCount);
}

void Socket::send(const std::string& msg) 
{
    ::send(sockfd, msg.c_str(), msg.size(), 0);
}

void Socket::send(const std::vector<char>& msg)
{
    ::send(sockfd, msg.data(), msg.size(), 0);
}

void Socket::close() 
{
    ::close(sockfd);
    // ::close(newsockfd);
}