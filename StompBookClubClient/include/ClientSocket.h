//
// Created by shachafk@wincs.cs.bgu.ac.il on 06/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_CLIENTSOCKET_H
#define BOOST_ECHO_CLIENT_CLIENTSOCKET_H


#include <mutex>
#include "ConnectionHandler.h"
#include "../include/MsgInfo.h"

#include "../include/User.h"


class ClientSocket {



public:

    ClientSocket(ConnectionHandler* handler,MsgInfo* info,User* user);
    ClientSocket(const ClientSocket &other);
    ClientSocket& operator=(const ClientSocket &other);
    void copy (ConnectionHandler* other_handler,MsgInfo* other_info,User* other_user);
    void connect();
    void run();

private:
    ConnectionHandler* handler_;
    std::string host_;
    int port_;
    MsgInfo* info_;
    User* user_;



};


#endif //BOOST_ECHO_CLIENT_CLIENTSOCKET_H
