#include "servidor.h"

int portmapper(char *host)
{
    int sock;
    struct sockaddr_in server;

    // socket para conectar con el servidor de nombres
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");

    server.sin_addr.s_addr = inet_addr(host);
    server.sin_family = AF_INET;
    server.sin_port = htons(PORTMAPPER);

    // conexión con el servidor de nombres
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        exit(1);
    }

    puts("Connected\n");
    return sock;
}

int initialization(int port)
{
    int socket_desc;
    struct sockaddr_in server;

    // create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");

    // prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    // bind
    if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        // print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");

    return socket_desc;
}

int connection(int socket_desc)
{
    struct sockaddr_in client;
    int client_sock, c, read_size;

    // listen
    listen(socket_desc, 3);

    // accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);

    // accept connection from an incoming client
    client_sock = accept(socket_desc,
                         (struct sockaddr *)&client,
                         (socklen_t *)&c);

    if (client_sock < 0)
    {
        perror("accept failed");
        exit(1);
    }
    puts("Connection accepted");

    return client_sock;
}
