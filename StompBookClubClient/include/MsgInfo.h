//
// Created by shachafk@wincs.cs.bgu.ac.il on 07/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_MSGINFO_H
#define BOOST_ECHO_CLIENT_MSGINFO_H


#include <map>
#include "../include/Message.h"

class MsgInfo {
public:

    MsgInfo();
    ~MsgInfo();
    void addToreceiptPerMsgMap(int id, Message* msg);
    Message* getMsgByReceiptId(int id);


private:
    std::map<int ,Message*> receiptPerMsgMap;
};


#endif //BOOST_ECHO_CLIENT_MSGINFO_H
