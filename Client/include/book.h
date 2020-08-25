//
// Created by hagairav@wincs.cs.bgu.ac.il on 07/01/2020.
//

#include <string>
#include <iostream>
using namespace std;

#ifndef BOOST_ECHO_CLIENT_BOOK_H
#define BOOST_ECHO_CLIENT_BOOK_H


#endif //BOOST_ECHO_CLIENT_BOOK_H
class Book {
private:
    string book_name;
    string owner;
    string genre;
    bool is_available;


public:
    Book(string book_name,string owner, string genre);

    Book();

    virtual ~Book();

    string getBookName();

     string &getOwner() ;

     string &getGenre() ;

    bool isAvailable() ;

    void setAvailable(bool set);

};