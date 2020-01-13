//
// Created by shachafk@wincs.cs.bgu.ac.il on 06/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_USER_H
#define BOOST_ECHO_CLIENT_USER_H


#include <string>
#include "../include/Inventory.h"


class User {

public:
    User(bool* connected, bool* shouldTerminate);
    User(const User &other);
    User& operator=(const User &other);
    ~User();
    void copy(bool* connected,bool* shouldTerminated, std::string name, bool Default,const Inventory* inventory_,int subscriptionIdCounter,int receiptId,std::vector<std::string> wishList);
    void clear();
    std::string getName();
    Inventory* getInv();
    int getAndIncrementSubscriptionId();
    int getAndIncrementreceiptId();
    void addToGenreSubIdmap(std::string genre ,int id);
    void removeFromenreSubIdmap(std::string genre);
    int getSubIdByGenre(std::string genre);
    void setName(std::string name);
    bool*  isConnected();
    bool*  shouldTerminate();
    void moveToloaned(std::string borrowed,std::string genere);
    std::vector<std::string>* getWishList() ;
private:
    std::map<std::string,int> genreSubIMmap;
    bool* connected;
    bool* shouldTerminate_;
    std::string name_;
    bool Default;
    Inventory* inventory_;
    int subscriptionIdCounter;
    int receiptId;
    std::vector<std::string> wishList;


};


#endif //BOOST_ECHO_CLIENT_USER_H
