#include "Headers.h"
#include "Funciones.h"

int main(int argc, char *const argv[]){

  int cantidadImg, uBnarizar, uCasifica, mostrar;
  int c;
  while ((c = getopt (argc, argv, "c:u:n:b")) != -1){
		switch (c){
			case 'c':
				sscanf(optarg, "%d", &cantidadImg);
				break;
			case 'u':
				sscanf(optarg, "%d", &uBnarizar);
				break;
			case 'n':
				sscanf(optarg, "%d", &uCasifica);
				break;
			case 'b':
				mostrar = 1;
				break;
			case '?':
				if (optopt == 'c' || optopt == 'u' || optopt == 'n')
				  fprintf (stderr, "Opcion -%c requiere un argumento.\n", optopt);
				else if (isprint (optopt))
				  fprintf (stderr, "Opcion desconocida `-%c'.\n", optopt);
				else
				  fprintf (stderr,"Opcion con caracter desconocido `\\x%x'.\n",optopt);
				return 0;
			default:
				abort ();
		}
	}
	datapath(cantidadImg, uBnarizar, uCasifica, mostrar);
	return 0;
}

