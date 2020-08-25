//
// Created by hagairav@wincs.cs.bgu.ac.il on 08/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_SERVERTASK_H
#define BOOST_ECHO_CLIENT_SERVERTASK_H

#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include <mutex>
#include <condition_variable>
#include "UserDetails.h"
#include "connectionHandler.h"

using namespace std;

class ServerTask {
private:
    ConnectionHandler &connection_handler;
    UserDetails &user_details;
    std::condition_variable& conditionVariable;
    std::mutex& mutex;

    void splitByChar(vector<string> &splitVec, string msgInput,char splitHere);

    void printStatus(string status);

    void sendMyBookStatus(string topic);

    void wishToBorrow(string bookName,string genre);

    void takeBook(string bookName,string userToTakeFrom);//called if someone want book from me

    void hasBook(string bookName,string ownerName, string genre);//called if someone has a book i want

    void returningBook(string bookName, string userToReturnTo);//called if someone return a book to me

    void receiptResponse(string receiptId);





public:
    ServerTask(ConnectionHandler &connectionHandler, UserDetails &userDetails,condition_variable& conditionVariable, std::mutex& mutex);

    virtual ~ServerTask();

    string decode();

    void messageProtocol(string msg);

    void disconnect();

    void operator()();


    void unSubscribe(string subscriptionId);
};


#endif //BOOST_ECHO_CLIENT_SERVERTASK_H
