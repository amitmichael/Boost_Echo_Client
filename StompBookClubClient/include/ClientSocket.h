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

    ClientSocket(ConnectionHandler* handler,MsgInfo* info,User* user,std::mutex * _mutex);
    ClientSocket(const ClientSocket &other);
    ClientSocket& operator=(const ClientSocket &other);
    void copy (ConnectionHandler* other_handler,MsgInfo* other_info,User* other_user,std::mutex * other_mutex);
    void connect();
    void run();

private:
    ConnectionHandler* handler_;
    std::string host_;
    int port_;
    MsgInfo* info_;
    User* user_;
    std::mutex * _mutex;



};


#endif //BOOST_ECHO_CLIENT_CLIENTSOCKET_H
