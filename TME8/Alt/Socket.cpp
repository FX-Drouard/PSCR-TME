#include "Socket.h"
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>

namespace pr {

void Socket::connect(const std::string &host, int port) {
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        perror("socket");
        return;
    }

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);

    if (inet_pton(AF_INET, host.c_str(), &(serverAddress.sin_addr)) <= 0) {
        perror("inet_pton");
        close();
        return;
    }

    if (::connect(fd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("connect");
        close();
        return;
    }
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
    char ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(addr->sin_addr), ip, INET_ADDRSTRLEN);
    os << ip << ":" << ntohs(addr->sin_port);
    return os;
}

} // namespace pr
