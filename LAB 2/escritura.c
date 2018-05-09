#include "Headers.h"
#include "Funciones.h"

int main(int argc, char const *argv[])
{
	unsigned char* imgdata;
	int i =  atoi(argv[4]);
	bmpFileHeader* fh =(bmpFileHeader*)malloc(sizeof(bmpFileHeader));
	bmpInfoHeader* ih =(bmpInfoHeader*)malloc(sizeof(bmpInfoHeader));
	int status,p[2];
	iniciador(fh, ih);
	imgdata = lecturaPipe(0, nImagen,fh,ih);
	escribir(ih, fh, imgdata, i);
	printf("Termino una Line\n");
	return 0;
}