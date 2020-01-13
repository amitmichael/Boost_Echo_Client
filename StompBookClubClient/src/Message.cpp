//
// Created by shachafk@wincs.cs.bgu.ac.il on 06/01/2020.
//

#include <string>
#include <iostream>
#include "../include/Message.h"


Message::Message(User* user):type(),msgID(),version(),body(),beforeType(),mapMessageType(),destination(),command(),bookName(),userName(),host(),port(),password(),user_(user),subscriptionId(),reciptid(),toSend(),errormessage(),end_(){
    loadMessageTypeMap();
    userName = user_->getName();
    reciptid = "-1";

}

bool Message::end(){
    return end_;
}

void Message::loaderror(std::string msg) {
    body="";
    while (!end_) {
        std::string line="";
        int index =0;
        bool endline=false;
        bool emptyline=false;
        for(auto x:msg){
            if(index==0){
                if (x == '\n') {
                    line="";
                    index++;
                }
                else{
                    line=line+x;
                }
            }
            if (emptyline){
                index++;
            }
            else if (index==1){ //headers parse
                if(endline){ //checks if it is an empty line and skip it
                    if (x=='\n'){
                        index++;
                        endline=false;
                        continue;
                    }
                    endline=false;
                }
                if (x=='\n'){
                    addNext(line,4);
                    line="";
                    endline=true;
                }
                else{ line=line+x;}
            }
            else if (index==2){
                if (x=='\n'){
                    if (body.size() > 0){
                        body = body + '\n' + line;
                        line = "";
                    }
                    else {
                        body = line;
                        line = "";
                    }
                }
                else if (x == '^'){
                    end_ = true;
                }
                else{ line=line+x;}
            }
        }



        if (line == "\0") {
            end_ = true;

        } else if (index == 0 | index == 1) {
            addNext(line, 4);
        } else if (body.size() > 0) {
            body = body + '\n' + line;
            line ="";
        } else {
            body = line;
            line = "";
        }
    }
}



void Message::execute(){
    int receiptid = user_->getAndIncrementreceiptId();
    reciptid = std::to_string(receiptid);

        if (type==error){
            if (body.find("already logged in")!=std::string::npos){
                std::cout << "User already logged in" <<std::endl;
                *user_->shouldTerminate() = true;

            }
            else if (body.find("Wrong Password")!=std::string::npos) {
                std::cout << "Wrong Password" <<std::endl;
                *user_->shouldTerminate() = true;
            }
        }

        if (type==returnn){
            Book* book = user_->getInv()->getAndRemoveBorrowedBooks(bookName,destination);
            if (book != nullptr) {
                toSend = "SEND\ndestination:" + destination + '\n' + '\n' + "Returning " + book->getName() + " to " +
                         book->getOwner() + '\n' + '\0';
            delete(book);
            }
        }

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

       if (type==wantToBorrow){ // this want to borrow a book
           user_->getWishList()->push_back(bookName);
       }
       if (type==recepit){

           if (beforeType==join){
               std::cout<<"Joined club "+getDestination()<<std::endl;
           }
           else if (beforeType==logout){
               std::cout<<"logging out... "+getDestination()<<std::endl;
               *user_->shouldTerminate() = true;
           }
           else if (beforeType==exitt){
               std::cout<<"Exited club "+getDestination()<<std::endl;
           }

           else{
              std::cout<<"beforeTYPE is invalid"<<std::endl;
           }
       }
       if (type==message){
            if(beforeType==add){
               std::cout<<""+userName+" has added the book "+bookName<<std::endl;
           }
           else if (body.find("wish to borrow")!=std::string::npos){ // someone wants to borrow a book
               type=CheckIfCanLoan;
           }
           else if (body.find("has added")!=std::string::npos){
               // add case
           }

           else if (body.find("Returning")!=std::string::npos){
               int posBookName=body.find("Returning") + 10;
               int posTo=body.find(" to ") ;
               int posOwner = posTo +4;
               std::string bookName = body.substr(posBookName,posTo-posBookName);
               std::string owner = body.substr(posOwner,body.length()-posOwner);
               if (user_->getName() == owner){ // the book was mine
                   std::vector<Book*>* vec = user_->getInv()->getLoanedBooks()->at(destination);
                   bool found = false;
                   Book* curr;
                   int it =0;
                   for (it = 0;!found & it < vec->size(); it ++) {
                       curr = vec->at(it);
                       if (curr->getName() == bookName){
                           found =true;
                       }
                   }
                   if (found) {
                       user_->getInv()->returnBook(curr, destination, user_->getName(), it-1);
                   }

                   // if i am the owner return to books
                   // if i am not the owner return to borrowed
               }
           }

           else if (body.find("has")!=std::string::npos){
               int pos=body.find("has");
               std::string bookToBorrow=body.substr((pos+4));
               std::string loaner=body.substr(0,pos-1);
               std::vector<std::string> *vec=  user_->getWishList();
               bool found = false;
               std::string book;
                 for(auto it = vec->begin();!found& it!= vec->end(); it++) {
                     book = *it;
                     if (book == bookToBorrow) {
                         found = true;
                     }
                 }
                 if (found){
                     Book* loanedBook = new Book(book,loaner,destination);
                     Inventory* inv =  user_->getInv();
                     inv->addLoanedBook(loanedBook);
                     toBorrow="SEND\ndestination:"+destination+'\n' + '\n'+"Taking "+loanedBook->getName()+" from "+loaner+'\n' +'\0';
                 }
           }
           else if (body.find("Taking")!=std::string::npos){
               int pos=body.find("from");
               std::string lender=body.substr(pos+5);
               if (lender==userName){
                   Inventory* inv =  user_->getInv();
                   int posa=body.find("Taking") + 7;
                   int posb=body.find("from");
                   std::string borrowed=body.substr(posa,posb-posa-1);
                   user_->moveToloaned(borrowed,destination);
               }

           }
       }
        if (type==CheckIfCanLoan){
            Inventory* inv =  user_->getInv();
        if (inv->hasBook(bookName,destination)){
            toSend="SEND\ndestination:"+destination+'\n' + '\n'+user_->getName()+" has "+bookName+'\n' + '\0';
        }
        }

       if (type == status){

       }

}

