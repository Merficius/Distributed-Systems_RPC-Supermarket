// Almacena mensajes en "mensajes.txt"

/* servicio.c: Código para el servidor */

#include <stdio.h>
#include <string.h>

// Agrega un nuevo mensaje al archivo

int store(char *m)
{
	FILE *fp = fopen("mensajes.txt", "a");

	fprintf(fp, "%s\n", m);
	fclose(fp);

	return strlen(m);
}

