//
// Created by hagairav@wincs.cs.bgu.ac.il on 07/01/2020.
//

#include "StompFrame.h"
StompFrame::StompFrame(string head, vector<pair<string, string>> headers, string body):_head(head),_headers(headers),_body(body) {}

StompFrame::StompFrame():_head(),_headers(),_body() {}

StompFrame::~StompFrame() {}

string StompFrame::getStompFrame() {
    string output=_head+'\n';
    for(unsigned int i=0;i<_headers.size();i++){
        output+=_headers[i].first+":"+_headers[i].second+'\n';
    }
    output+='\n';
    if(_body.compare("") != -0) {
        output += _body + '\n';
    }
    output+='\0';
    return output;
}

