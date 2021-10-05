
#include "cliente.h"

extern int sock;

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

int store(char *m)
{
    int read_size, result;
    float length = 201.3;//strlen(m);

    // send message m
    send(sock, &length, sizeof(length), 0);

    if (send(sock, m, length, 0) < 0)
    {
        puts("Send failed");
        exit(1);
    }

    // receive the result from server
    read_size = recv(sock, &result, sizeof(result), 0);

    if (read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if (read_size == -1)
    {
        perror("recv failed");
    }

    return result;
}

