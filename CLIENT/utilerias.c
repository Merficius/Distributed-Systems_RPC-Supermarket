
#include "cliente.h"

extern char *host;

int connection(int port)
{
    int sock;
    struct sockaddr_in server;

    // create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");

    server.sin_addr.s_addr = inet_addr(host);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    // connect to remote server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        exit(1);
    }

    puts("Connected\n");
    return sock;
}
