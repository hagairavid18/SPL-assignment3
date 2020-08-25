//
// Created by hagairav@wincs.cs.bgu.ac.il on 06/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_KEYBOARDTASK_H
#define BOOST_ECHO_CLIENT_KEYBOARDTASK_H

#include "connectionHandler.h"
#include "UserDetails.h"
#include <string>
#include <condition_variable>

using namespace std;
class KeyBoardTask {
private:
    ConnectionHandler &connection_handler;
    UserDetails &user_details;
    vector<string> input_vec;
    std::condition_variable& conditionVariable;
    std::mutex& mutex;

    void splitBySpace(vector<string> &splitVec, string msgInput);


public:
    KeyBoardTask(ConnectionHandler &connectionHandler,UserDetails &userDetails,vector<string> input_vec,condition_variable& conditionVariable, std::mutex& mutex);
    void operator()();
    bool encode(std::string line);
    bool Login(vector< string> inputVec);
    bool Join(vector< string> inputVec);
    bool Exit(vector< string> inputVec);
    bool Add(vector< string> inputVec);
    bool Borrow(vector< string> inputVec);
    bool Return(vector< string> inputVec);
    bool Status(vector< string> inputVec);
    bool Logout(vector< string> inputVec);








};


#endif //BOOST_ECHO_CLIENT_KEYBOARDTASK_H
