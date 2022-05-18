#include <netinet/in.h> //structure for storing address information
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h> //for socket APIs
#include <sys/types.h>
#include <pthread.h>
#include "Stack.h"

void *func(void *sock)
{
    int sock_id = *((int *)sock);
    free(sock);
    char data[1024];
    int num_of_bytes;
    num_of_bytes = recv(sock_id, data, 1024, 0);
    data[num_of_bytes] = '\0';
    if (!strncmp(data, "PUSH", 4))
    {
        char *substring = data + 5;
        push(substring);
    }
    else if (!strcmp(data, "POP"))
    {
        char *curr = pop();
        printf("%s\n", curr);
        send(sock_id, curr, strlen(curr), 0);
    }
    else if (!strcmp(data, "PEEK"))
    {
        char *curr = peek();
        send(sock_id, curr, strlen(curr), 0);
    }
    else
    {
        printf("Invalid command was entered\n");
    }
    close(sock_id);
}

int main(int argc, char const *argv[])
{
    init();
    int serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    // define server address
    struct sockaddr_in serv_addr;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(3490);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    // bind socket to the specified IP and port
    bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    // listen for connections
    listen(serv_sock, 10);
    while (1)
    {
        // integer to hold client socket.
        int client_sock = accept(serv_sock, NULL, NULL);
        pthread_t new_thread;
        int *new_sock = malloc(sizeof(int));
        *new_sock = client_sock;
        pthread_create(&new_thread, NULL, func, new_sock);
    }
    return 0;
}