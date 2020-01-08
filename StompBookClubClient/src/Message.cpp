//
// Created by shachafk@wincs.cs.bgu.ac.il on 06/01/2020.
//

#include <string>
#include <iostream>
#include "../include/Message.h"


Message::Message(User* user):user_(user){
    loadMessageTypeMap();
    userName = user_->getName();
}

void Message::execute(){
    int receiptid = user_->getAndIncrementreceiptId();
    reciptid = std::to_string(receiptid);


       if (type == logout){
           if (!*user_->isConnected()){
               *user_->shouldTerminate() = true;
           }
       }

        if (type==login){
           user_->setName(userName);
           *user_->isConnected() = true;
       }
        if(type== add){
            Inventory* inv =  user_->getInv();
            inv->addBook(new Book(bookName,userName,destination));
       }
       if (type ==join){
           int subid = user_->getAndIncrementSubscriptionId();
           user_->addToGenreSubIdmap(destination,subid);
           subscriptionId = std::to_string(subid);

       }
       if (type==exitt){
           subscriptionId = std::to_string(user_->getSubIdByGenre(destination));
           user_->removeFromenreSubIdmap(destination);
       }
       if(type==connected){
           std::cout<<"Login succsessful"<<std::endl;
       }
       if (type==recepit){
           if (beforeType=="join"){
               std::cout<<"Joined club "+getDestination()<<std::endl;
           }
           else if (beforeType=="logout"){
               std::cout<<"Joined club "+getDestination()<<std::endl;
           }
           else{
              std::cout<<"beforeTYPE is invalid"<<std::endl;
           }
       }
       if (type==message){

       }

}

void  Message::loadFromBefore(Message before){
    beforeType=before.type;
}

void Message::addFirst(std::string msg){
    type = mapMessageType.at(msg);
    command = msg;
}



void Message::addNext(std::string msg,int index){
    ////// first add////////////////////////////
    if (index==1){
        if ( type == join| type ==add | type == borrow | type ==returnn | type == status| type == exitt){
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
    ///////load header////////
    if(index==4){
        int pos = msg.find(":");
        std::pair<std::string,std::string> toPush;
        toPush.first=msg.substr(0,pos);
        toPush.second=msg.substr(pos+1);
        if (toPush.first==("receipt")){
            reciptid=toPush.second;
        }
        header.push_back(toPush);
    }
    ///////////set body///////
    if(index==5){
        body=msg;
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

User* Message::getUser(){
    return user_;
}


std::string Message::getSubscriptionId(){
    return subscriptionId;
}
std::string Message::getreciptid(){
    return reciptid;
}
void Message::setBody(std::string body_){
    body=body_;
}


void Message::loadMessageTypeMap(){
    mapMessageType.insert(std::make_pair("logout", MessageType::logout));
    mapMessageType.insert(std::make_pair("join", MessageType::join));
    mapMessageType.insert(std::make_pair("status", MessageType::status));
    mapMessageType.insert(std::make_pair("add", MessageType::add));
    mapMessageType.insert(std::make_pair("borrow", MessageType::borrow));
    mapMessageType.insert(std::make_pair("exit", MessageType::exitt));
    mapMessageType.insert(std::make_pair("login", MessageType::login));
    mapMessageType.insert(std::make_pair("return", MessageType::returnn));
    mapMessageType.insert(std::make_pair("CONNECTED", MessageType::connected));
    mapMessageType.insert(std::make_pair("RECEIPT", MessageType::recepit));
    mapMessageType.insert(std::make_pair("MESSAGE", MessageType::message));
    mapMessageType.insert(std::make_pair("ERROR", MessageType::error));


}

