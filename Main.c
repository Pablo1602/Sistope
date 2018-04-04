#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>


//Maximo Largo Linea 50
//Formato archivo : sin salto de linea al final del archivo

//Structura guarda registros
typedef struct cosa{

}reg;


int main(int argc, char const *argv[]){

  int cantidadImg, uBnarizar, uCasifica, mostrar;
  
  /*while ((c = getopt (argc, argv, "c:u:n:b:")) != -1){
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
		        if (optopt == 'c' || optopt == 'u' || optopt == 'n' || optopt == 'b')
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
  exit(0);*/
  int imagen;
  imagen = open("imagen_1.bmp", O_RDONLY); 
  
 
	return 0;
}
