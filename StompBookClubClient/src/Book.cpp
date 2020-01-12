//
// Created by shachafk@wincs.cs.bgu.ac.il on 06/01/2020.
//

#include <string>
#include "../include/Book.h"

Book::Book(std::string name,std::string owner,std::string genre):name_(name),owner_(owner),loaner_(),genre_(genre){}


std::string Book::getName(){
    return name_;
}
std::string Book::getOwner(){
    return owner_;
}
std::string Book::getLoaner(){
    return loaner_;
}
std::string Book::getGenre() {
    return genre_;
}