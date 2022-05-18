#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

const int MAX_CMD_SIZE = 1024;

int main()
{
    int sockD = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(3490);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    int conn_stat = connect(sockD, (struct sockaddr *)&server_addr, sizeof(server_addr));

    if (conn_stat == -1)
    {
        printf("Error...\n");
        return 0;
    }
    while (1)
    {
        char new_msg[MAX_CMD_SIZE];
        fgets(new_msg, MAX_CMD_SIZE, stdin);
        new_msg[strlen(new_msg) - 1] = '\0';
        send(sockD, new_msg, strlen(new_msg), 0);
        if (!strncmp(new_msg, "PUSH", 4))
        {
            return 0;
        }
        else if (!strncmp(new_msg, "POP", 3) || !strncmp(new_msg, "TOP", 3))
        {
            char data[1024];
            int num_of_bytes;
            num_of_bytes = recv(sockD, data, 1024, 0);
            data[num_of_bytes] = '\0';
            printf("%s\n", data);
        }
        else
        {
            printf("Invalid command\n");
        }
        return 0;
    }
}
