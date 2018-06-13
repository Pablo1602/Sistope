#include "Headers.h"
#include "Funciones.h"

int main(int argc, char *const argv[]){

  int cantidadImg, uBnarizar, uCasifica, mostrar, numHbr;
  int c;
  while ((c = getopt (argc, argv, "c:h:u:n:b")) != -1){
		switch (c){
			case 'c':
				sscanf(optarg, "%d", &cantidadImg);
				break;
			case 'h':
				sscanf(optarg, "%d", &numHbr);
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
	datapath(cantidadImg, numHbr, uBnarizar, uCasifica, mostrar);
	return 0;
}

