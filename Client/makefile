CFLAGS:=-c -Wall -Weffc++ -g -std=c++11  -Iinclude -pthread
LDFLAGS:=-lboost_system -pthread


all: StompBookClubClient
	g++ -o bin/StompBookClubClient bin/Book.o bin/clientMain.o bin/connectionHandler.o bin/KeyBoardTask.o bin/ServerTask.o bin/StompFrame.o bin/UserDetails.o $(LDFLAGS)

StompBookClubClient: bin/Book.o bin/clientMain.o bin/connectionHandler.o bin/KeyBoardTask.o bin/ServerTask.o bin/StompFrame.o bin/UserDetails.o

bin/Book.o: src/Book.cpp
	g++ $(CFLAGS) -o bin/Book.o src/Book.cpp

bin/clientMain.o: src/clientMain.cpp
	g++ $(CFLAGS) -o bin/clientMain.o src/clientMain.cpp

bin/connectionHandler.o: src/connectionHandler.cpp
	g++ $(CFLAGS) -o bin/connectionHandler.o src/connectionHandler.cpp

bin/KeyBoardTask.o: src/KeyBoardTask.cpp
	g++ $(CFLAGS) -o bin/KeyBoardTask.o src/KeyBoardTask.cpp

bin/ServerTask.o: src/ServerTask.cpp
	g++ $(CFLAGS) -o bin/ServerTask.o src/ServerTask.cpp

bin/StompFrame.o: src/StompFrame.cpp
	g++ $(CFLAGS) -o bin/StompFrame.o src/StompFrame.cpp
	
bin/UserDetails.o: src/UserDetails.cpp
	g++ $(CFLAGS) -o bin/UserDetails.o src/UserDetails.cpp

.PHONY: clean
clean:
	rm -f bin/*