void  Message::loadFromBefore(Message* before){
    beforeType=before->type;
    bookName=before->getBookName();
    destination=before->getDestination();
//    if (beforeType==borrow){
//        Inventory* inv =  user_->getInv();
//        if (inv->hasBook(bookName,destination)){
//            toSend=""+user_->getName()+"has the book"+bookName;
//        }

}

void Message::addFirst(std::string msg){
    type = mapMessageType.at(msg);
    command = msg;
}



void Message::addNext(std::string msg,int index){
    ////// first add////////////////////////////
    if (index==1){
        if ( type == join| type ==add | type == wantToBorrow | type ==returnn | type == status| type == exitt){
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
        if (type ==add| type==wantToBorrow | type == returnn){
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
        else if (header=="message"){
            errormessage=msg.substr(pos+1);
        }


    }

    ///////////set body///////
    if(index==5){
        body=msg;
        if (msg.find("added the book")!=std::string::npos){
           int pos=msg.find("book");
           bookName=msg.substr(pos+5);
        }
        if (msg.find("wish to borrow")!=std::string::npos){
            type =CheckIfCanLoan;
            int i = msg.find("borrow");
            bookName = msg.substr(i+7);
        }
        if (msg.find("book status")!=std::string::npos){
            type = status;
        }
    }
    if (index ==6){
            body = msg;
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
std::string Message::getToSend(){
    return toSend;
}
std::string Message::getToBorrow(){
    return toBorrow;
}

void Message::loadMessageTypeMap(){
    mapMessageType.insert(std::make_pair("logout", MessageType::logout));
    mapMessageType.insert(std::make_pair("join", MessageType::join));
    mapMessageType.insert(std::make_pair("status", MessageType::status));
    mapMessageType.insert(std::make_pair("add", MessageType::add));
    mapMessageType.insert(std::make_pair("borrow", MessageType::wantToBorrow));
    mapMessageType.insert(std::make_pair("exit", MessageType::exitt));
    mapMessageType.insert(std::make_pair("login", MessageType::login));
    mapMessageType.insert(std::make_pair("return", MessageType::returnn));
    mapMessageType.insert(std::make_pair("CONNECTED", MessageType::connected));
    mapMessageType.insert(std::make_pair("RECEIPT", MessageType::recepit));
    mapMessageType.insert(std::make_pair("MESSAGE", MessageType::message));
    mapMessageType.insert(std::make_pair("ERROR", MessageType::error));


}


