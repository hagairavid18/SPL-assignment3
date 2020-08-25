//
// Created by hagairav@wincs.cs.bgu.ac.il on 06/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_USERDETAILS_H
#define BOOST_ECHO_CLIENT_USERDETAILS_H

#include <string>
#include <vector>
#include "Book.h"
#include <map>
#include <mutex>

using namespace std;


class UserDetails {
private:
    string user_name;
    int subscription_id;
    int receipt_id;
    string password;
    vector<pair<string,string>>  subscription_vec; //each pair represent a genre, and its subscription id- in this order
    vector<Book*> _books; //represent the book library of a specific client
    vector<pair<string,string>> receipt_vec;//first receipt id, second action
    vector<Book*> wish_list;
    int login;//this integer represent the connection current state: 0=logged out, 1=waiting for server respond, 2=logged in
    std::mutex mutex_for_books;
    std::mutex mutex_for_wishlist;









public:
    UserDetails(string userName, string password);
    virtual ~UserDetails();

    string getSubscriptionId();




    string getReceiptId() ;

    string getUserName() ;

    void addBook(string bookName,string genre,string owner);

    void subscribe(string genre, string subsription_id);

    Book* removeBook(string bookName);

    void unSubscribe(string genre);



     string getPassword();

     vector<pair<string,string>>& getReceiptVec();

     string getSubscriptionIdByGenre(string genre);

     Book* getBook(string book_name);

     string getBooksByGenre(string genre);

     bool checkIfInterested(string book_name);

     string getReceiptResponse(string receiptId);//send the action that need to be taken when this receipt gets back from the server

    int getLogin() ;

    void setLogin(int login);

    void clean();

    void setUserName( string &userName);

    void setPassword( string &password);


    void addReceipt(pair<string, string> res);

    void addToWishList(string bookName, string owner, string genre);

    vector<pair<string,string>> &getSubscriptionVec();
};


#endif //BOOST_ECHO_CLIENT_USERDETAILS_H
