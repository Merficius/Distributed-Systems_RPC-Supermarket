#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

SUPERMERCADO comprarProducto(SUPERMERCADO s, int idProducto, int cantidad, float efectivoDisponible);
