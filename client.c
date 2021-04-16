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
    int socketfd = 0;

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == 0)
    {
        perror("Failed to create a socket!\n");
        exit(EXIT_FAILURE);
    }

    char m_buffer[1000];

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(7000);

    int connerr = connect(socketfd, (struct sockaddr *)&address, sizeof(address));
    if (connerr < 0)
    {
        perror("Failed to make a connection!\n");
        exit(EXIT_FAILURE);
    }

    int readMessage = read(socketfd, &m_buffer, sizeof(m_buffer));
    if (readMessage < 0)
    {
        perror("Failed to receive message!\n");
        exit(EXIT_FAILURE);
    }

    close(connerr);
    close(socketfd);
    printf("\n%s\n", m_buffer);
    return EXIT_SUCCESS;
}
