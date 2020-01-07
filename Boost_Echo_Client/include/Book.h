//
// Created by shachafk@wincs.cs.bgu.ac.il on 06/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_BOOK_H
#define BOOST_ECHO_CLIENT_BOOK_H


class Book {


public:
    Book(std::string name,std::string owner,std::string genre);
    std::string getName();
    std::string getOwner();
    std::string getLoaner();
    std::string getGenre();

private:
    std::string name_;
    std::string owner_;
    std::string loaner_;
    std::string genre_;


};


#endif //BOOST_ECHO_CLIENT_BOOK_H
