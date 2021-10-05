
/* services.c: Código para el servidor de nombres */

#include "server.h"

// servicios del servidor de nombres

int entry = NIL;
LOCATION directory[TABLE_SIZE];

void register_service(int id, int port)
{
    // Cambio de puerto para un id registrado
    for (int i = 0; i < entry; i++)
    {
        if (directory[i].id == id)
        {
            directory[i].port = port;
            return;
        }
    }

    directory[entry].id = id;
    directory[entry].port = port;

    entry++; // no se debe rebasar TABLE_SIZE
}

int find_service(int id)
{
    for (int i = 0; i < entry; i++)
    {
        if (directory[i].id == id)
        {
            return directory[i].port;
        }
    }

    // no lo encontró
    return NIL;
}
