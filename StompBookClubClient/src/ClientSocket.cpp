//
// Created by shachafk@wincs.cs.bgu.ac.il on 06/01/2020.
//

#include "../include/ClientSocket.h"
#include "../include/ConnectionHandler.h"
#include "../include/StompEncoderDecoder.h"



ClientSocket::ClientSocket(ConnectionHandler* handler,MsgInfo* info,User* user): handler_(handler),info_(info),user_(user){};

void ClientSocket::connect() {

    if (!handler_->connect()) {
        std::cerr << "Cannot connect to " << host_ << ":" << port_ << std::endl;

    }
    else {

    }

}

void ClientSocket::run() {
    StompEncoderDecoder enddec(user_);
    while (!*user_->shouldTerminate() &  *user_->isConnected()) {
        const int bufsize = 1024;
        char buf[bufsize];
        handler_->getBytes(buf,bufsize);
        std::string toAdd;
        while (toAdd.size()==0){
            toAdd=(std::string)enddec.decodeNextByte(buf[0]);
        }
        Message* msg = enddec.parseMsgFromSocket(toAdd);
        int rid = stoi(msg->getreciptid());
        if (rid>0){
            Message* before = info_->getMsgByReceiptId(rid);
            msg->loadFromBefore(before);
        }
        msg->execute();
        info_->addToreceiptPerMsgMap(stoi(msg->getreciptid()), msg);
        //msg->clear();
        std::cout << msg << std::endl;
    }
}