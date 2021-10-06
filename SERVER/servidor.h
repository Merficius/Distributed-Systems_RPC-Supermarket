#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORTMAPPER 1111 // Servidor de nombres
#define SERVICE_PORT 4444

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

// utilerias
int portmapper(char *host);      // conexión con servidor de nombres
int initialization();            // inicialización del servicio
int connection(int socket_desc); // esperar a los clientes
int close(int sock);

// servicio(s)
int store(char *m);
SUPERMERCADO comprarProducto(SUPERMERCADO s, int idProducto, int cantidad, float efectivoDisponible);
