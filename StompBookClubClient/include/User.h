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
    ~User();
    std::string getName();
    bool isDefault();
    Inventory* getInv();
    int getAndIncrementSubscriptionId();
    int getAndIncrementreceiptId();
    void addToGenreSubIdmap(std::string genre ,int id);
    void removeFromenreSubIdmap(std::string genre);
    int getSubIdByGenre(std::string genre);
    void setName(std::string name);
    bool* isConnected();
    bool* shouldTerminate();
    void setTermination(bool toTerminate);
    void moveToBorrowed(std::string borrowed,std::string genere);
    std::vector<std::string>* getWishList() ;

private:
    std::string name_;
    bool Default;
    Inventory* inventory_;
    int subscriptionIdCounter;
    int receiptId;
    std::vector<std::string> wishList;


private:

    bool* connected;
    bool* shouldTerminate_;
    std::map<std::string,int> genreSubIMmap;


};


#endif //BOOST_ECHO_CLIENT_USER_H
