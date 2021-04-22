#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s <port>\n", argv[0]);
        exit(0);
    }

    int port = atoi(argv[1]);

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
    address.sin_port = htons(port);

    int bindres = bind(socketfd, (struct sockaddr *)&address, sizeof(address));

    if (bindres == -1)
    {
        printf("\nError occured when binding a socket \n");
        exit(-1);
    }
    else
    {
        printf("Binding port is successful.\n");
    }

    if (listen(socketfd, 10) == -1)
    {
        printf("Failed to listen\n");
        exit(EXIT_FAILURE);
    }

    char message[100];
    memset(message, 0, sizeof(message));

    connfd = accept(socketfd, NULL, NULL);

    char *m_buffer = NULL;
    while (1)
    {
        recv(connfd, message, sizeof(message), 0);
        printf("%s", message);

        size_t linesize;
        getline(&m_buffer, &linesize, stdin);
        send(connfd, m_buffer, linesize - 1, 0);
        sleep(1);
    }

    close(connfd);
    close(socketfd);
    return EXIT_SUCCESS;
}
