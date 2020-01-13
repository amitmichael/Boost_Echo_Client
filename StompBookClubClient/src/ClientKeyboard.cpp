//
// Created by shachafk@wincs.cs.bgu.ac.il on 06/01/2020.
//

#include "../include/ClientKeyboard.h"
#include "../include/ConnectionHandler.h"
#include "../include/StompEncoderDecoder.h"
#include "../include/MsgInfo.h"


ClientKeyboard::ClientKeyboard(ConnectionHandler* handler,MsgInfo* info,User* user,std::mutex & _mutex) : handler_(handler),host_(),port_(),info_(info),user_(user),_mutex(_mutex){};



void ClientKeyboard::run() {
    StompEncoderDecoder enddec(user_);
    while (!*user_->shouldTerminate() ) {

        const int bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);
        Message* msg = enddec.parseMsgFromKeyboard(line);
        msg->execute();
        if (msg->getType() == returnn) {
            std::string out = msg->getToSend();
            if (out.size() > 0) { //send msg that the user has the book
                if (*user_->isConnected())
                    handler_->sendBytes(out.c_str(), out.length());
            }
        }
        info_->addToreceiptPerMsgMap(stoi(msg->getreciptid()), msg);
        std::string encoded = enddec.encode(msg);
        if (*user_->isConnected())
            handler_->sendBytes(encoded.c_str(), encoded.length());
        if (msg->getType() == logout)
            break;
        }

}

