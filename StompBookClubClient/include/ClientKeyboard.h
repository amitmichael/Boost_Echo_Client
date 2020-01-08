//
// Created by shachafk@wincs.cs.bgu.ac.il on 06/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_CLIENTKEYBOARD_H
#define BOOST_ECHO_CLIENT_CLIENTKEYBOARD_H


#include "../include/ConnectionHandler.h"
#include "../include/MsgInfo.h"

class ClientKeyboard {


public:

    ClientKeyboard(ConnectionHandler* handler,MsgInfo* info,User* user);

    void run();

private:
    ConnectionHandler* handler_;
    std::string host_;
    int port_;
    MsgInfo* info_;
    User* user_;




};


#endif //BOOST_ECHO_CLIENT_CLIENTKEYBOARD_H
