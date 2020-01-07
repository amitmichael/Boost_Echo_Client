//
// Created by shachafk@wincs.cs.bgu.ac.il on 06/01/2020.
//

#include "../include/StompEncoderDecoder.h"
#include "../include/Message.h"


StompEncoderDecoder::StompEncoderDecoder(User* user):user_(user){}
StompEncoderDecoder::~StompEncoderDecoder(){}
std::string StompEncoderDecoder::encode(Message msg){

    return toString(msg);

}
std::string StompEncoderDecoder::decodeNextByte(char byte){}


std::string StompEncoderDecoder::toString(Message m) {
    std::string toReturn= "";
    if (m.getType() == add ){
        toReturn = "SEND\ndestination:" + m.getDestination() +'\n' + '\n' + m.getUser()->getName()+" has added the book "+ m.getBookName() + '\n' + '\0';
    }
    if (m.getType() == join){

        toReturn = "SUBSCRIBE\ndestination:" + m.getDestination() +'\n' +"id:" + m.getSubscriptionId() + '\n' + "receipt:" + m.getreciptid() + '\n' + '\n' + '\0';
    }
    if (m.getType() == exitt){
        toReturn = "UNSUBSCRIBE\ndestination:" + m.getDestination() +'\n' +"id:" + m.getSubscriptionId() + '\n' + "receipt:" + m.getreciptid() + '\n' + '\n' + '\0';
    }
    if (m.getType() == login){
        toReturn = "CONNECT\naccept-version:1.2\nhost:" +m.getHost()+ ":" +std::to_string(m.getPort())+ '\n'+ "login:" + m.getUserName() + '\n' + "passcode:" + m.getPassword() + '\n' + '\n' + '\0';
    }
    if (m.getType() == borrow){
        toReturn = "SEND\ndestination:" + m.getDestination() +'\n' + '\n' + m.getUserName() + " wish to borrow " + m.getBookName() + '\n' + '\0';

    }
    if (m.getType() == returnn){
        toReturn = "SEND\ndestination:" + m.getDestination() +'\n' + '\n'  + "Returning " + m.getBookName() + " to TBD" + '\n' + '\0';
    }
    if (m.getType() == status){
        toReturn = "SEND\ndestination:" + m.getDestination() +'\n' + '\n'  + "book status"  + '\n' + '\0';
    }
    if (m.getType() == logout){
        toReturn = "DISCONNECT\nreceipt:" + m.getreciptid() + '\n'  + '\n' + '\0';
    }


    return toReturn;
}




Message StompEncoderDecoder::parseMsgFromKeyboard(std::string msg) {

    std::string word = "";
    int index =0;
    Message parsedMsg(user_) ;
    for (auto x: msg){
        if (x == ' '){
            if (index==0) { //first word
                parsedMsg.addFirst(word);
                word = "";
                index++;
            }
            else {
                parsedMsg.addNext(word,index);
                word = "";
                index++;
            }
        }
        else {
            word = word+x;
        }
    }
    if (index==0){
        parsedMsg.addFirst(word);
    }
    else {
        parsedMsg.addNext(word, index);
    }
    return parsedMsg;

}
