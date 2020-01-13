//
// Created by shachafk@wincs.cs.bgu.ac.il on 06/01/2020.
//

#include "../include/ClientKeyboard.h"
#include "../include/ConnectionHandler.h"
#include "../include/StompEncoderDecoder.h"
#include "../include/MsgInfo.h"


ClientKeyboard::ClientKeyboard(ConnectionHandler* handler,MsgInfo* info,User* user,std::mutex * _mutex) : handler_(handler),host_(),port_(),info_(info),user_(user),_mutex(_mutex){};
ClientKeyboard::ClientKeyboard(const ClientKeyboard &other){
    copy (other.handler_,other.info_,other.user_,other._mutex) ;
}
ClientKeyboard& ClientKeyboard::operator=(const ClientKeyboard &other){
    if (this!=&other){
        copy (other.handler_,other.info_,other.user_,other._mutex) ;
    }
    return *this;
}
void ClientKeyboard::copy (ConnectionHandler* other_handler,MsgInfo* other_info,User* other_user,std::mutex * other_mutex){
    handler_=other_handler;
    info_=other_info;
    _mutex=other_mutex;
}


void ClientKeyboard::run() {
    StompEncoderDecoder enddec(user_);
    while (!*user_->shouldTerminate()) {

        const int bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);
        Message* msg = enddec.parseMsgFromKeyboard(line);
        msg->execute();
        if (msg->getType() == returnn) {
            std::string out = msg->getToSend();
            if (out.size() > 0) { //send msg that the user has the book
                std::cout << out << std::endl;
                handler_->sendBytes(out.c_str(), out.length());
            }
        }
        info_->addToreceiptPerMsgMap(stoi(msg->getreciptid()), msg);
        std::string encoded = enddec.encode(msg);
        std::cout << encoded << std::endl;
        handler_->sendBytes(encoded.c_str(), encoded.length());
        if (msg->getType() == logout)
            break;
        }

}

