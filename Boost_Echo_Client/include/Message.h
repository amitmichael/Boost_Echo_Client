//
// Created by shachafk@wincs.cs.bgu.ac.il on 06/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_MESSAGE_H
#define BOOST_ECHO_CLIENT_MESSAGE_H

#include <map>
#include "User.h"

enum MessageType {login,
    join,
    add,
    borrow,
    returnn, //double n
    status,
    logout};

class Message {

public:
    Message(User user);

    Message(std::string);
    MessageType getType();
    void loadMessageTypeMap();
    void addFirst(std::string);
    void addNext(std::string msg,int index);
    std::string getDestination();
    std::string getBookName();
    std::string getUserName();
    std::string getPassword();
    std::string getHost();
    int getPort();

private:
    MessageType type;
    std::map<std::string, MessageType> mapMessageType;
    std::string destination;
    std::string command;
    std::string bookName;
    std::string userName;
    std::string host;
    int port;
    std::string password;


};


#endif //BOOST_ECHO_CLIENT_MESSAGE_H
