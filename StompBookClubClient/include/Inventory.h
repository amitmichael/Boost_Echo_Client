//
// Created by shachafk@wincs.cs.bgu.ac.il on 06/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_INVENTORY_H
#define BOOST_ECHO_CLIENT_INVENTORY_H


#include <map>
#include <vector>
#include <mutex>
#include "Book.h"

class Inventory {

public:
    Inventory();
    Inventory(std::string username);
    Inventory(const Inventory &other);
    void copy(std::string username,std::map<std::string,std::vector<Book*>*> books_,std::map<std::string,std::vector<Book*>*> borrowedBooks_,
    std::map<std::string,std::vector<Book*>*> loanedBooks_);
    ~Inventory();
    void addBook(Book* book);
    bool hasBook(std::string bookname,std::string genere) ;
    Book* getAndRemoveBorrowedBooks(std::string bookName,std::string genre) ;
   std::map<std::string,std::vector<Book*>*>* getBooks() ;
   std::map<std::string,std::vector<Book*>*>* getBorrowedBooks();
   std::map<std::string,std::vector<Book*>*>* getLoanedBooks() ;
    void returnBook(Book* book,std::string genre,std::string userName,int index);
    std::string getStatus(std::string genre);
    void addLoanedBook(Book* book) ;



    private:
    std::string username_;
    std::map<std::string,std::vector<Book*>*> books_; // key - genre , vector of books
    std::map<std::string,std::vector<Book*>*> borrowedBooks_;
    std::map<std::string,std::vector<Book*>*> loanedBooks_;
    std::mutex booksMapLock;




};


#endif //BOOST_ECHO_CLIENT_INVENTORY_H
