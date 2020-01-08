//
// Created by shachafk@wincs.cs.bgu.ac.il on 06/01/2020.
//

#include "../include/User.h"


User::~User() {
    delete(inventory_);
    delete(connected);
    delete(shouldTerminate_);
}

std::string User::getName(){
    return name_;
}

User::User(bool* connected, bool* shouldTerminate):genreSubIMmap(),connected(connected),shouldTerminate_(shouldTerminate){
    Default=true;
    name_ = "defaultUser";
    inventory_ = new Inventory(name_);
    subscriptionIdCounter=0;
    receiptId=0;

};

bool* User::isConnected(){
    return connected;
}

bool* User::shouldTerminate(){
    return shouldTerminate_;
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
    genreSubIMmap.insert(std::make_pair(genre,id));
}


void User::removeFromenreSubIdmap(std::string genre){
    genreSubIMmap.erase(genre);
}



int User::getAndIncrementreceiptId(){
    receiptId++;
    return receiptId;
}

int User::getSubIdByGenre(std::string genre){

    return genreSubIMmap.find(genre)->second;
}

void User::setName(std::string name){
    name_ = name;
}

