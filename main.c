#include <arpa/inet.h>
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
    memset(&address, '0', sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(7000);

    int bindres = bind(socketfd, (struct sockaddr *)&address, sizeof(address));

    printf("bindres : %d \n", bindres);
    if (bindres == -1)
    {
        printf("\nError occured when binding a socket \n");
        exit(-1);
    }

    if (listen(socketfd, 10) == -1)
    {
        printf("Failed to listen\n");
        exit(EXIT_FAILURE);
    }

    char message[100];
    memset(message, '0', sizeof(message));

    connfd = accept(socketfd, (struct sockaddr *)NULL, NULL);
    strcpy(message, "Hi I am sending this message");
    write(connfd, message, sizeof(char) * strlen(message));

    close(connfd);
    close(socketfd);
    return EXIT_SUCCESS;
}
