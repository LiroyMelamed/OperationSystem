# Authors
Arik Tatievski

Roi Meshulam

# What is this project?

This project is a synchronized multi-process server using a Stack to save data.

# The way we made our project:
The server runs an infinite loop and can listen to 10 users at the same time.

When the server gets a connection he runs a thread to handle the sapsific clients request.

Client can either *PUSH -text-*, *POP*, *TOP*, any other command will be denided.

Push - push a string to the stack.

Pop - removes the head of the stack and returns it.

Top - reads the head of the stack and returns it.

The server supports synchronized through fcntl.

The server allocates space in the stack using a shared mmap.

# How to use our project:

Write in a bash environment "make all".

Please run ./Server to activate our server

Please run ./Client to activate a client (Not an infinite connection does dummy commands and disconnects).

You can also run your own client as long as it matches the IP/PORT written in "Server.c"

# Hope you find good usuage of this project!
