//
// Created by shachafk@wincs.cs.bgu.ac.il on 06/01/2020.
//

#include "../include/Frame.h"


Frame::Frame(boost::asio::streambuf &stomp_response) {
    loadStringValuesMap();

        while (stomp_response.size() > 0){

        }


}

void Frame::loadStringValuesMap() {
    s_mapStringValues.insert(std::make_pair("CONNECT", StringValue::CONNECT));
    s_mapStringValues.insert(std::make_pair("DISCONNECT", StringValue::DISCONNECT));
    s_mapStringValues.insert(std::make_pair("SUBSCRIBE", StringValue::SUBSCRIBE));
    s_mapStringValues.insert(std::make_pair("UNSUBSCRIBE", StringValue::UNSUBSCRIBE));
    s_mapStringValues.insert(std::make_pair("SEND", StringValue::SEND));
}