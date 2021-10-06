#include "supermercado.h"

int main(int argc, char *argv[])
{
	int idProducto;
	int cantidad;
	float efectivoDisponible;
	FILE *f = fopen("superama.txt", "r+"); // read only

	SUPERMERCADO superama;
	superama.nombre = (char *)malloc(20);
	fscanf(f, "%s%d", superama.nombre, &superama.numeroDePersonas);
	for (int i = 0; i < 2; i++)
	{
		fscanf(f, "%d", &superama.productos[i].id);
		fscanf(f, "%d", &superama.productos[i].cantidadDisponible);
		fscanf(f, "%f\n", &superama.productos[i].costo);
	}

	fclose(f); // Closing the read file
	
	if (argc == 1)
	{
		printf("Bienvenido a Superama! tenemos los siguientes productos ordenados por id:\n1.- Leche\n2.- Detergente\n\n");
		for (int i = 0; i < 2; i++)
		{
			printf("id:%d\n\tCantidad %d\n\tCosto $%f\n\n", superama.productos[i].id, superama.productos[i].cantidadDisponible, superama.productos[i].costo);
		}

		printf("\nServicios disponibles:\n\n1.- Comprar producto\n");
		printf("\nUso: %s <servicio> <idProducto> <cantidad> <efectivoDisponible>\n", argv[0]);

		return 0;
	}
	
	if (argc != 5)
	{
		fprintf(stderr,
				"Uso: %s <servicio> <idProducto> <cantidad> <efectivoDisponible>\n", argv[0]);
		exit(1);
	}

	idProducto = atoi(argv[2]);
	cantidad = atoi(argv[3]);
	efectivoDisponible = atof(argv[4]);

	superama = comprarProducto(superama, idProducto, cantidad, efectivoDisponible); // as if it was a local call!

	FILE *write_file = fopen("superama.txt", "w"); // write only

	fprintf(write_file, "%s %d\n", superama.nombre, superama.numeroDePersonas);
	
	for (int i = 0; i < 2; i++)
	{
		fprintf(write_file, "%d ", superama.productos[i].id);
		fprintf(write_file, "%d ", superama.productos[i].cantidadDisponible);
		fprintf(write_file, "%f\n", superama.productos[i].costo);
	}

	fclose(write_file); // Closing the write file
	printf("El mensaje fue almacenado\n");

	return 1;
}

SUPERMERCADO comprarProducto(SUPERMERCADO s, int idProducto, int cantidad, float efectivoDisponible)
{
	int indiceDeProducto = idProducto - 1;

	if (cantidad > s.productos[indiceDeProducto].cantidadDisponible)
	{
		printf("No hay suficiente productos disponibles :(\n");
		return s;
	}

	float costoDeProducto = s.productos[indiceDeProducto].costo;
	float costoTotal = cantidad * costoDeProducto;

	if (efectivoDisponible >= costoTotal)
	{
		s.productos[indiceDeProducto].cantidadDisponible -= cantidad;
		printf("El cambio para el cliente es de: %f\n", efectivoDisponible - costoTotal);
	}
	else
	{
		printf("No te alcanza :(\n");
	}

	return s;
}
