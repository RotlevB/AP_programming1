/*
 * Server.h
 *
 *  Created on: Dec 13, 2020
 *      Author: Eli
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <thread>
#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "commands.h"
#include "CLI.h"

using namespace std;

// edit your ClientHandler interface here:
class ClientHandler{
    public:
    virtual void handle(int clientID)=0;
};


// you can add helper classes here and implement on the cpp file


// edit your AnomalyDetectionHandler class here
class AnomalyDetectionHandler:public ClientHandler{
public:
    virtual void handle(int clientID) {
        socketIO* defIO = new socketIO(clientID);
        CLI cli(defIO);
        cli.start();
        delete defIO;
    }
};


// implement on Server.cpp
class Server {
	thread* t; // the thread to run the start() method in
    vector<thread*> threadpool;
    int serverFD;
    sockaddr_in server;
    sockaddr_in client;
    int limit;
    volatile bool willStop = false;
	// you may add data members

public:
	Server(int port) throw (const char*);
	virtual ~Server();
    void acceptClient(ClientHandler& ch)throw(const char*);
	void start(ClientHandler& ch)throw(const char*);
	void stop();
};

#endif /* SERVER_H_ */
