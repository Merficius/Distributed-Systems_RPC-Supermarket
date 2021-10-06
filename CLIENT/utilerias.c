
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

int find_service(int id)
{
    int read_size, port, proc = 2; // busqueda de servidor
    int sock = connection(PORTMAPPER);

    send(sock, &proc, sizeof(proc), 0);
    if (send(sock, &id, sizeof(id), 0) < 0)
    {
        puts("Send failed");
        exit(1);
    }

    //recibir el puerto del servidor
    read_size = recv(sock, &port, sizeof(port), 0);

    if (read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if (read_size == -1)
    {
        perror("recv failed");
    }

    close(sock);
    return port;
}
