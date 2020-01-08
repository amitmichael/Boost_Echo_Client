//
// Created by shachafk@wincs.cs.bgu.ac.il on 06/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_CLIENTSOCKET_H
#define BOOST_ECHO_CLIENT_CLIENTSOCKET_H


#include "ConnectionHandler.h"
#include "../include/MsgInfo.h"

#include "../include/User.h"


class ClientSocket {



public:

    ClientSocket(ConnectionHandler* handler,std::string host, int port, bool* shouldTerminate,MsgInfo* info,bool* connected,User* user);

    void connect();
    void run();

private:
    ConnectionHandler* handler_;
    std::string host_;
    int port_;
    bool* shouldTerminate_;
    bool* connected_;
    MsgInfo* info_;

    User* user_;



};


#endif //BOOST_ECHO_CLIENT_CLIENTSOCKET_H
