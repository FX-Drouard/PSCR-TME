#include "Socket.h"
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
namespace pr {

void Socket::connect(const std::string &host, int port) {
   struct addrinfo * res;
   getaddrinfo(host.c_str(),(std::to_string(port)).c_str(),nullptr,& res);
   in_addr ipv4= ((struct sockaddr_in*) (res->ai_addr))->sin_addr;
   freeaddrinfo(res);
   connect(ipv4,port);
}

void Socket::connect(in_addr ipv4, int port) {
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        perror("socket");
        return;
    }

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr = ipv4;

    if (::connect(fd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("connect");
        close();
        return;
    }
}

void Socket::close() {
    if (fd != -1) {
        ::close(fd);
        fd = -1;
    }
}

std::ostream &operator<<(std::ostream &os, struct sockaddr_in *addr) {
    //char ip[INET_ADDRSTRLEN];
    //inet_ntop(AF_INET, &(addr->sin_addr), ip, INET_ADDRSTRLEN);

    char hname[1024];
    if(!getnameinfo((struct sockaddr *) addr, sizeof (*addr),hname,1024,nullptr,0,0)){
        os << std::string(hname);
    }
    //os << ip << ":" << ntohs(addr->sin_port);
    return os;
}

} // namespace pr
