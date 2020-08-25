//
// Created by hagairav@wincs.cs.bgu.ac.il on 07/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_STOMPFRAME_H
#define BOOST_ECHO_CLIENT_STOMPFRAME_H

#include <string>
#include <vector>

using namespace std;

class StompFrame {
private:
    string _head;
    vector<pair<string,string>> _headers;
    string _body;


public:
    ~StompFrame();
    StompFrame();
    StompFrame(string head,vector<pair<string,string>> headers,string body);
    string getStompFrame();

};


#endif //BOOST_ECHO_CLIENT_STOMPFRAME_H
