//
// Created by hagairav@wincs.cs.bgu.ac.il on 08/01/2020.
//
#include <boost/algorithm/string.hpp>

#include "ServerTask.h"
#include <string>
#include <StompFrame.h>

using namespace std;
using namespace boost;


ServerTask::ServerTask(ConnectionHandler &connectionHandler, UserDetails &userDetails,condition_variable& conditionVariable, std::mutex& mutex):connection_handler(connectionHandler), user_details(userDetails),conditionVariable(conditionVariable),mutex(mutex) {}

ServerTask::~ServerTask() {}



void ServerTask::operator()() {



        while (user_details.getLogin()!=0) {

            string msg = decode();
            if (msg != "")
                messageProtocol(msg);
        }


}

string ServerTask::decode() {
    string msg="";

    connection_handler.getLine(msg);


    return msg;
}

void ServerTask::messageProtocol(string msg) {
    vector<string> inputVec;
    splitByChar(inputVec,msg,'\n');


    vector<string> headers={"CONNECTED","RECEIPT","MESSAGE","ERROR"};
    int index=-1;
    for(unsigned int i=0;(i<headers.size())&(index==-1);i++){
        if(inputVec[0].compare(headers[i])==0)//if we are looking at the same header
            index=i;
    }
    switch (index) {
        case 0: {//CONNECTED
            user_details.setLogin(2);//connected
            cout << "Login successful" << endl;
        }
            break;
        case 1: {//RECEIPT


            vector<string> line;
            splitByChar(line, inputVec[1], ':');
            receiptResponse(line[1]);//send the receipt id
        }
            break;
        case 2: {//MESSAGE





            vector<string> header3;
            splitByChar(header3, inputVec[3], ':');
            string destination = header3[1];

            vector<string> body;
            splitByChar(body, inputVec[5], ' ');

            if ((body.size() == 2) &&
                (body[0].compare("Book") == 0) &
                (body[1].compare("status") == 0)) {//send books status
                sendMyBookStatus(destination);
            }
            else if (body[0].compare("Taking")==0) {//taking book


                //--the book can contain more then one word
                string bookName="";
                for(unsigned int i=1;i<body.size();i++) {
                    if (body[i].compare("from") == 0) {
                        i=body.size();//end reading the book name
                    } else {
                        bookName +=  body[i] + " ";
                    }
                }

                bookName = bookName.substr(0,bookName.length()-1);

                //
                takeBook(bookName,body[body.size()-1]);
                cout<<destination+":"+inputVec[5] <<endl;

            }
            else if (body[0].compare("Returning")==0) {//returning book

                cout << inputVec[5] << endl;


                //--the book can contain more then one word
                string bookName="";
                for(unsigned int i=1;i<body.size();i++) {
                    if (body[i].compare("to") == 0) {
                        i=body.size();//end reading the book name
                    }else {
                        bookName +=   body[i] + " ";
                    }
                }

                bookName = bookName.substr(0,bookName.length()-1);


                //
                returningBook(bookName,body[body.size()-1]);
                cout<<destination+":"+inputVec[5] <<endl;


            }
            else if ((body.size() >= 6) && ((body[1].compare("has") == 0)
                                            & (body[2].compare("added") == 0)
                                            & (body[4].compare("book") == 0))) {//book added

                cout<<destination+":"+inputVec[5] <<endl;


            } else if ((body.size() >= 5) &&
                       ((body[1].compare("wish") == 0)
                        & (body[3].compare("borrow") == 0))) {//someone wish to borrow book

                //--book name can has more then one word
                string bookName="";
                for(unsigned int i=4;i<body.size();i++)
                    bookName+=body[i] + " ";
                bookName = bookName.substr(0,bookName.length()-1);

                //--
                wishToBorrow(bookName,destination);
                cout<<destination+":"+inputVec[5] <<endl;


            } else if (body.size()>=2 && body[1].compare("has") == 0) {//someone had a book


                //--book name can has more then one word
                string bookName="";
                for(unsigned int i=2;i<body.size();i++)
                    bookName+=body[i] + " ";
                bookName = bookName.substr(0,bookName.length()-1);
                //--
                hasBook(bookName,body[0],destination);
                cout<<destination+":"+inputVec[5] <<endl;

            } else {


               // vector<string> splitBody;
                //splitByChar(splitBody, body[0],':');//in case there is a ':' we can be sure that the message we got is about printing status
               // if (splitBody.size() >= 2) {//print status
                   // printStatus(inputVec[5]);
                //}
                cout<<destination+":"+inputVec[5] <<endl;

            }
        }
            break;

        case 3: {//ERROR
            cout<<msg<<endl;
            disconnect();
        }
            break;
    }
}


void ServerTask::splitByChar(vector<string> &splitVec, string line, char splitHere) {
    int i=0;
    while (i!=-1){
        i=line.find_first_of(splitHere);

        splitVec.push_back(line.substr(0,i));

        line=line.substr(i+1,line.length());
    }
}

void ServerTask::printStatus(string status) {
    cout<<status<<endl;
}

