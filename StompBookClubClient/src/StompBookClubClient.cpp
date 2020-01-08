
//
// Created by shachafk@wincs.cs.bgu.ac.il on 08/01/2020.
//


#include <stdlib.h>
#include "../include/ConnectionHandler.h"
#include "../include/ClientKeyboard.h"
#include "../include/ClientSocket.h"
#include <boost/system/error_code.hpp>
#include <thread>

/**
* This code assumes that the server replies the exact text the client sent it (as opposed to the practical session example)
*/
int main (int argc, char *argv[]) {
//    if (argc < 3) {
//        std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
//        return -1;
//    }
   // std::string host = argv[1];
   // short port = atoi(argv[2]);


    ConnectionHandler*  connectionHandler;// = new ConnectionHandler(host, port);
    User *user = new User(new bool(false));
    MsgInfo* info = new MsgInfo();
    bool* shouldTerminate = new bool(false);
    ClientKeyboard clientKeyboard(connectionHandler,shouldTerminate,info,user);
    ClientSocket clientSocket(connectionHandler,shouldTerminate,info,user);
    //clientSocket.connect();
    std::thread threadKeyboard(&ClientKeyboard::run,&clientKeyboard); // run keyboard thread
    std::thread threadSocket(&ClientSocket::run,&clientSocket); // run socket thread
    threadKeyboard.join();
    threadSocket.join();
    connectionHandler->close();


    /// delete all objects ///
    delete(info);
    delete(shouldTerminate);
    delete(connectionHandler);
    delete(user);

    return 0;
}
