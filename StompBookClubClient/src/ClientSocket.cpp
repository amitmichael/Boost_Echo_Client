//
// Created by shachafk@wincs.cs.bgu.ac.il on 06/01/2020.
//

#include "../include/ClientSocket.h"
#include "../include/ConnectionHandler.h"


ClientSocket::ClientSocket(ConnectionHandler* handler,std::string host, int port, bool* shouldTerminate,MsgInfo* info,bool* connected,User* user): handler_(handler),host_(host),port_(port),shouldTerminate_(shouldTerminate),info_(info),connected_(connected),user_(user){};

void ClientSocket::connect() {

    if (!handler_->connect()) {
        std::cerr << "Cannot connect to " << host_ << ":" << port_ << std::endl;

    }
    else {

    }

}

void ClientSocket::run() {
    while (!*shouldTerminate_){
//        if (!*connected_){
//            *shouldTerminate_=true;
//        }
    }
}