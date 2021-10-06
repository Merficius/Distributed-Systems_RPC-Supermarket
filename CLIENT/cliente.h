#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>
#include <sys/socket.h>

#define PORTMAPPER 1111

typedef struct
{
    int id;
    int port;
} LOCATION;

typedef struct
{
    int id;
    int cantidadDisponible;
    float costo;
} PRODUCTO;

typedef struct
{
    char *nombre;
    int numeroDePersonas;
    PRODUCTO productos[2];
} SUPERMERCADO;

// utilities
int connection(int port);
int close(int sock);

// remote services
int store(char *m);
SUPERMERCADO comprarProducto(SUPERMERCADO s, int idProducto, int cantidad, float efectivoDisponible);
int find_service(int id);
