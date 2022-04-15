CC=gcc
AR=ar
FLAGS= -Wall -g

all: new_Client new_Server

new_Client:  new_Client.o
	$(CC) $(FLAGS) -o new_Client new_Client.o

new_Server:  new_Server.o
	$(CC) $(FLAGS) -o new_Server new_Server.o

new_Server.o: new_Server.c
	$(CC) $(FLAGS) -c new_Server.c

new_Client.o: new_Client.c
	$(CC) $(FLAGS) -c new_Client.c

.PHONY: clean all
clean:
	rm -f *.o new_Client new_Server