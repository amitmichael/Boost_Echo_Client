//
// Created by shachafk@wincs.cs.bgu.ac.il on 06/01/2020.
//

#include "../include/User.h"


User::~User() {
    delete(inventory_);
    delete(genreSubIMmap);
}

User::User(){
    Default=true;
    name = "defaultUser";
    inventory_ = new Inventory(name);
    subscriptionIdCounter=0;
    receiptId=0;
    genreSubIMmap = new std::map<std::string,int>;

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

int User::getAndIncrementSubscriptionId(){
    subscriptionIdCounter++;
    return subscriptionIdCounter;
}

void User::addToGenreSubIdmap(std::string genre ,int id){
    genreSubIMmap->insert(std::make_pair(genre,id));
}

void User::removeFromenreSubIdmap(std::string genre){
    genreSubIMmap->erase(genre);
}



int User::getAndIncrementreceiptId(){
    receiptId++;
    return receiptId;
}

int User::getSubIdByGenre(std::string genre){
    return genreSubIMmap->find(genre)->second;
}
