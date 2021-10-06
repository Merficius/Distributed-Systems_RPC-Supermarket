// store messages using a service

#include "cliente.h"

int sock;				  // server socket
char *host = "127.0.0.1"; // server name

int main(int argc, char *argv[])
{
	int idProducto;
	int cantidad;
	float efectivoDisponible;

	SUPERMERCADO superama;
	superama.nombre = "Superama";
	superama.numeroDePersonas = 21;
	for (int i = 0; i < 2; i++)
	{
		superama.productos[i].id = i + 1;
	}
	superama.productos[0].cantidadDisponible = 7;
	superama.productos[0].costo = 21.5;
	superama.productos[1].cantidadDisponible = 3;
	superama.productos[1].costo = 34;

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

	printf("El mensaje fue almacenado\n");
	close(sock);

	return 1;
}
