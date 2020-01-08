
//
// Created by shachafk@wincs.cs.bgu.ac.il on 08/01/2020.
//


#include <stdlib.h>
#include "../include/ConnectionHandler.h"
#include "../include/ClientKeyboard.h"
#include "../include/ClientSocket.h"
#include "../include/StompEncoderDecoder.h"
#include <boost/system/error_code.hpp>
#include <thread>
#include <mutex>

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


    std::mutex  _mutex;
    ConnectionHandler*  connectionHandler;// = new ConnectionHandler(host, port);
    User *user = new User(new bool(false) , new bool(false));
    MsgInfo* info = new MsgInfo();
    StompEncoderDecoder enddec(user);

    const int bufsize = 1024;
    char buf[bufsize];
    std::cin.getline(buf, bufsize);
    std::string line(buf);
    Message* msg = enddec.parseMsgFromKeyboard(line);
    if (msg->getType() ==login) {
        std::string host = msg->getHost();
        short port = msg->getPort();
        ConnectionHandler *connectionHandler = new ConnectionHandler(host, port);
        connectionHandler->connect();
        msg->execute();
        ClientKeyboard clientKeyboard(connectionHandler, info, user, _mutex);
        ClientSocket clientSocket(connectionHandler, info, user, _mutex);
        info->addToreceiptPerMsgMap(stoi(msg->getreciptid()), msg);
        std::string encoded = enddec.encode(msg);
        std::cout << encoded << std::endl;
        connectionHandler->sendBytes(encoded.c_str(), encoded.length());
        std::thread threadKeyboard(&ClientKeyboard::run, &clientKeyboard); // run keyboard thread
        std::thread threadSocket(&ClientSocket::run, &clientSocket); // run socket thread
        threadKeyboard.join();
        threadSocket.join();

    } else{
        std::cout <<  "please login to continue" << std::endl;

    }


    /// delete all objects ///
    delete(info);
    delete(connectionHandler);
    delete(user);

    return 0;
}
