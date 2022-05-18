CC=g++
AR=ar
FLAGS= -Wall -g

all: client server

client:  Client.o
	$(CC) $(FLAGS) -o Client Client.o

server:  Server.o
	$(CC) $(FLAGS)  -o Server Server.o

Server.o: Server.cpp
	$(CC) $(FLAGS)  -c Server.cpp

Client.o: Client.cpp
	$(CC) $(FLAGS) -c Client.cpp


.PHONY: clean all
clean:
	rm -f *.o Client Server