//
// Created by hagairav@wincs.cs.bgu.ac.il on 06/01/2020.
//

#include <boost/algorithm/string.hpp>
#include <StompFrame.h>

#include "KeyBoardTask.h"

using namespace std;
using namespace boost;

KeyBoardTask::KeyBoardTask(ConnectionHandler &connectionHandler, UserDetails &userDetails, vector<string> input_vec,
                           condition_variable &conditionVariable, std::mutex &mutex) : connection_handler(
        connectionHandler), user_details(userDetails), input_vec(input_vec), conditionVariable(conditionVariable),
                                                                                       mutex(mutex) {}

void KeyBoardTask::operator()() {


    Login(input_vec);



    //getting line from keyboard



        while (user_details.getLogin() != 0) {

            const short bufsize = 1024;
            char buf[bufsize];
            std::cin.getline(buf, bufsize);
            std::string line(buf);

            if (line.compare("bye")==0){//in case we got error we use "bye" word to exit the main loop
                break;
            }

            if (user_details.getLogin() != 0 && !encode(line)) {
                std::cout << "Invalid action" << std::endl;
            }


            if (line.compare("logout") == 0) {
                std::unique_lock<std::mutex> lock(mutex);
                conditionVariable.wait(lock);//when logging out we will wait till a receipt will be returned- when it will we will get a
            }
        }


    }








bool KeyBoardTask::encode(std::string line) {


    vector<string> inputVec;

    splitBySpace(inputVec, line);


    vector<string> headers = {"login", "join", "exit", "add", "borrow", "return", "status", "logout"};
    int index = -1;
    for (unsigned int i = 0; (i < headers.size()) & (index == -1); i++) {
        if (inputVec[0].compare(headers[i]) == 0)//if we are looking at the same header
            index = i;
    }
    switch (index) {
        case 0: {//login/

            return Login(inputVec);
        }
        case 1: {//join

            return Join(inputVec);
        }
        case 2: {//exit
            return Exit(inputVec);
        }
        case 3: {//add
            return Add(inputVec);
        }
        case 4: {//borrow
            return Borrow(inputVec);
        }
        case 5: {//return
            return Return(inputVec);
        }
        case 6: {//status
            return Status(inputVec);
        }
        case 7: {//logout
            return Logout(inputVec);
        }
        case (-1): {//invalid input
            return false;

        }
    }
    return false;//is needed because of warnings


}

bool KeyBoardTask::Logout(vector<string> inputVec) {
    vector<pair<string, string>> headers;
    string receipt_id = user_details.getReceiptId();


    pair<string, string> p1("receipt", receipt_id);
    headers.push_back(p1);


    pair<string, string> s1(receipt_id, "DISCONNECT");


    user_details.getReceiptVec().push_back(s1); //insert receipt


    string stompFrame = StompFrame("DISCONNECT", headers, "").getStompFrame();
    char bytesArray[stompFrame.size()];
    strcpy(bytesArray, stompFrame.c_str());

    return connection_handler.sendBytes(bytesArray, stompFrame.size());
}

bool KeyBoardTask::Status(vector<string> inputVec) {
    vector<pair<string, string>> headers;
    pair<string, string> p1("destination", inputVec[1]);
    headers.push_back(p1);
    string stompFrame = StompFrame("SEND", headers, "Book status").getStompFrame();
    char bytesArray[stompFrame.size()];
    strcpy(bytesArray, stompFrame.c_str());

    return connection_handler.sendBytes(bytesArray, stompFrame.size());
}

bool KeyBoardTask::Return(vector<string> inputVec) {
    vector<pair<string, string>> headers;
    pair<string, string> p1("destination", inputVec[1]);//the only header here
    headers.push_back(p1);
    //--the book can contain more then one word
    string bookName = "";
    for (unsigned int i = 2; i < inputVec.size(); i++) {
        bookName += inputVec[i] + " ";
    }
    bookName = bookName.substr(0, bookName.length() - 1);


    //
    Book *bookToReturn = user_details.removeBook(bookName);
    string ownerName = bookToReturn->getOwner();
    delete bookToReturn;

    string body = "Returning " + bookName + " to " + ownerName;


    string stompFrame = StompFrame("SEND", headers, body).getStompFrame(); //creating a "SEND" frame


    char bytesArray[stompFrame.size()];
    strcpy(bytesArray, stompFrame.c_str());

    return connection_handler.sendBytes(bytesArray, stompFrame.size());

}

