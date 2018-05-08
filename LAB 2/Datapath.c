#include "Headers.h"
#include "Funciones.h"

int main(int argc, char const *argv[])
{
	int cantidadImg    =  atoi(argv[1]);
	int uBnarizar = atoi(argv[2]);
	int uCasifica = atoi(argv[3]);
	int mostrar = atoi(argv[4]);
	datapath(cantidadImg, uBnarizar, uCasifica, mostrar);

	return 0;
}