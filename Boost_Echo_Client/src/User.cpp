//
// Created by shachafk@wincs.cs.bgu.ac.il on 06/01/2020.
//

#include "../include/User.h"


User::~User() {
    delete(inventory_);
}

User::User(){
    Default=true;
    name = "defaultUser";
    inventory_ = new Inventory(name);
};
std::string User::getName(){
    return name;
}
bool User::isDefault(){
    return Default;
}

Inventory* User::getInv(){
    return inventory_;
}
