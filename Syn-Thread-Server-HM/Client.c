#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <netinet/in.h> //structure for storing address information
#include <sys/socket.h> //for socket APIs
#include <sys/types.h>

const int MAX_CMD_SIZE = 1024;

int main()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(3490); // use some unused port number
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    int connectStatus = connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    if (connectStatus == -1)
    {
        printf("Error...\n");
        return 0;
    }
    // Accepting data from the server
    char new_msg[MAX_CMD_SIZE];
    fgets(new_msg, MAX_CMD_SIZE, stdin);
    new_msg[strlen(new_msg) - 1] = '\0';
    send(sock, new_msg, strlen(new_msg), 0);
    if (!strncmp(new_msg, "PUSH", 4))
    {
        return 0;
    }
    else if (!strncmp(new_msg, "POP", 3) || !strncmp(new_msg, "PEEK", 4))
    {
        char data[1024];
        int num_of_bytes = recv(sock, data, 1024, 0);
        data[num_of_bytes] = '\0';
        printf("%s\n", data);
    }
    else
    {
        printf("Invalid command was entered\n");
    }
    return 0;
}
