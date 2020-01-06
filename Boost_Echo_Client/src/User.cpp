//
// Created by shachafk@wincs.cs.bgu.ac.il on 06/01/2020.
//

#include "../include/User.h"


User::User(){
    Default=true;
    name = "defaultUser";
};
std::string User::getName(){
    return name;
}
bool User::isDefault(){
    return Default;
}