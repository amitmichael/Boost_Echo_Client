//
// Created by shachafk@wincs.cs.bgu.ac.il on 06/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_INVENTORY_H
#define BOOST_ECHO_CLIENT_INVENTORY_H


#include <map>
#include <vector>
#include "Book.h"

class Inventory {

public:
    Inventory();
    Inventory(std::string username);
    ~Inventory();
    void addBook(Book* book);
   // User returnBook(std::string genre,std::string bookname);
   // void returnBorrowedBookToOwner(std::string genre,Book book);
    std::map<std::string,std::vector<Book*>*> getBooks();
    std::map<std::string,std::vector<Book*>*> getBorrowedBooks();


private:
    std::map<std::string,std::vector<Book*>*> books_;
    std::map<std::string,std::vector<Book*>*> borrowedBooks_;
    std::string username_;



};


#endif //BOOST_ECHO_CLIENT_INVENTORY_H
