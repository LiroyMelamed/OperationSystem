
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "Stack.hpp"
#include <sys/mman.h>
#include <fcntl.h>
#include <fstream>

void *new_func(void *sock)
{
    int sock_id = *((int *)sock);
    free(sock);
    fd = open("text.txt", O_WRONLY | O_CREAT);
    if (fd == -1)
    {
        printf("Wrong file opening");
    }
    else
    {
        char client_text[1024];
        int num_of_bytes;
        num_of_bytes = recv(sock_id, client_text, 1024, 0);
        client_text[num_of_bytes] = '\0';
        if (!strncmp(client_text, "PUSH", 4))
        {
            char *sub_string = client_text + 5;
            push(sub_string);
        }
        else if (!strcmp(client_text, "POP"))
        {
            char *curr = pop();
            printf("%s\n", curr);
            if (curr != NULL)
            {
                send(sock_id, curr, strlen(curr), 0);
            }
            else
            {
                send(sock_id, "Stack is empty", 14, 0);
            }
        }
        else if (!strcmp(client_text, "TOP"))
        {
            char *curr = top();
            send(sock_id, curr, strlen(curr), 0);
        }
        else
        {
            printf("Invalid command was entered\n");
        }
        close(fd);
    }
    close(sock_id);
}

int main(int argc, char const *argv[])
{
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    // server address
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(3490);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // bind socket
    bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    // listen for connections
    listen(server_sock, 10);
    map = (struct nodeMap *)mmap(NULL, sizeof(struct nodeMap *), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    map->first_in = (struct node *)mmap(NULL, sizeof(struct node) * 10000, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, PUS0);
    while (1)
    {
        int client_sock = accept(server_sock, NULL, NULL);
        int *new_sock = (int *)malloc(sizeof(int));
        *new_sock = client_sock;
        pid_t pid = fork();
        if (pid == -1)
        {
            printf("Error in forking\n");
        }
        else if (pid == 0)
        {
            new_func(new_sock);
        }
        else
        {
            usleep(100);
        }
    }
    return 0;
}