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
    std::string decoded="";
    while (!*shouldTerminate_) {
        const int bufsize = 1024;
        char* buf[bufsize];
        std::string line;
        while (handler_->getBytes(buf,bufsize))) {
            getline(buf, bufsize);
            // check for invalid utf-8 (for a simple yes/no check, there is also utf8::is_valid function)
            string::iterator end_it = utf8::find_invalid(line.begin(), line.end());
            decoded=enddec.decodeNextByte((char) end_it);
            }
        Message msg = enddec.parseMsgFromSocket(decoded);
        msg.execute();
        msg.clear();
        std::cout << decoded << std::endl;
    }
}