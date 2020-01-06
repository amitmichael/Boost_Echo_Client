//
// Created by shachafk@wincs.cs.bgu.ac.il on 06/01/2020.
//

#include "../include/ClientSocket.h"
#include "../include/ConnectionHandler.h"


ClientSocket::ClientSocket(ConnectionHandler* handler,std::string host, int port,bool shouldTerminate) : handler_(handler),host_(host),port_(port),shouldTerminate_(shouldTerminate){};

void ClientSocket::connect() {

    if (!handler_->connect()) {
        std::cerr << "Cannot connect to " << host_ << ":" << port_ << std::endl;
        connected_ =false;
    }
    else {
        connected_=true;
    }

}

void ClientSocket::run() {
    while (!shouldTerminate_){

    }
}