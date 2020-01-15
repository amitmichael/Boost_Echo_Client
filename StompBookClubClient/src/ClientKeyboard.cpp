//
// Created by shachafk@wincs.cs.bgu.ac.il on 06/01/2020.
//

#include "../include/ClientKeyboard.h"
#include "../include/ConnectionHandler.h"
#include "../include/StompEncoderDecoder.h"
#include "../include/MsgInfo.h"


ClientKeyboard::ClientKeyboard(ConnectionHandler* handler,MsgInfo* info,User* user) : handler_(handler),host_(),port_(),info_(info),user_(user),toContinue(true){};
ClientKeyboard::ClientKeyboard(const ClientKeyboard &other):handler_(),host_(),port_(),info_(),user_(),toContinue(true){
    copy (other.handler_,other.info_,other.user_) ;
}
ClientKeyboard& ClientKeyboard::operator=(const ClientKeyboard &other){
    if (this!=&other){
        copy (other.handler_,other.info_,other.user_) ;
    }
    return *this;
}
void ClientKeyboard::copy (ConnectionHandler* other_handler,MsgInfo* other_info,User* other_user){
    handler_=other_handler;
    info_=other_info;
}


void ClientKeyboard::run() {
    StompEncoderDecoder enddec(user_);
    while (!*user_->shouldTerminate() & toContinue ) {

        const int bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);
        Message *msg = enddec.parseMsgFromKeyboard(line);
        if (msg->getType() == invalid) {
            std::cout << "Invalid input" << std::endl;
            delete (msg);
        } else {
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
                toContinue= false;
        }
    }

}

