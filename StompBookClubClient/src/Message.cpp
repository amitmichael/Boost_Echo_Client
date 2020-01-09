//
// Created by shachafk@wincs.cs.bgu.ac.il on 06/01/2020.
//

#include <string>
#include <iostream>
#include "../include/Message.h"


Message::Message(User* user):user_(user){
    loadMessageTypeMap();
    userName = user_->getName();
    reciptid = "-1";

}

void Message::execute(){
    int receiptid = user_->getAndIncrementreceiptId();
    reciptid = std::to_string(receiptid);


        if (type==login){
           user_->setName(userName);

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
           std::cout<<"Login successful"<<std::endl;
       }
       if (type==recepit){

           if (beforeType==join){
               std::cout<<"Joined club "+getDestination()<<std::endl;
           }
           else if (beforeType==logout){
               std::cout<<"logging out... "+getDestination()<<std::endl;
               *user_->shouldTerminate() = true;
           }
           else{
              std::cout<<"beforeTYPE is invalid"<<std::endl;
           }
       }
       if (type==message){
           if (beforeType==exitt){
               std::cout<<"Exited club "+getDestination()<<std::endl;
           }
           else if(beforeType==add){
               std::cout<<""+userName+" has added the book "+bookName<<std::endl;
           }
           else if(beforeType==borrow){

           }
       }

}

void  Message::loadFromBefore(Message* before){
    beforeType=before->type;
    bookName=before->getBookName();
    destination=before->getDestination();
    if (beforeType==borrow){
        Inventory* inv =  user_->getInv();
        if(inv->getBooks().count(destination)>0){
            std::vector<Book*>* books =inv->getBooks().at(destination);

        }
    }
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
        std::string header=msg.substr(0,pos);
        if(header=="receipt-id"){
            reciptid=msg.substr(pos+1);
        }
        else if (header=="subscription"){
            subscriptionId=msg.substr(pos+1);
        }
        else if (header=="destination"){
            destination=msg.substr(pos+1);
        }
        else if (header=="version"){
            version=stoi(msg.substr(pos+1));
        }
        else if (header=="Message-id"){
            msgID=msg.substr(pos+1);
        }


    }
    ///////////set body///////
    if(index==5){
        body=msg;
        if (msg.find("added the book")!=std::string::npos){
           int pos=msg.find("book");
           bookName=msg.substr(pos+5);
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

