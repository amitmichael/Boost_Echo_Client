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
    wantToBorrow,
    CheckIfCanLoan,
    exitt, //double t
    returnn, //double n
    status,
    logout,
    connected,
    error,
    recepit,
    message,
    invalid,
    statusResponse
    };

class Message {

public:
    Message(User* user);
    Message(std::string);
    Message(const Message &other);
    Message& operator=(const Message &other);
    void copy(MessageType other_type,std::string other_msgID,double other_version,std::string other_body,MessageType other_beforeType,std::map<std::string, MessageType> other_mapMessageType,std::string other_destination,std::string other_command,std::string other_bookName,std::string other_userName,std::string other_host,int other_port,std::string other_password,User* other_user_,std::string other_subscriptionId,std::string other_reciptid,std::string other_toSend);
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
    void loadFromBefore(Message* before);
    User* getUser();
    std::string getToSend();
    std::string toBorrow="";
    bool end();
    void loaderror(std::string line);


private:
    MessageType type;
    std::string msgID;
    double version;
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
    std::string errormessage = "";
    bool end_ = false;



};


#endif //BOOST_ECHO_CLIENT_MESSAGE_H
