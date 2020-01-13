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
    ~User();
    std::string getName();
    bool isDefault();
    const Inventory* getInv();
    int getAndIncrementSubscriptionId();
    int getAndIncrementreceiptId();
    void addToGenreSubIdmap(std::string genre ,int id);
    void removeFromenreSubIdmap(std::string genre);
    int getSubIdByGenre(std::string genre);
    void setName(std::string name);
    const bool* isConnected();
    const bool* shouldTerminate();
    void setTermination(bool toTerminate);
    void moveToloaned(std::string borrowed,std::string genere);
    std::vector<std::string>* getWishList() ;
    void copy(const bool* connected,const bool* shouldTerminated, std::string name, bool Default,const Inventory* inventory_,int subscriptionIdCounter,int receiptId,std::vector<std::string> wishList);
private:
    std::map<std::string,int> genreSubIMmap;
    const bool* connected;
    const bool* shouldTerminate_;
    std::string name_;
    bool Default;
    const Inventory* inventory_;
    int subscriptionIdCounter;
    int receiptId;
    std::vector<std::string> wishList;


};


#endif //BOOST_ECHO_CLIENT_USER_H
