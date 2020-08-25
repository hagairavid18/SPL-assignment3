#include <stdlib.h>
#include <connectionHandler.h>
#include <UserDetails.h>
#include <KeyBoardTask.h>
#include <ServerTask.h>
#include <thread>

/**
* This code assumes that the server replies the exact text the client sent it (as opposed to the practical session example)
*/
using namespace std;

//int main(int argc, char *argv[]) {
//    if (argc < 3) {
//        std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
//        return -1;
//    }
//    std::string host = argv[1];
//    short port = atoi(argv[2]);
//
//    ConnectionHandler connectionHandler(host, port);
//    if (!connectionHandler.connect()) {
//        std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
//        return 1;
//    }
//
//	//From here we will see the rest of the ehco client implementation:
//    while (1) {
//        const short bufsize = 1024;
//        char buf[bufsize];
//        std::cin.getline(buf, bufsize);
//		std::string line(buf);
//		int len=line.length();
//        if (!connectionHandler.sendLine(line)) {
//            std::cout << "Disconnected. Exiting...\n" << std::endl;
//            break;
//        }
//		// connectionHandler.sendLine(line) appends '\n' to the message. Therefor we send len+1 bytes.
//        std::cout << "Sent " << len+1 << " bytes to server" << std::endl;
//
//
//        // We can use one of three options to read data from the server:
//        // 1. Read a fixed number of characters
//        // 2. Read a line (up to the newline character using the getline() buffered reader
//        // 3. Read up to the null character
//        std::string answer;
//        // Get back an answer: by using the expected number of bytes (len bytes + newline delimiter)
//        // We could also use: connectionHandler.getline(answer) and then get the answer without the newline char at the end
//        if (!connectionHandler.getLine(answer)) {
//            std::cout << "Disconnected. Exiting...\n" << std::endl;
//            break;
//        }
//
//		len=answer.length();
//		// A C string must end with a 0 char delimiter.  When we filled the answer buffer from the socket
//		// we filled up to the \n char - we must make sure now that a 0 char is also present. So we truncate last character.
//        answer.resize(len-1);
//        std::cout << "Reply: " << answer << " " << len << " bytes " << std::endl << std::endl;
//        if (answer == "bye") {
//            std::cout << "Exiting...\n" << std::endl;
//            break;
//        }
//    }

//    int i = 1;
//    string first_word;
//    string line;
//    std::vector<std::string> inputVec;
//
//
//    do {
//
//        const short bufsize = 1024;
//        char buf[bufsize];
//        cin.getline(buf, bufsize);
//        string line(buf);
//        int i;
//        while (i != -1) {
//            i = line.find_first_of(' ');
//            inputVec.push_back(line.substr(0, i));
//            line = line.substr(i + 1, line.length());
//        }
//
//    } while (inputVec[0].compare("login") != 0);
//    string second_word = inputVec[1];
//
//    i = second_word.find_first_of(':');
//    string host(second_word.substr(0, i));
//    std::string port = std::string(inputVec[1].substr(i + 1, inputVec[1].length()));
//    short ports_in_short = std::stoi(port);
//
//
//    UserDetails userDetails(inputVec[2], inputVec[3]);
//    ConnectionHandler connectionHandler(host, ports_in_short);
//    connectionHandler.connect();
//
//
//
//    //------------define threads
//
//
//    KeyBoardTask readFromKeyboard(connectionHandler, userDetails, inputVec);
//    ServerTask readFromServer(connectionHandler, userDetails);
//    //will start the threads
//    std::thread t1(std::ref(readFromKeyboard));
//    std::thread t2(std::ref(readFromServer));
//    t2.join();
//    t1.join();
//
//
//    return 0;
//}//login 127.0.0.1:7474 bob alice
//
