#include "ServerSocket.h"
#include <unistd.h>
#include <netinet/in.h>
#include <iostream>

namespace pr {

ServerSocket::ServerSocket(int port) : socketfd(-1) {
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        perror("socket");
        return;
    }

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    if (::bind(socketfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("bind");
        close();
        return;
    }

    if (::listen(socketfd, 5) == -1) {
        perror("listen");
        close();
        return;
    }
}

Socket ServerSocket::accept() {
    int clientSocket = ::accept(socketfd, nullptr, nullptr);
    if (clientSocket == -1) {
        perror("accept");
        return Socket(); // Return a Socket with invalid fd
    }
    return Socket(clientSocket);
}

void ServerSocket::close() {
    if (socketfd != -1) {
        ::close(socketfd);
        socketfd = -1;
    }
}

} // namespace pr
