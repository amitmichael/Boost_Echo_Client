//
// Created by shachafk@wincs.cs.bgu.ac.il on 06/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_STOMPENCODERDECODER_H
#define BOOST_ECHO_CLIENT_STOMPENCODERDECODER_H


#include <string>
#include "Message.h"

class StompEncoderDecoder {

private:
    User user_;
    std::vector<char> bytesVector_;

public:
    StompEncoderDecoder(User user);
    ~StompEncoderDecoder();
    std::string encode(Message msg);
    std::string decodeNextByte(char byte);
    std::string toString(Message m);
    Message parseMsgFromKeyboard(std::string basicString);

    Message parseMsgFromSocket(char nextbyte);
};


#endif //BOOST_ECHO_CLIENT_STOMPENCODERDECODER_H
