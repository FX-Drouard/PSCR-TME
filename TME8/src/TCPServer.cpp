#include "TCPServer.h"
#include <iostream>

namespace pr {

void clientHandler(Socket sc, ConnectionHandler *handler) {
    handler->handleConnection(sc);
    sc.close();
}

void TCPServer::stopServer() {
    ss->close();
    acceptThread.join();
}

bool TCPServer::startServer(int port) {
    ss = new ServerSocket(port);

    if (!ss->isOpen()) {
        std::cerr << "Failed to open ServerSocket." << std::endl;
        return false;
    }

    acceptThread = std::thread([this] {
        while (true) {
            Socket sc = ss->accept();
            if (!sc.isOpen()) {
                std::cerr << "Failed to accept connection." << std::endl;
                break;
            }
            std::thread(clientHandler, std::move(sc), handler).detach();
        }
    });

    return true;
}

} // namespace pr
