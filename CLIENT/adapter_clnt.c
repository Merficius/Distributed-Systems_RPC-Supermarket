#include "cliente.h"

extern int sock;

SUPERMERCADO comprarProducto(SUPERMERCADO s, int idProducto, int cantidad, float efectivoDisponible)
{
    //int length = strlen(m); // "hola" -> length = 4
    //int read_size, result;
    //int id_length = strlen(m);
    //int cantidad_length = strlen(m);
    //int efectivoDisponible_length = strlen(m);

    // Enviar nombre de supermercado
    char *nombre = s.nombre;
    int length = strlen(nombre);
    send(sock, &length, sizeof(length), 0);
    send(sock, nombre, length, 0);

    int numeroDePersonas = s.numeroDePersonas;
    send(sock, &s.numeroDePersonas, sizeof(s.numeroDePersonas), 0);

    
    for (int i = 0; i < sizeof(s.productos) / sizeof(s.productos[0]); i++)
    {
        // Enviar id, cantidad y costo de cada producto
        send(sock, &s.productos[i].id, sizeof(s.productos[i].id), 0);
        send(sock, &s.productos[i].cantidadDisponible, sizeof(s.productos[i].cantidadDisponible), 0);
        send(sock, &s.productos[i].costo, sizeof(s.productos[i].costo), 0);
    }

    send(sock, &idProducto, sizeof(idProducto), 0);
    send(sock, &cantidad, sizeof(cantidad), 0);
    send(sock, &efectivoDisponible, sizeof(efectivoDisponible), 0);

    // Recibe nombre de supermercado
    recv(sock, &length, sizeof(length), 0);
    s.nombre = (char *)malloc(length);
    recv(sock, s.nombre, length, 0);

    // Recibe número de personas
    recv(sock, &s.numeroDePersonas, sizeof(s.numeroDePersonas), 0);

    // recibir id, cantidad y costo de cada producto
    for (int i = 0; i < sizeof(s.productos) / sizeof(s.productos[0]); i++)
    {
        recv(sock, &s.productos[i].id, sizeof(s.productos[i].id), 0);
        recv(sock, &s.productos[i].cantidadDisponible, sizeof(s.productos[i].cantidadDisponible), 0);
        recv(sock, &s.productos[i].costo, sizeof(s.productos[i].costo), 0);
    }

    printf("recibiendo por cliente: %s, %d, %d, %d, %f, %d, %d, %f\n", s.nombre, s.numeroDePersonas, s.productos[0].id, s.productos[0].cantidadDisponible, s.productos[0].costo, s.productos[1].id, s.productos[1].cantidadDisponible, s.productos[1].costo);
    // if (send(sock, idProducto, idProducto, 0) < 0)
    // {
    //     puts("Send failed");
    //     exit(1);
    // }

    // receive the result from server
    //read_size = recv(sock, &result, sizeof(result), 0);

    // if (read_size == 0)
    // {
    //     puts("Client disconnected");
    //     fflush(stdout);
    // }
    // else if (read_size == -1)
    // {
    //     perror("recv failed");
    // }

    return s; //result;
}


