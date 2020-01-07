//
// Created by shachafk@wincs.cs.bgu.ac.il on 06/01/2020.
//

#include "../include/ClientSocket.h"
#include "../include/ConnectionHandler.h"
#include "../include/StompEncoderDecoder.h"


ClientSocket::ClientSocket(ConnectionHandler* handler,std::string host, int port,bool* shouldTerminate,MsgInfo* info,
                           bool* connected) : handler_(handler),host_(host),port_(port),shouldTerminate_(shouldTerminate),info_(info),connected_(connected){};

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
        std::cin.getline(buf, bufsize);
        std::string line(buf);
        std::string toAdd= (String)enddec.decodeNextByte((byte) read);
        if (toAdd!=null) {
            nextMessage.addNextInput(toAdd);
        }
        Message msg = enddec.parseMsgFromSocket();
        msg.execute();
        std::string decoded = enddec.encode(msg);
        msg.clear();
        std::cout << decoded << std::endl;
        handler_->sendBytes(encoded.c_str(), encoded.length());
    }
}