void ServerTask::sendMyBookStatus(string topic) {




    string bookList=user_details.getBooksByGenre(topic);


        vector<pair<string, string>> headers;
        pair<string, string> p1("destination", topic);//the only header here
        headers.push_back(p1);
        string body = user_details.getUserName() + ":" + bookList;

        string stompFrame = StompFrame("SEND", headers, body).getStompFrame(); //creating a "SEND" frame

        char bytesArray[stompFrame.size()];
        strcpy(bytesArray, stompFrame.c_str());



        connection_handler.sendBytes(bytesArray, stompFrame.size());
    }

void ServerTask::wishToBorrow(string bookName,string genre) {//check if I have this book, if i have it then i will send:

    // <user name> has <book>
    //I'm not changing the book status until i get a Taking Frame with my user name on it
    if ((user_details.getBook(bookName)!= nullptr)&&(user_details.getBook(bookName)->isAvailable())){


        //create a SEND frame:
        vector<pair<string,string>> headers;
        pair<string,string> p1("destination",genre);//the only header here
        headers.push_back(p1);
        string body=user_details.getUserName()+" has "+bookName;

        string stompFrame = StompFrame("SEND",headers,body).getStompFrame(); //creat ing a "SEND" frame

        char bytesArray[stompFrame.size()];
        strcpy(bytesArray,stompFrame.c_str());

        connection_handler.sendBytes(bytesArray,stompFrame.size());
    }
}

void ServerTask::takeBook(string bookName, string userToTakeFrom) {//this method checks if i am the user who the server
    // want to take the book from, if i am then the book will be no longer available in my inventory
    if(user_details.getUserName().compare(userToTakeFrom)==0){

        Book *bookToLend=user_details.getBook(bookName);
        if(bookToLend!= nullptr) {
            bookToLend->setAvailable(false);
        }
    }
}

void ServerTask::hasBook(string bookName, string ownerName,string genre) {
    if(user_details.checkIfInterested(bookName)){//in case it was me who asked for this book


        user_details.addBook(bookName,ownerName,genre);//add the book to my inventory

        //create SEND frame
        vector<pair<string,string>> headers;
        pair<string,string> p1("destination",genre);//the only header here
        headers.push_back(p1);
        string body="Taking "+bookName+" from "+ownerName;

        string stompFrame = StompFrame("SEND",headers,body).getStompFrame(); //creating a "SEND" frame

        char bytesArray[stompFrame.size()];
        strcpy(bytesArray,stompFrame.c_str());

        connection_handler.sendBytes(bytesArray,stompFrame.size());

    }
}

void ServerTask::returningBook(string bookName, string userToReturnTo) {
    if(user_details.getUserName().compare(userToReturnTo)==0){

        Book *returnedBook=user_details.getBook(bookName);
        if(returnedBook!= nullptr){
            returnedBook->setAvailable(true);
        }
    }
}

void ServerTask::receiptResponse(string receiptId) {



    string response= user_details.getReceiptResponse(receiptId);

    vector<string> responseSplit;
    splitByChar(responseSplit,response,' ');


    vector<string> vec={"DISCONNECT","SUBSCRIBE","UNSUBSCRIBE"};
    unsigned int index=0;
    for( index=0;index<vec.size();index++){
        if(vec[index].compare(responseSplit[0])==0)
            break;
    }

    switch (index){
        case 0:{//DISCONNECT


            disconnect();

            std::unique_lock<std::mutex> lock(mutex);
            conditionVariable.notify_all();
            cout<<"Logout successful" <<endl;




        }
            break;
        case 1:{//SUBSCRIBE


            user_details.subscribe(responseSplit[1],responseSplit[2]);
            cout<<"Joined club "+responseSplit[1]<<endl;
        }
            break;
        case 2:{//UNSUBSCRIBE


            user_details.unSubscribe(responseSplit[1]);
            cout<<"Exited club "+responseSplit[1]<<endl;
        }
            break;
    }
}

void ServerTask::disconnect() {

    vector<pair<string,string>> subscriptionVec=user_details.getSubscriptionVec();
    for(pair<string,string> pair:subscriptionVec) {  //sending unsubscribe frames for all topics
        unSubscribe(pair.second);
    }

    user_details.clean();//changing the login to 0 and erase all data


    connection_handler.close();//close socket


}

void ServerTask::unSubscribe(string subscription_id){
    vector<pair<string, string>> headers;
    pair<string, string> p1("id",
                            subscription_id);//remove the genre from user details, and gives back its subscription id
    string receipt_id = user_details.getReceiptId();
    pair<string, string> p2("receipt", receipt_id);


    headers.push_back(p1);
    headers.push_back(p2);


    string stompFrame = StompFrame("UNSUBSCRIBE", headers, "").getStompFrame(); //creating a "SEND" frame
    char bytesArray[stompFrame.size()];
    strcpy(bytesArray, stompFrame.c_str());

    connection_handler.sendBytes(bytesArray, stompFrame.size());
}