bool KeyBoardTask::Borrow(vector<string> inputVec) {
    vector<pair<string, string>> headers;
    pair<string, string> p1("destination", inputVec[1]);//the only header here
    headers.push_back(p1);
    //--the book can contain more then one word
    string bookName = "";
    for (unsigned int i = 2; i < inputVec.size(); i++) {
        bookName += inputVec[i] + " ";
    }

    bookName = bookName.substr(0, bookName.length() - 1);

    user_details.addToWishList(bookName, "", inputVec[1]);


    //
    string body = user_details.getUserName() + " wish to borrow " + bookName;


    string stompFrame = StompFrame("SEND", headers, body).getStompFrame(); //creating a "SEND" frame


    char bytesArray[stompFrame.size()];
    strcpy(bytesArray, stompFrame.c_str());

    return connection_handler.sendBytes(bytesArray, stompFrame.size());
}

bool KeyBoardTask::Add(vector<string> inputVec) {
    vector<pair<string, string>> headers;
    pair<string, string> p1("destination", inputVec[1]);//the only header here
    headers.push_back(p1);
    //--the book can contain more then one word
    string bookName = "";
    for (unsigned int i = 2; i < inputVec.size(); i++) {
        bookName += inputVec[i] + " ";
    }
    bookName = bookName.substr(0, bookName.length() - 1);


    //
    user_details.addBook(bookName, user_details.getUserName(), inputVec[1]);

    string body = user_details.getUserName() + " has added the book " + bookName;
    string stompFrame = StompFrame("SEND", headers, body).getStompFrame(); //creating a "SEND" frame


    char bytesArray[stompFrame.size()];
    strcpy(bytesArray, stompFrame.c_str());

    return connection_handler.sendBytes(bytesArray, stompFrame.size());
}

bool KeyBoardTask::Exit(vector<string> inputVec) {//exit genre club
    string subscription_id(user_details.getSubscriptionIdByGenre(inputVec[1]));
    vector<pair<string, string>> headers;
    pair<string, string> p1("id",
                            subscription_id);//remove the genre from user details, and gives back its subscription id
    string receipt_id = user_details.getReceiptId();
    pair<string, string> p2("receipt", receipt_id);


    pair<string, string> s1(receipt_id, "UNSUBSCRIBE " + inputVec[1] + " " + subscription_id);


    user_details.getReceiptVec().push_back(s1); //insert receipt



    headers.push_back(p1);
    headers.push_back(p2);


    string stompFrame = StompFrame("UNSUBSCRIBE", headers, "").getStompFrame(); //creating a "SEND" frame
    char bytesArray[stompFrame.size()];
    strcpy(bytesArray, stompFrame.c_str());

    return connection_handler.sendBytes(bytesArray, stompFrame.size());
}

bool KeyBoardTask::Join(vector<string> inputVec) {


    string subscriptionId = user_details.getSubscriptionId(); //get unique subscription id


    vector<pair<string, string>> headers;
    pair<string, string> p1("destination", inputVec[1]);
    pair<string, string> p2("id", subscriptionId);


    string receipt_id = user_details.getReceiptId();
    pair<string, string> p3("receipt", receipt_id);

    pair<string, string> s1(receipt_id, "SUBSCRIBE " + inputVec[1] + " " + subscriptionId);


    user_details.addReceipt(s1);


    headers.push_back(p1);
    headers.push_back(p2);
    headers.push_back(p3);


    string stompFrame = StompFrame("SUBSCRIBE", headers, "").getStompFrame(); //creating SUBSCRIBE frame
    char bytesArray[stompFrame.size()];
    strcpy(bytesArray, stompFrame.c_str());


    return connection_handler.sendBytes(bytesArray, stompFrame.size());
}

bool KeyBoardTask::Login(vector<string> inputVec) {
    if(user_details.getUserName().compare(inputVec[2])==0) {//in case we are already logged in them my user name will not be "" and in this case we will not create a new user

        vector<pair<string, string>> headers;
        pair<string, string> p1("accept-version", "1.2");
        pair<string, string> p2("host", "stomp.cs.bgu.ac.il");

        user_details.setUserName(inputVec[2]);
        user_details.setPassword(inputVec[3]);

        pair<string, string> p3("login", user_details.getUserName());
        pair<string, string> p4("passcode", user_details.getPassword());


        headers.push_back(p1);
        headers.push_back(p2);
        headers.push_back(p3);
        headers.push_back(p4);

        string stompFrame = StompFrame("CONNECT", headers, "").getStompFrame();
        char bytesArray[stompFrame.size()];
        strcpy(bytesArray, stompFrame.c_str());

        return connection_handler.sendBytes(bytesArray, stompFrame.size());;
    }
    return false;
}

void KeyBoardTask::splitBySpace(vector<string> &splitVec, string line) {

    int i = 0;
    while (i != -1) {
        i = line.find_first_of(' ');
        splitVec.push_back(line.substr(0, i));
        line = line.substr(i + 1, line.length());
    }
}














