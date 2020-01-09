//
// Created by shachafk@wincs.cs.bgu.ac.il on 06/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_MESSAGE_H
#define BOOST_ECHO_CLIENT_MESSAGE_H

#include <map>
#include "../include/User.h"


enum MessageType {login,
    join,
    add,
    borrow,
    exitt, //double t
    returnn, //double n
    status,
    logout,
    connected,
    error,
    recepit,
    message

    };

class Message {

public:
    Message(User* user);
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
    void execute();
    std::string getSubscriptionId();
    std::string getreciptid();
    void clear();
    void setBody(std::string body_);
    void loadFromBefore(Message* before);
    User* getUser();
    std::string getToSend();



private:
    MessageType type;
    std::string msgID;
    int version;
    std::string body;
    MessageType beforeType;
    std::map<std::string, MessageType> mapMessageType;
    std::string destination;
    std::string command;
    std::string bookName;
    std::string userName;
    std::string host;
    int port;
    std::string password;
    User* user_;
    std::string subscriptionId;
    std::string reciptid;
    std::string toSend="";



};


#endif //BOOST_ECHO_CLIENT_MESSAGE_H
