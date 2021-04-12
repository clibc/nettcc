#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
//sleep
#include <unistd.h>

int main()
{
    int socketdes;
    socketdes = socket(AF_INET, SOCK_STREAM, 0);
    if (socketdes == 0)
    {
        perror("Failed to create a socket!");
        exit(EXIT_FAILURE);
    }

    //
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(7000);

    bind(socketdes, (struct sockaddr *)&address, sizeof(address));

    sleep(10);
    close(socketdes);
    return EXIT_SUCCESS;
}
