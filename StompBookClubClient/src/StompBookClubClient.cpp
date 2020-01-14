
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


    /// variables
    ConnectionHandler* connectionHandler;//
    bool *connected = new bool(false);
    bool *shouldTerminate = new bool(false);
    User *user = new User(connected, shouldTerminate);
    MsgInfo *info = new MsgInfo();
    StompEncoderDecoder enddec(user);


    /////
    Message* msg = nullptr;
    while (!*connected) {
        const int bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);
        msg = enddec.parseMsgFromKeyboard(line);
        if (msg->getType() == login) {
            std::string host = msg->getHost();
            short port = msg->getPort();
            connectionHandler = new ConnectionHandler(host, port);
            try {
                *connected = connectionHandler->connect();
            } catch (std::exception &e) {
                std::cerr << "Connection failed (Error: " << e.what() << ')' << std::endl;
                delete (connectionHandler);
            }
        }

        else{
        std::cout << "please login to continue" << std::endl;
        }
        }

    msg->execute();
    ClientKeyboard clientKeyboard(connectionHandler, info, user);
    ClientSocket clientSocket(connectionHandler, info, user);
    info->addToreceiptPerMsgMap(stoi(msg->getreciptid()), msg);
    std::string encoded = enddec.encode(msg);
    if (*connected)
        connectionHandler->sendBytes(encoded.c_str(), encoded.length());
    std::thread threadKeyboard(&ClientKeyboard::run, &clientKeyboard); // run keyboard thread
    std::thread threadSocket(&ClientSocket::run, &clientSocket); // run socket thread
    threadKeyboard.join();
    threadSocket.join();
    connectionHandler->close();

    /// delete all objects ///
    delete(info);
    delete(connectionHandler);
    delete(user);

    return 0;
}
