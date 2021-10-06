#include "servidor.h"

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
