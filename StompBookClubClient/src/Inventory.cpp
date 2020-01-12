//
// Created by shachafk@wincs.cs.bgu.ac.il on 06/01/2020.
//

#include <string>
#include "../include/Inventory.h"


Inventory::~Inventory(){

    for (auto it = books_.begin(); it!=books_.end();it++){ //delete all books
        std::vector<Book*>* curr = it->second;
        for (auto itt = curr->begin(); itt!= curr->end();itt++) {
            delete (*itt);// delete all books in the vector
        }
        delete (curr);
    }
    for (auto it1 = borrowedBooks_.begin(); it1!=borrowedBooks_.end();it1++){ // delete all borrowed books
        std::vector<Book*>* curr = it1->second;
        for (auto itt = curr->begin(); itt!= curr->end();itt++) {
            delete (*itt);// delete all books in the vector
        }
        delete (curr);
    }
    for (auto it2 = loanedBooks_.begin(); it2!=loanedBooks_.end();it2++){ // delete all loaned books
        std::vector<Book*>* curr = it2->second;
        for (auto itt = curr->begin(); itt!= curr->end();itt++) {
            delete (*itt);// delete all books in the vector
        }
        delete (curr);
    }
}


Inventory::Inventory(std::string username):username_(username),books_(),borrowedBooks_(),loanedBooks_(){}

    void Inventory::addBook(Book* book){
        std::string genre = book->getGenre();
        if (books_.find(genre) != books_.end()){ //genre exist
            books_.at(genre)->push_back(book);
        }
        else { // new genre
            std::vector<Book*>* vec = new std::vector<Book*>;
            vec->push_back(book);
            books_.insert(std::make_pair(genre, vec));
        }
    }

void Inventory::addLoanedBook(Book* book){
    std::string genre = book->getGenre();
    if (borrowedBooks_.find(genre) != borrowedBooks_.end()){ //genre exist
        borrowedBooks_.at(genre)->push_back(book);
    }
    else { // new genre
        std::vector<Book*>* vec = new std::vector<Book*>;
        vec->push_back(book);
        borrowedBooks_.insert(std::make_pair(genre, vec));
    }
}

std::map<std::string,std::vector<Book*>*>* Inventory::getBooks(){
    return &books_;
}
std::map<std::string,std::vector<Book*>*>* Inventory::getBorrowedBooks(){
    return &borrowedBooks_;
}

    bool Inventory::hasBook(std::string bookname,std::string genere){
    bool found = false;


        if(getBooks()->count(genere)>0 & !found){
            std::vector<Book*>* vec=  books_.at(genere);
            for(auto it = vec->begin(); it!= vec->end(); it++){
                Book* book = *it;
                if (book->getName() == bookname){
                    found = true;
                }
            }
        }

        if(getBorrowedBooks()->count(genere)>0 & !found){
            std::vector<Book*>* vec=  borrowedBooks_.at(genere);
            for(auto it = vec->begin(); it!= vec->end(); it++){
                Book* book = *it;
                if (book->getName() == bookname){
                    found = true;
                }
            }
        }

        return found;

    }
    void Inventory::returnBook(Book* book,std::string genre,std::string userName,int index){
    if (book->getOwner() == userName){ // the book is mine return to books
        books_.at(genre)->push_back(book);
        loanedBooks_.at(genre)->erase(loanedBooks_.at(genre)->begin()+ index);
    }
    else { // the book is not mine, return to borrowed
        borrowedBooks_.at(genre)->push_back(book);
        loanedBooks_.at(genre)->erase(loanedBooks_.at(genre)->begin()+ index);
    }
    }


Book* Inventory::getAndRemoveBorrowedBooks(std::string bookName,std::string genre){
        std::vector<Book *>* vec = borrowedBooks_.at(genre);
        Book *book;
        for (int i = 0; i < vec->size(); i++) {
            book = vec->at(i);
            if (book->getName() == bookName) {
                vec->erase(vec->begin()+i);
                return book;
            }
        }
        return nullptr;
    }
std::map<std::string,std::vector<Book*>*>* Inventory::getLoanedBooks(){
    return &loanedBooks_;
}




std::string Inventory::getStatus(std::string genre){
        std::string toReturn;

        if (books_.count(genre) > 0) {
            std::vector<Book *> *vec = books_.at(genre);
            if (vec != nullptr) {
                for (auto it = vec->begin(); it != vec->end(); it++) {
                    Book *book = *it;
                    toReturn = toReturn + book->getName() + ",";
                }

            }
        }

        if (borrowedBooks_.count(genre)> 0) {
            std::vector<Book *> *vec1 = borrowedBooks_.at(genre);
            if (vec1 != nullptr) {
                for (auto it = vec1->begin(); it != vec1->end(); it++) {
                    Book *book = *it;
                    toReturn = toReturn + book->getName() + ",";
                }

            }
        }

        if (toReturn.size() > 0) {
            toReturn = toReturn.substr(0, toReturn.size() - 1); // remove last comma
        }

        return toReturn;
    }







