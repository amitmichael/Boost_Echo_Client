//
// Created by shachafk@wincs.cs.bgu.ac.il on 06/01/2020.
//

#include "../include/StompEncoderDecoder.h"
#include "../include/Message.h"


StompEncoderDecoder::StompEncoderDecoder(User* user):user_(user),bytes(){}
StompEncoderDecoder::StompEncoderDecoder(const StompEncoderDecoder &other): user_(),bytes(){
    copy (other.user_);
}
StompEncoderDecoder& StompEncoderDecoder::operator=(const StompEncoderDecoder &other){
    if (this!=&other){
        copy (other.user_);
    }
    return *this;
}
void StompEncoderDecoder::copy (User* other_user){
    user_=other_user;
}
StompEncoderDecoder::~StompEncoderDecoder(){
    delete (bytes);
}

std::string StompEncoderDecoder::encode(Message* msg){

    return toString(msg);

}
std::string StompEncoderDecoder::decodeNextByte(char byte){
    if(byte=='\0') {
        std::string toReturn(bytes->begin(),bytes->end());
    }
    bytes->push_back(byte);
    return "";  //not message yet
}


std::string StompEncoderDecoder::toString(Message* m) {
    std::string toReturn= "";
    if (m->getType() == add ){
        toReturn = "SEND\ndestination:" + m->getDestination() +'\n' + '\n' + m->getUser()->getName()+" has added the book "+ m->getBookName() + '\n' + '\0';
    }
    if (m->getType() == join){

        toReturn = "SUBSCRIBE\ndestination:" + m->getDestination() +'\n' +"id:" + m->getSubscriptionId() + '\n' + "receipt:" + m->getreciptid() + '\n' + '\n' + '\0';
    }
    if (m->getType() == exitt){
        toReturn = "UNSUBSCRIBE\ndestination:" + m->getDestination() +'\n' +"id:" + m->getSubscriptionId() + '\n' + "receipt:" + m->getreciptid() + '\n' + '\n' + '\0';
    }
    if (m->getType() == login){
        toReturn = "CONNECT\naccept-version:1.2\nhost:" +m->getHost()+ ":" +std::to_string(m->getPort())+ '\n'+ "login:" + m->getUserName() + '\n' + "passcode:" + m->getPassword() + '\n' + '\n' + '\0';
    }
    if (m->getType() == wantToBorrow){
        toReturn = "SEND\ndestination:" + m->getDestination() +'\n' + '\n' + m->getUserName() + " wish to borrow " + m->getBookName() + '\n' + '\0';

    }
    if (m->getType() == returnn){
        //Book* book = get
       // toReturn = "SEND\ndestination:" + m->getDestination() +'\n' + '\n'  + "Returning " + m->getBookName() + " to " + "" + '\n' + '\0';
    }
    if (m->getType() == status){
        toReturn = "SEND\ndestination:" + m->getDestination() +'\n' + '\n'  + "Book status"  + '\n' + '\0';
    }
    if (m->getType() == logout){
        toReturn = "DISCONNECT\nreceipt:" + m->getreciptid() + '\n'  + '\n' + '\0';
    }
    if (m->getType() == statusResponse){
        std::string bodyToSend =user_->getName() + ":" ;
        Inventory* inv =  user_->getInv();
        bodyToSend = bodyToSend + inv->getStatus(m->getDestination());
        toReturn = "SEND\ndestination:" + m->getDestination() +'\n' + '\n'  + bodyToSend + '\n' + '\0';
    }


    return toReturn;
}


Message* StompEncoderDecoder::parseMsgFromKeyboard(std::string msg) {

    std::string word = "";
    int index =0;
    Message* parsedMsg = new Message(user_);
    for (auto x: msg){
        if (x == ' '){
            if (index==0) { //first word
                parsedMsg->addFirst(word);
                word = "";
                index++;
            }
            else {
                parsedMsg->addNext(word,index);
                word = "";
                index++;

            }
        }
        else {
            word = word+x;
        }
    }
    if (index==0){
        parsedMsg->addFirst(word);
    }
    else {
        parsedMsg->addNext(word, index);
    }
    return parsedMsg;

}
Message* StompEncoderDecoder::parseMsgFromSocket(std::string msg){
    if (msg.size()==0){
        return nullptr;
    }
    int index =0;
    std::string line="";
    bool endline=false;
    bool emptyline=false;
    Message* parsedMsg = new Message(user_) ;
    int len = msg.size();
    int i = 0;
    for(auto x:msg){
        i++;
        if(index==0){
            if (x == '\n') {
                parsedMsg->addFirst(line);
                line="";
                index++;
            }
            else{
                line=line+x;
            }
        }
        if (emptyline){
            index++;
            emptyline= false;
        }
        if (index==1){ //headers parse
            if(endline){ //checks if it is an empty line and skip it
                if (x=='\n'){
                 endline=false;
                 emptyline=true;
                 continue;
                }
                endline=false;
            }
            if (x=='\n'){
                parsedMsg->addNext(line,4);
                line="";
                endline=true;
            }
            else{ line=line+x;}
        }
         else if (index==2){

            if (x=='\n'||x=='\0'){
                parsedMsg->addNext(line,5);
                return parsedMsg;
            }


            else{ line=line+x;}
        }
    }
    if (i==len){
        parsedMsg->addNext(line,5);
        return parsedMsg;
    }
    return parsedMsg;
}
