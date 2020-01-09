//
// Created by shachafk@wincs.cs.bgu.ac.il on 06/01/2020.
//

#include "../include/ClientSocket.h"
#include "../include/ConnectionHandler.h"
#include "../include/StompEncoderDecoder.h"



ClientSocket::ClientSocket(ConnectionHandler* handler,MsgInfo* info,User* user,std::mutex & _mutex): handler_(handler),info_(info),user_(user),_mutex(_mutex){};

void ClientSocket::connect() {

    if (!handler_->connect()) {
        std::cerr << "Cannot connect to " << host_ << ":" << port_ << std::endl;

    }
    else {

    }

}

void ClientSocket::run() {
    StompEncoderDecoder enddec(user_);
    while (!*user_->shouldTerminate() ) {
        if (*user_->isConnected()) {
            std::lock_guard<std::mutex> lock(_mutex);
            std::string toAdd = "";
            while (handler_->getLine(toAdd) != false) {
            }
            Message *msg = enddec.parseMsgFromSocket(toAdd);
            if (msg != nullptr) {
                int rid = stoi(msg->getreciptid());
                if (rid > 0) {
                    Message *before = info_->getMsgByReceiptId(rid);
                    msg->loadFromBefore(before);
                }
                msg->execute();
                if (msg->getType()==borrow){
                    std::string out=msg->getToSend();
                    if (out.size()>0){ //send msg that the user has the book
                        //info_->addToreceiptPerMsgMap(stoi(msg->getreciptid()), msg);
                        std::cout << out << std::endl;
                        handler_->sendBytes(out.c_str(), out.length());
                    }
                }
                if (msg->getType() == status){
                    std::string encoded = enddec.encode(msg);
                    std::cout << encoded << std::endl;
                    handler_->sendBytes(encoded.c_str(), encoded.length());
                }
                info_->addToreceiptPerMsgMap(stoi(msg->getreciptid()), msg);
                std::cout << enddec.toString(msg) << std::endl;
            }
        }
    }
}