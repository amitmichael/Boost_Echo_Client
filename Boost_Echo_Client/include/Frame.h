//
// Created by shachafk@wincs.cs.bgu.ac.il on 06/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_FRAME_H
#define BOOST_ECHO_CLIENT_FRAME_H


#include <boost/asio/streambuf.hpp>
#include <map>



class Frame {

    enum StringValue {CONNECT,
        DISCONNECT,
        SUBSCRIBE,
        UNSUBSCRIBE,
        SEND};

private:
    std::map<std::string, StringValue> s_mapStringValues;


public:
    Frame(boost::asio::streambuf& stomp_response);
    void loadStringValuesMap();

};


#endif //BOOST_ECHO_CLIENT_FRAME_H
