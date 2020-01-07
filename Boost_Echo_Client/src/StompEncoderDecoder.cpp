//
// Created by shachafk@wincs.cs.bgu.ac.il on 06/01/2020.
//

#include "../include/StompEncoderDecoder.h"
#include "../include/Message.h"


StompEncoderDecoder::StompEncoderDecoder(User user):user_(user){}
StompEncoderDecoder::~StompEncoderDecoder(){}
std::string StompEncoderDecoder::encode(std::string msg){



}
std::string StompEncoderDecoder::decodeNextByte(char byte){}


std::string StompEncoderDecoder::toString(Message m) {
    std::string toReturn= "";
    if (m.getType() == add ){
        toReturn = "SEND\ndestination:" + m.getDestination() +'\n' + '\n' + m.getUserName()+" has added the book "+ m.getBookName() + '\n' + '\0';
    }


    return toReturn;
}




std::string StompEncoderDecoder::parseMsgFromKeyboard(std::string msg) {

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
    parsedMsg.addNext(word,index);
    return toString(parsedMsg);

}
