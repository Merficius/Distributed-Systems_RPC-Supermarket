// store messages using a service

#include "cliente.h"

int sock;				  // server socket
char *host = "127.0.0.1"; // server name

int main(int argc, char *argv[])
{
	int idProducto;
	int cantidad;
	float efectivoDisponible;
	FILE *f = fopen("superama.txt", "r"); // read only

	SUPERMERCADO superama;
	fscanf(f, "%s", superama.nombre);
	fscanf(f, "%d\n", &superama.numeroDePersonas);
	for (int i = 0; i < 2; i++)
	{
		fscanf(f, "%d", &superama.productos[i].id);
		fscanf(f, "%d", &superama.productos[i].cantidadDisponible);
		fscanf(f, "%f\n", &superama.productos[i].costo);
	}

	//printf("%s,%d,%d,%d,%f,%d,%d,%f", superama.nombre, superama.numeroDePersonas, superama.productos[0].id, superama.productos[0].cantidadDisponible, superama.productos[0].costo, superama.productos[1].id, superama.productos[1].cantidadDisponible, superama.productos[1].costo);
	
	if (argc == 1)
	{
		printf("Bienvenido a Superama! tenemos los siguientes productos ordenados por id:\n1.- Leche\n2.- Detergente\n\n");
		for (int i = 0; i < 2; i++)
		{
			printf("id:%d\n\tCantidad %d\n\tCosto $%f\n\n", superama.productos[i].id, superama.productos[i].cantidadDisponible, superama.productos[i].costo);
		}
		
		return 0;
	}
	fclose(f); // Closing the file
	if (argc != 5)
	{
		fprintf(stderr,
				"Uso: %s <servicio> <idProducto> <cantidad> <efectivoDisponible>\n", argv[0]);
		exit(1);
	}

	idProducto = atoi(argv[2]);
	cantidad = atoi(argv[3]);
	efectivoDisponible = atof(argv[4]);

	int port = find_service(atoi(argv[1]));
	sock = connection(port);														// remote invocation
	superama = comprarProducto(superama, idProducto, cantidad, efectivoDisponible); // as if it was a local call!

	//printf("%s,%d,%d,%d,%f,%d,%d,%f", superama.nombre, superama.numeroDePersonas, superama.productos[0].id, superama.productos[0].cantidadDisponible, superama.productos[0].costo, superama.productos[1].id, superama.productos[1].cantidadDisponible, superama.productos[1].costo);

	printf("El mensaje fue almacenado\n");
	close(sock);

	return 1;
}
