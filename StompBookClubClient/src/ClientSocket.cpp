//
// Created by shachafk@wincs.cs.bgu.ac.il on 06/01/2020.
//

#include "../include/ClientSocket.h"
#include "../include/ConnectionHandler.h"
#include "../include/StompEncoderDecoder.h"



ClientSocket::ClientSocket(ConnectionHandler* handler,std::string host, int port, bool* shouldTerminate,MsgInfo* info,bool* connected,User* user): handler_(handler),host_(host),port_(port),shouldTerminate_(shouldTerminate),info_(info),connected_(connected),user_(user){};

void ClientSocket::connect() {

    if (!handler_->connect()) {
        std::cerr << "Cannot connect to " << host_ << ":" << port_ << std::endl;

    }
    else {

    }

}

void ClientSocket::run() {
    User *user = new User();
    StompEncoderDecoder enddec(user);
    while (!*shouldTerminate_) {
        const int bufsize = 1024;
        char buf[bufsize];
        handler_->getBytes(buf,bufsize);
        std::string toAdd= (std::string)enddec.decodeNextByte(buf[0]);
        if (toAdd.size() > 0) {
         //   nextMessage.addNextInput(toAdd); ??
        }
        Message msg = enddec.parseMsgFromSocket(toAdd);
        msg.execute();
        std::string decoded = enddec.encode(msg);
        msg.clear();
        std::cout << decoded << std::endl;
        handler_->sendBytes(decoded.c_str(), decoded.length());

    }
}