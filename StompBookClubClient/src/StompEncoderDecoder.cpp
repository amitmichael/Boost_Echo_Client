//
// Created by shachafk@wincs.cs.bgu.ac.il on 06/01/2020.
//

#include "../include/StompEncoderDecoder.h"
#include "../include/Message.h"


StompEncoderDecoder::StompEncoderDecoder(User* user):user_(user){}
StompEncoderDecoder::~StompEncoderDecoder(){}

std::string StompEncoderDecoder::encode(Message* msg){

    return toString(msg);

}
std::string StompEncoderDecoder::decodeNextByte(char byte){
    if(byte=='\0') {
        std::string toReturn="";
        for (auto it = bytes->begin() ; it != bytes->end(); ++it){
          //  toReturn+=(char) it;
    }
    bytes->push_back(byte);
    return "";  //not message yet
}
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
    if (m->getType() == borrow){
        toReturn = "SEND\ndestination:" + m->getDestination() +'\n' + '\n' + m->getUserName() + " wish to borrow " + m->getBookName() + '\n' + '\0';

    }
    if (m->getType() == returnn){
        toReturn = "SEND\ndestination:" + m->getDestination() +'\n' + '\n'  + "Returning " + m->getBookName() + " to TBD" + '\n' + '\0';
    }
    if (m->getType() == status){
        toReturn = "SEND\ndestination:" + m->getDestination() +'\n' + '\n'  + "book status"  + '\n' + '\0';
    }
    if (m->getType() == logout){
        toReturn = "DISCONNECT\nreceipt:" + m->getreciptid() + '\n'  + '\n' + '\0';
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
    int index =0;
    std::string line="";
    bool endline=false;
    bool emptyline=false;
    Message* parsedMsg = new Message(user_) ;
    for(auto x:msg){
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
        }
        if (index==1){
            if(endline){ //checks if it is an empty line and skip it
                if (x=='\n'){
                 index++;
                 endline=false;
                 continue;
                }
                endline=false;
            }
            if (x=='\n'){
                parsedMsg->addNext(line,4);
                line="";
                endline=true;
            }
            line=line+x;
        }
        if (index==2){
            if (x=='\n'){
                parsedMsg->addNext(line,5);
            }
        }
    }
    return parsedMsg;
}
