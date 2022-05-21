# Authors

Barak Amram & Liroy Melamed

# Brief

Our project operate synchronized multi-process server using a stack.

# The way we made our project:

Our server can listen up to 10 clients using a thread.

The Client can operate the next commands:

Push - to the stack.

Pop - pop the head of the stack.

Top - reads the head of the stack and returns it.

The server allocates space in the stack using a shared mmap.

# How to use our project:

Write "make all".

run ./Server to activate our server.

run ./Client to activate a single command client.
