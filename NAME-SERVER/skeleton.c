#include "server.h"

int recv_integer(int client_sock);
void send_integer(int client_sock, int value);

int main(int argc, char *argv[])
{
    int socket_desc = initialization();

    // loop infinito
    while (1)
    {
        int id, port;
        int client_sock = connection(socket_desc);
        int proc = recv_integer(client_sock);

        switch (proc)
        {
        case 1: // registrar un servidor que tiene servicios
            id = recv_integer(client_sock);
            port = recv_integer(client_sock);
            printf("suscription: %d, %d\n", id, port);

            // puerto donde se debe de conectar el cliente para encontrar el servicio
            register_service(id, port);
            break;

        case 2: // encontrar un servidor que tiene servicios
            id = recv_integer(client_sock);
            port = find_service(id);
            printf("lookup: %d, %d\n", id, port);

            // puerto donde se debe de conectar el cliente para ejecutar el servicio
            send_integer(client_sock, port);
            break;

        default:
            printf("undefined service: %d\n", proc);
            break;
        }
    }

    close(socket_desc);
    return 0;
}

int recv_integer(int client_sock)
{
    int read_size, value;

    // receive an integer from client
    read_size = recv(client_sock, &value, sizeof(value), 0);

    if (read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if (read_size == -1)
    {
        perror("recv failed");
    }

    return value;
}

void send_integer(int client_sock, int value)
{
    printf("server_result: %d\n", value);

    // send result to the client
    if (send(client_sock, &value, sizeof(value), 0) < 0)
    {
        puts("Send failed");
        exit(1);
    }
}
