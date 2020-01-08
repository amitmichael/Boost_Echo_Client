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
}


Inventory::Inventory(std::string username):username_(username),books_(),borrowedBooks_(){}

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






