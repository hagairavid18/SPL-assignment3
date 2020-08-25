//
// Created by hagairav@wincs.cs.bgu.ac.il on 10/01/2020.
//

#include <connectionHandler.h>
#include <UserDetails.h>
#include <KeyBoardTask.h>
#include <ServerTask.h>
#include <thread>
#include <mutex>
#include <condition_variable>

/**
* This code assumes that the server replies the exact text the client sent it (as opposed to the practical session example)
*/
using namespace std;

int main() {


    int i = 1;
    string first_word;
    string line;
    std::vector<std::string> inputVec;


    do {

        const short bufsize = 1024;
        char buf[bufsize];
        cin.getline(buf, bufsize);
        string line(buf);
        int i=0;
        while (i != -1) {
            i = line.find_first_of(' ');
            inputVec.push_back(line.substr(0, i));
            line = line.substr(i + 1, line.length());
        }

    } while (inputVec[0].compare("login") != 0);
    string second_word = inputVec[1];

    i = second_word.find_first_of(':');
    string host(second_word.substr(0, i));
    std::string port = std::string(inputVec[1].substr(i + 1, inputVec[1].length()));
    short ports_in_short = std::stoi(port);


    UserDetails userDetails(inputVec[2], inputVec[3]);
    ConnectionHandler connectionHandler(host, ports_in_short, false);
    connectionHandler.connect();



    //------------define threads

    std::mutex mutex;
    std::condition_variable conditionVariable;


    KeyBoardTask readFromKeyboard(connectionHandler, userDetails, inputVec,conditionVariable,mutex);
    ServerTask readFromServer(connectionHandler, userDetails,conditionVariable,mutex);
    //will start the threads
    std::thread t1(std::ref(readFromKeyboard));
    std::thread t2(std::ref(readFromServer));
    t2.join();
    t1.join();


    return 0;
}//login 127.0.0.1:7777 amit alice

//login 132.72.44.49:7777 hagai alice

//