//
// Created by shachafk@wincs.cs.bgu.ac.il on 06/01/2020.
//

#include "../include/ClientKeyboard.h"
#include "../include/ConnectionHandler.h"
#include "../include/StompEncoderDecoder.h"


ClientKeyboard::ClientKeyboard(ConnectionHandler* handler,std::string host, int port,bool shouldTerminate) : handler_(handler),host_(host),port_(port),shouldTerminate_(shouldTerminate){};


void ClientKeyboard::run() {
    User user;
        StompEncoderDecoder enddec(user);
    while (!shouldTerminate_){
        const short bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);
        Message msg = enddec.parseMsgFromKeyboard(line);
        msg.execute();
        std::string encoded = enddec.encode(msg);
        std::cout << encoded << std::endl;
        handler_->sendBytes(encoded.c_str(),encoded.length());

        }

    }
