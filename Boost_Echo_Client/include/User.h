//
// Created by shachafk@wincs.cs.bgu.ac.il on 06/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_USER_H
#define BOOST_ECHO_CLIENT_USER_H


#include <string>

class User {

public:
    User();
    std::string getName();
    bool isDefault();
private:
    std::string name;
    bool Default ;

};


#endif //BOOST_ECHO_CLIENT_USER_H
