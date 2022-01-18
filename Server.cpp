
#include "Server.h"

Server::Server(int port)throw (const char*) {
    serverFD = socket(AF_INET, SOCK_STREAM, 0);
    if (serverFD < 0) {
        throw "socket error!";
    }
    limit = 5;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);
    if (bind(serverFD, (struct sockaddr*)&server, sizeof(server)) < 0) {
        throw "bind error";
    }
    if (listen(serverFD, 3) < 0) {
        throw "listen error!";
    }
}

void Server::acceptClient(ClientHandler& ch)throw(const char*) {

    socklen_t clientSize = sizeof(client);
    int aClient;
    aClient = accept(serverFD, (struct sockaddr*)&client, &clientSize);
    if (aClient < 0) {
        throw "accept failed";
    }
    //cout << "client connected" << endl;
    ch.handle(aClient);
    close(aClient);
}

void Server::start(ClientHandler& ch)throw(const char*){	
    t = new thread([&ch, this]() {
        //cout << "waiting for a client" << endl;
        while (!willStop) { // shouldStop is changed only by stop() method
            if (threadpool.size() < limit) {
                try {
                    //threadpool.push_back(new thread(&Server::acceptClient, this, ch));
                    acceptClient(ch);
                }
                catch (const char* msg) {
                    throw msg;
                }
            }
            else {
                for (auto it = std::begin(threadpool); it != std::end(threadpool); ++it) {
                    if ((*it)->joinable()) {
                        (*it)->join();
                        delete (*it);
                        threadpool.erase(it);
                    }
                }
            }
        }
        for (auto it = std::begin(threadpool); it != std::end(threadpool); ++it) {
            (*it)->join();
            delete (*it);
            threadpool.erase(it);
        }
        close(serverFD);
        });
}

void Server::stop(){
	t->join(); // do not delete this!
}

Server::~Server() {
}

