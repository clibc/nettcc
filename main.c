#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int socketfd, connfd;
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == 0)
    {
        perror("Failed to create a socket!\n");
        exit(EXIT_FAILURE);
    }

    //
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(7000);

    bind(socketfd, (struct sockaddr *)&address, sizeof(address));

    if (listen(socketfd, 10) == -1)
    {
        printf("Failed to listen\n");
        exit(EXIT_FAILURE);
    }

    char message[100];
    memset(message, '0', sizeof(message));

    while (1)
    {
        connfd = accept(socketfd, (struct sockaddr *)NULL, NULL);

        strcpy(message, "Hello There!\n");
        write(connfd, message, strlen(message));
        close(connfd);
        sleep(1);
    }

    close(socketfd);
    return EXIT_SUCCESS;
}
