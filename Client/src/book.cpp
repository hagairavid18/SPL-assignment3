//
// Created by hagairav@wincs.cs.bgu.ac.il on 07/01/2020.
//

//#include <bits/basic_string.h>
#include <Book.h>

string Book::getBookName() {
    return book_name;
}
string& Book::getGenre() {
    return genre;
}
string& Book::getOwner() {
    return owner;
}
bool Book::isAvailable() {
    return is_available;
}

Book::Book(string book_name, string owner, string genre):book_name(book_name), owner(owner),genre(genre), is_available(true) {
}

Book::Book():book_name(),owner(),genre(),is_available() {}

void Book::setAvailable(bool set) {


    is_available = set;

}

Book::~Book() {}
