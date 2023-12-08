#ifndef SRC_TCPSERVER_H_
#define SRC_TCPSERVER_H_

#include <thread>
#include "ServerSocket.h"
#include "ConnectionHandler.h"

namespace pr {

class TCPServer {
    ServerSocket *ss;            // la socket d'attente si elle est instanciee
    ConnectionHandler *handler;   // le gestionnaire de session passe a la constru

    std::thread acceptThread;     // Thread pour accepter les connexions

public:
    TCPServer(ConnectionHandler *handler) : ss(nullptr), handler(handler) {}
    // Tente de creer une socket d'attente sur le port donne
    bool startServer(int port);

    // stoppe le serveur
    void stopServer();
};

} // namespace pr

#endif /* SRC_TCPSERVER_H_ */
