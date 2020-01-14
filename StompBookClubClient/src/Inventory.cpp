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


Inventory::Inventory(std::string username):username_(username),books_(),borrowedBooks_(),loanedBooks_(),booksMapLock(){}
Inventory::Inventory(const Inventory &other):username_(),books_(),borrowedBooks_(),loanedBooks_(),booksMapLock() {
    copy(other.username_,other.books_,other.borrowedBooks_,other.loanedBooks_);
}
void Inventory::copy(std::string other_username,std::map<std::string,std::vector<Book*>*> other_books,std::map<std::string,std::vector<Book*>*> other_borrowedBooks,
                     std::map<std::string,std::vector<Book*>*> other_loanedBooks){
    username_=other_username;
    books_.clear(); // memory leak ??
    for (auto it = other_books.begin(); it!=other_books.end();it++){ //delete all books
        books_.insert(*it);
    }
    borrowedBooks_.clear();// memory leak ??
    for (auto it = other_borrowedBooks.begin(); it!=other_borrowedBooks.end();it++){ //delete all books
        borrowedBooks_.insert(*it);
    }
    loanedBooks_.clear();// memory leak ??
    for (auto it = other_loanedBooks.begin(); it!=other_loanedBooks.end();it++){ //delete all books
        loanedBooks_.insert(*it);
    }

}
    void Inventory::addBook(Book* book){
       booksMapLock.lock();
        std::string genre = book->getGenre();
        if (books_.find(genre) != books_.end()){ //genre exist
            books_.at(genre)->push_back(book);
        }
        else { // new genre
            std::vector<Book*>* vec = new std::vector<Book*>;
            vec->push_back(book);
            books_.insert(std::make_pair(genre, vec));
        }
        booksMapLock.unlock();
    }

void Inventory::addLoanedBook(Book* book) {
    std::string genre = book->getGenre();
    booksMapLock.lock();
    if (borrowedBooks_.count(genre) > 0){ //genre exist
        borrowedBooks_.at(genre)->push_back(book);
    }
    else { // new genre
        std::vector<Book*>* vec = new std::vector<Book*>;
        vec->push_back(book);
        borrowedBooks_.insert(std::make_pair(genre, vec));
    }
    booksMapLock.unlock();

}

std::map<std::string,std::vector<Book*>*>* Inventory::getBooks() {
    return &books_;
}
std::map<std::string,std::vector<Book*>*>* Inventory::getBorrowedBooks(){
    return &borrowedBooks_;
}
std::map<std::string,std::vector<Book*>*>* Inventory::getLoanedBooks()  {
    return &loanedBooks_;
}


    bool Inventory::hasBook(std::string bookname,std::string genere){
    bool found = false;


        if(getBooks()->count(genere)>0 && !found){
            std::vector<Book*>* vec=  books_.at(genere);
            for(auto it = vec->begin(); it!= vec->end(); it++){
                Book* book = *it;
                if (book->getName() == bookname){
                    found = true;
                }
            }
        }

        if(getBorrowedBooks()->count(genere)>0 && !found){
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
        booksMapLock.lock(); // only one thread can return a book at a time
    if (book->getOwner() == userName){ // the book is mine return to books
        books_.at(genre)->push_back(book);
        loanedBooks_.at(genre)->erase(loanedBooks_.at(genre)->begin()+ index);
    }
    else { // the book is not mine, return to borrowed
        borrowedBooks_.at(genre)->push_back(book);
        loanedBooks_.at(genre)->erase(loanedBooks_.at(genre)->begin()+ index);
    }
        booksMapLock.unlock();
    }


Book* Inventory::getAndRemoveBorrowedBooks(std::string bookName,std::string genre){
        std::vector<Book *>* vec = borrowedBooks_.at(genre);
        Book *book;
        for (unsigned int i = 0; i < vec->size(); i++) {
            book = vec->at(i);
            booksMapLock.lock(); // only one thread can erase a book at a time
            if (book->getName() == bookName) {
                vec->erase(vec->begin()+i);
                return book;
            }
            booksMapLock.unlock();

        }
        return nullptr;
    }




 std::string Inventory::getStatus(std::string genre) {
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







