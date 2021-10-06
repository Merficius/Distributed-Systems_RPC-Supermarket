#include "servidor.h"

void register_service(int id, int port);
SUPERMERCADO recv_messages(int client_sock);
void send_result(int client_sock, SUPERMERCADO s);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr,
                "Uso: %s <id-servicio>\n", argv[0]);
        exit(1);
    }

    register_service(atoi(argv[1]), SERVICE_PORT);
    int socket_desc = initialization(SERVICE_PORT);

    while (1)
    {
        int client_sock = connection(socket_desc);
        int idProducto;
        int cantidad;
        float efectivoDisponible;

        SUPERMERCADO s = recv_messages(client_sock);

        recv(client_sock, &idProducto, sizeof(idProducto), 0);
        recv(client_sock, &cantidad, sizeof(cantidad), 0);
        recv(client_sock, &efectivoDisponible, sizeof(efectivoDisponible), 0);
    
        s = comprarProducto(s, idProducto, cantidad, efectivoDisponible);

        send_result(client_sock, s);
    }

    close(socket_desc);
    return 0;
}

void register_service(int id, int port)
{
    int proc = 1; // id del servicio
    int sock = portmapper("127.0.0.1");

    send(sock, &proc, sizeof(proc), 0);
    send(sock, &id, sizeof(id), 0);

    if (send(sock, &port, sizeof(port), 0) < 0)
    {
        puts("Send failed");
        exit(1);
    }

    close(sock);
}

SUPERMERCADO recv_messages(int client_sock)
{
    SUPERMERCADO s;
    int message1, message2;
    float message;
    int length;
    char *str;

    // Recibe nombre de supermercado
    recv(client_sock, &length, sizeof(length), 0);
    s.nombre = (char *)malloc(length);
    recv(client_sock, s.nombre, length, 0);

    // Recibe número de personas
    recv(client_sock, &s.numeroDePersonas, sizeof(s.numeroDePersonas), 0);

    // recibir id, cantidad y costo de cada producto
    for (int i = 0; i < sizeof(s.productos) / sizeof(s.productos[0]); i++)
    {
        recv(client_sock, &s.productos[i].id, sizeof(s.productos[i].id), 0);
        recv(client_sock, &s.productos[i].cantidadDisponible, sizeof(s.productos[i].cantidadDisponible), 0);
        recv(client_sock, &s.productos[i].costo, sizeof(s.productos[i].costo), 0);
    }

    return s;
}

void send_result(int client_sock, SUPERMERCADO s)
{
    char *nombre = s.nombre;
    int length = strlen(nombre);
    send(client_sock, &length, sizeof(length), 0);
    send(client_sock, nombre, length, 0);

    int numeroDePersonas = s.numeroDePersonas;
    send(client_sock, &s.numeroDePersonas, sizeof(s.numeroDePersonas), 0);

    for (int i = 0; i < sizeof(s.productos) / sizeof(s.productos[0]); i++)
    {
        // Enviar id, cantidad y costo de cada producto
        send(client_sock, &s.productos[i].id, sizeof(s.productos[i].id), 0);
        send(client_sock, &s.productos[i].cantidadDisponible, sizeof(s.productos[i].cantidadDisponible), 0);
        send(client_sock, &s.productos[i].costo, sizeof(s.productos[i].costo), 0);
    }
}
