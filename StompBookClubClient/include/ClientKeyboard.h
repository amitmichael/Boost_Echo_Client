//
// Created by shachafk@wincs.cs.bgu.ac.il on 06/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_CLIENTKEYBOARD_H
#define BOOST_ECHO_CLIENT_CLIENTKEYBOARD_H


#include <mutex>
#include "../include/ConnectionHandler.h"
#include "../include/MsgInfo.h"

class ClientKeyboard {


public:

    ClientKeyboard(ConnectionHandler* handler,MsgInfo* info,User* user,std::mutex & _mutex);

    void run();

private:
    ConnectionHandler* handler_;
    std::string host_;
    int port_;
    MsgInfo* info_;
    User* user_;
    std::mutex & _mutex;




};


#endif //BOOST_ECHO_CLIENT_CLIENTKEYBOARD_H
