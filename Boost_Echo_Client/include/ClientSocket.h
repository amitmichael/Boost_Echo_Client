//
// Created by shachafk@wincs.cs.bgu.ac.il on 06/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_CLIENTSOCKET_H
#define BOOST_ECHO_CLIENT_CLIENTSOCKET_H


#include "ConnectionHandler.h"

class ClientSocket {
private:
 ConnectionHandler* handler_;
 std::string host_;
 int port_;
 bool& shouldTerminate_;
 bool connected_;



public:
    ClientSocket(ConnectionHandler* handler,std::string host, int port, bool shouldTerminate);
    void connect();
    void run();

};


#endif //BOOST_ECHO_CLIENT_CLIENTSOCKET_H
