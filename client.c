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

    int socketfd = 0;

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == 0)
    {
        perror("Failed to create a socket!\n");
        exit(EXIT_FAILURE);
    }

    char m_buffer[100];

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(port);

    char r_buffer[100];

    strcpy(m_buffer, "Lol");
    while (1)
    {
        int conn = connect(socketfd, (struct sockaddr *)&address, sizeof(address));

        send(socketfd, m_buffer, strlen(m_buffer), 0);

        recv(socketfd, r_buffer, 100, 0);
        printf("%s\n", r_buffer);
        close(conn);
        sleep(1);
    }

    return EXIT_SUCCESS;
}
