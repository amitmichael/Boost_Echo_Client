//
// Created by shachafk@wincs.cs.bgu.ac.il on 06/01/2020.
//

#include <string>
#include "../include/Message.h"
#include "../include/User.h"


Message::Message(User user){
    loadMessageTypeMap();
    userName = user.getName();

}

void Message::addFirst(std::string msg){
        type = mapMessageType.at(msg);
        command = msg;
}

void Message::addNext(std::string msg,int index){
    ////// first add////////////////////////////
    if (index==1){
        if ( type == join| type ==add | type == borrow | type ==returnn | type == status){
            destination =msg;
        }
        if (type == login){
            int i = msg.find(':');
            host = msg.substr(0,i);
            msg = msg.substr(i+1);
            port = stoi(msg);
        }
    }

    ////// second add////////////////////////////
    if (index ==2){
        if ( type ==login){
            userName = msg;
        }
        if (type ==add| type==borrow | type == returnn){
            bookName = msg;
        }
    }

    ////// third add////////////////////////////
    if (index ==3){
        if ( type ==login){
            password = msg;
        }

    }
}

MessageType Message::getType(){
    return type;
}

std::string Message::getDestination(){
    return destination;
}

std::string Message::getBookName(){
    return bookName;
}


std::string Message::getUserName(){
    return userName;
}

std::string Message::getPassword(){
    return password;
}

std::string Message::getHost(){
    return host;
}

int Message::getPort(){
    return port;
}


void Message::loadMessageTypeMap(){
    mapMessageType.insert(std::make_pair("join", MessageType::join));
    mapMessageType.insert(std::make_pair("status", MessageType::status));
    mapMessageType.insert(std::make_pair("add", MessageType::add));
    mapMessageType.insert(std::make_pair("borrow", MessageType::borrow));
    mapMessageType.insert(std::make_pair("login", MessageType::login));
    mapMessageType.insert(std::make_pair("logout", MessageType::logout));
    mapMessageType.insert(std::make_pair("return", MessageType::returnn));



}

