//
// Created by shachafk@wincs.cs.bgu.ac.il on 07/01/2020.
//

#include "../include/MsgInfo.h"


MsgInfo::MsgInfo(){
    receiptPerMsgMap = new std::map<int,Message>;
}


MsgInfo::~MsgInfo(){
    for (auto it = receiptPerMsgMap.begin();it!=receiptPerMsgMap.end();it++ ){
        delete(it->second); // delete all msgs
    }
    receiptPerMsgMap.clear();
}
void MsgInfo::addToreceiptPerMsgMap(int id, Message* msg){
    receiptPerMsgMap.insert(std::make_pair(id,msg));

}
Message* MsgInfo::getMsgByReceiptId(int id){
    return receiptPerMsgMap.find(id)->second;
}