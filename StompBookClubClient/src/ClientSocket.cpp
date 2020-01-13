//
// Created by shachafk@wincs.cs.bgu.ac.il on 06/01/2020.
//

#include "../include/ClientSocket.h"
#include "../include/ConnectionHandler.h"
#include "../include/StompEncoderDecoder.h"



ClientSocket::ClientSocket(ConnectionHandler* handler,MsgInfo* info,User* user,std::mutex * _mutex): handler_(handler),host_(),port_(),info_(info),user_(user),_mutex(_mutex){};

ClientSocket::ClientSocket(const ClientSocket &other):handler_(),host_(),port_(),info_(),user_(),_mutex(){
    copy (other.handler_,other.info_,other.user_,other._mutex) ;
}
ClientSocket& ClientSocket::operator=(const ClientSocket &other){
    if (this!=&other){
        copy (other.handler_,other.info_,other.user_,other._mutex) ;
    }
    return *this;
}
void ClientSocket::copy (ConnectionHandler* other_handler,MsgInfo* other_info,User* other_user,std::mutex * other_mutex){
    handler_=other_handler;
    info_=other_info;
    _mutex=other_mutex;
}
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
            //std::lock_guard<std::mutex> lock(*_mutex);
            std::string toAdd = "";
            while (handler_->getLine(toAdd) != false) {
            }
            Message *msg = enddec.parseMsgFromSocket(toAdd);
            /// error case////
            if (msg->getType() == error){
                    msg->loaderror(toAdd);
                    toAdd = "";
                    handler_->close();// close the connection due to error
                    *user_->isConnected() = false;
            }
            if (msg != nullptr) {
                if (msg->getType()!=error) {
                    int rid = stoi(msg->getreciptid());
                    if (rid > 0) {
                        Message *before = info_->getMsgByReceiptId(rid);
                        msg->loadFromBefore(before);
                    }
                } else{ // type is error

                }
                msg->execute();
                if (msg->getType()==CheckIfCanLoan){
                    std::string out=msg->getToSend();
                    if (out.size()>0){ //send msg that the user has the book
                        //std::cout << out << std::endl;
                        handler_->sendBytes(out.c_str(), out.length());
                    }
                }
                if (msg->getType() == status){
                    std::string encoded = enddec.encode(msg);
                    //std::cout << encoded << std::endl;
                    handler_->sendBytes(encoded.c_str(), encoded.length());
                }
                if (msg->toBorrow.size()>0){//sends the msg Taking
                    //std::cout << msg->toBorrow << std::endl;
                    handler_->sendBytes(msg->toBorrow.c_str(), msg->toBorrow.length());
                }
                info_->addToreceiptPerMsgMap(stoi(msg->getreciptid()), msg);
                //std::cout << enddec.toString(msg) << std::endl;
            }
        }
    }
}