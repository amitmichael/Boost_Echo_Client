//
// Created by shachafk@wincs.cs.bgu.ac.il on 06/01/2020.
//

#include "../include/ClientKeyboard.h"
#include "../include/ConnectionHandler.h"
#include "../include/StompEncoderDecoder.h"
#include "../include/MsgInfo.h"


ClientKeyboard::ClientKeyboard(ConnectionHandler* handler,std::string host, int port,bool* shouldTerminate,MsgInfo* info,

    while (!*shouldTerminate_) {
                               bool* connected,User* user) : handler_(handler),host_(host),port_(port),shouldTerminate_(shouldTerminate),info_(info),connected_(connected),user_(user){};


void ClientKeyboard::run() {
    StompEncoderDecoder enddec(user_);
    while (!*shouldTerminate_ & *connected_) {
        const int bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);
        Message* msg = enddec.parseMsgFromKeyboard(line);
        if (msg->getType()==logout){ // to remove
            *connected_=false;
        }
        msg->execute();
        info_->addToreceiptPerMsgMap(stoi(msg->getreciptid()), msg);
        std::string encoded = enddec.encode(msg);
        //msg.clear();
        std::cout << encoded << std::endl;
        handler_->sendBytes(encoded.c_str(), encoded.length());
        }
    }
