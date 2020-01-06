//
// Created by shachafk@wincs.cs.bgu.ac.il on 06/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_CLIENTKEYBOARD_H
#define BOOST_ECHO_CLIENT_CLIENTKEYBOARD_H


#include "ConnectionHandler.h"

class ClientKeyboard {
private:
    ConnectionHandler* handler_;
    std::string host_;
    int port_;
    bool& shouldTerminate_;



public:
    ClientKeyboard(ConnectionHandler* handler,std::string host, int port, bool shouldTerminate);
    void run();


};


#endif //BOOST_ECHO_CLIENT_CLIENTKEYBOARD_H
