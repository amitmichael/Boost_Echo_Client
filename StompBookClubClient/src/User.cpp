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

User::User(bool* connected, bool* shouldTerminate):genreSubIMmap(),connected(connected),shouldTerminate_(shouldTerminate),name_(),Default(),inventory_(),subscriptionIdCounter(),receiptId(),wishList(){
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
    if (genreSubIMmap.count(genre)> 0)
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
void User::setTermination(bool toTerminate){
    *shouldTerminate()=toTerminate;
}

std::vector<std::string>* User::getWishList() {
    return &wishList;
}


void User::moveToloaned(std::string borrowed,std::string genere) {
    Inventory *inv = getInv();
    Book *book;
    //// books/////
    bool found = false;
    if (inv->getBooks()->count(genere) > 0) {
        std::vector<Book *> *vec = inv->getBooks()->at(genere);
        for (int i = 0; !found & i < vec->size(); i++) {
            book = vec->at(i);
            if (book->getName() == borrowed) {
                found = true;
                vec->erase(vec->begin() + i);
            }
        }
    }
    //// borrowed ////
    if (inv->getBorrowedBooks()->count(genere) > 0) {
        std::vector<Book *> *vec1 = inv->getBorrowedBooks()->at(genere);
        for (int i = 0; !found & i < vec1->size(); i++) {
            book = vec1->at(i);
            if (book->getName() == borrowed) {
                found = true;
                vec1->erase(vec1->begin() + i);

            }
        }
    }

    if (found) { // add to loaned
        if (inv->getLoanedBooks()->count(genere) > 0) {
            inv->getLoanedBooks()->at(genere)->push_back(book);
        } else {
            std::vector<Book *> *vec2 = new std::vector<Book *>;
            inv->getLoanedBooks()->insert(std::make_pair(genere, vec2));
            inv->getLoanedBooks()->at(genere)->push_back(book);
        }
    }
}




