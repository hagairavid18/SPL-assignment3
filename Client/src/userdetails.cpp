//
// Created by hagairav@wincs.cs.bgu.ac.il on 06/01/2020.
//

#include <sstream>
#include "UserDetails.h"

UserDetails::UserDetails(string userName,string password):user_name(userName),subscription_id(0),receipt_id(0),password(password),subscription_vec(),_books(),receipt_vec(),wish_list(),login(1),mutex_for_books(),mutex_for_wishlist() {}
UserDetails::~UserDetails() {
    clean();
}


string UserDetails::getSubscriptionId()  {//we choose to return a string value although subscriptionId is integer from convenient issues

    stringstream ss;
    ss<<subscription_id;
    string ans=ss.str();
    subscription_id++;
    return ans;
}

string UserDetails::getReceiptId()  {//we choose to return a string value although receiptId is integer from convenient issues
    stringstream ss;
    ss<<receipt_id;
    string ans=ss.str();
    receipt_id++;
    return ans;
}

string UserDetails::getUserName()  {
    return user_name;
}

void UserDetails::addBook(string bookName, string owner,string genre) {
    std::lock_guard<std::mutex> lock(mutex_for_books);


    Book* newBook = new Book(bookName,owner, genre);
    _books.push_back(newBook);
}

void UserDetails::addToWishList(string bookName, string owner,string genre) {
    std::lock_guard<std::mutex> lock(mutex_for_wishlist);

    Book* newBook = new Book(bookName,owner,genre);
    wish_list.push_back(newBook);
}



Book* UserDetails::removeBook(string bookName) {
    std::lock_guard<std::mutex> lock(mutex_for_books);

    Book* bookToReturn;
    unsigned int i;
    for ( i = 0; i < _books.size(); i++) {
        if (_books[i]->getBookName().compare(bookName) == 0){
            break;
        }
    }
    if (i < _books.size()) {
        bookToReturn = _books[i];
        //delete _books[i];//the deletion will be after a frame will be made
        _books.erase(_books.begin()+i);
    }
    return bookToReturn;
}

void UserDetails::subscribe(string genre, string subscription_id) {//the function get a genre to subscribe, add the genre to subscription_vec, and return its new subscriptionId
    pair<string,string> pair(genre,subscription_id);
    subscription_vec.push_back(pair);
}

void UserDetails::unSubscribe(string genre) {//the function get a genre name, removes is from  subscription_vec,
    // and returns the genre subscription id (by string value)
    unsigned int i=0;
    for(i=0;i<subscription_vec.size();i++){
        if(subscription_vec[i].first.compare(genre)==0){
            break;
        }
    }
    if(i<subscription_vec.size()) subscription_vec.erase(subscription_vec.begin()+i);

}




 string UserDetails::getPassword() {
    return password;
}

vector<pair<string, string>> &UserDetails::getReceiptVec() {
    return receipt_vec;
}

string UserDetails::getSubscriptionIdByGenre(string genre) {

    unsigned int i=0;
    for(i=0;i<subscription_vec.size();i++){
        if(subscription_vec[i].first.compare(genre)==0){
            break;
        }
    }
    if(i<subscription_vec.size()){
        string subscriptionId= subscription_vec[i].second;
        return subscriptionId;
    }
    return "";



}

Book* UserDetails::getBook(string book_name) {
    std::lock_guard<std::mutex> lock(mutex_for_books);
    for (unsigned int i = 0; i < _books.size() ; ++i) {
        if( _books.at(i)->getBookName().compare(book_name) == 0){
            return _books.at(i);
        }
    }


    return nullptr ;
}

string UserDetails::getBooksByGenre(string genre) {
    std::lock_guard<std::mutex> lock(mutex_for_books);
    string ans("");
    for (unsigned int i = 0; i < _books.size() ; ++i) {
        if( (_books.at(i)->getGenre().compare(genre) == 0) &  (_books.at(i)->isAvailable())){
            ans +=  _books.at(i)->getBookName() + ", ";

        }
    }
    if (ans.compare("") !=0) return ans.substr(0,ans.size()-2);



    return ans ;



}

bool UserDetails::checkIfInterested(string book_name) {
    std::lock_guard<std::mutex> lock(mutex_for_wishlist);
    for (unsigned int i = 0; i < wish_list.size() ; ++i) {
        if( wish_list.at(i)->getBookName().compare(book_name) == 0){
            delete wish_list[i];
            wish_list.erase(wish_list.begin()+i);
            return true;

        }
    }

    return false;
}

string UserDetails::getReceiptResponse(string receiptId) {
    string response="";



    for(unsigned int i=0;i<receipt_vec.size();i++){
        if((receipt_vec[i].first.compare(receiptId))==0){
            response=receipt_vec[i].second;
            return response;
        }
    }

    return response;
}

int UserDetails::getLogin() {
    return login;
}

void UserDetails::setLogin(int login) {
    UserDetails::login = login;
}

void UserDetails::clean() {


    subscription_id=0;
    receipt_id=0;
    subscription_vec.clear();
    user_name="";
    for(unsigned int i=0;i<_books.size();i++) {
        delete _books[i];
        _books.erase(_books.begin()+i);
    }
    _books.clear();
//    for(auto iter=receipt_map.begin();iter!=receipt_map.end();++iter){//not sure if needed
//        delete(iter.operator->()->second);
//    }
    receipt_vec.clear();
    for(unsigned int i=0;i<wish_list.size();i++)
        delete wish_list[i];
    wish_list.clear();
    login=0;//logged out
}

void UserDetails::setUserName( string &userName) {
    user_name = userName;
}

void UserDetails::setPassword( string &password) {
    UserDetails::password = password;
}

void UserDetails::addReceipt(pair<string,string> res) {
    receipt_vec.push_back(res);

}

vector<pair<string, string>>& UserDetails::getSubscriptionVec() {
    return subscription_vec;
}





