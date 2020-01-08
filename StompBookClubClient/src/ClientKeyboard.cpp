//
// Created by shachafk@wincs.cs.bgu.ac.il on 06/01/2020.
//

#include "../include/ClientKeyboard.h"
#include "../include/ConnectionHandler.h"
#include "../include/StompEncoderDecoder.h"
#include "../include/MsgInfo.h"


ClientKeyboard::ClientKeyboard(ConnectionHandler* handler,bool* shouldTerminate,MsgInfo* info,User* user) : handler_(handler),shouldTerminate_(shouldTerminate),info_(info),user_(user){};



void ClientKeyboard::run() {
    StompEncoderDecoder enddec(user_);
    while (!*shouldTerminate_ ) {
        const int bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);
        Message* msg = enddec.parseMsgFromKeyboard(line);

        if ( *user_->isConnected()) {
            msg->execute();
            info_->addToreceiptPerMsgMap(stoi(msg->getreciptid()), msg);
            std::string encoded = enddec.encode(msg);
            std::cout << encoded << std::endl;
            handler_->sendBytes(encoded.c_str(), encoded.length());
        }
        else if (msg->getType() ==login){
           host_ = msg->getHost();
           port_ = msg->getPort();
           handler_ = new ConnectionHandler(host_,port_);
           handler_->connect();
            msg->execute();
            info_->addToreceiptPerMsgMap(stoi(msg->getreciptid()), msg);
            std::string encoded = enddec.encode(msg);
            std::cout << encoded << std::endl;
            handler_->sendBytes(encoded.c_str(), encoded.length());
       }
        else{
            std::cout <<  "please login to continue" << std::endl;
        }
    }
}

