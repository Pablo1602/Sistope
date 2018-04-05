#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 
#define MAX 1024

//http://www.aprendeaprogramar.com/mod/resource/view.php?id=630

//https://poesiabinaria.net/2011/06/leyendo-archivos-de-imagen-en-formato-bmp-en-c/https://poesiabinaria.net/2011/06/leyendo-archivos-de-imagen-en-formato-bmp-en-c/

//https://os.mbed.com/handbook/C-Data-Types    Conversion 

int main(int argc, char const *argv[]){

  //int cantidadImg, uBnarizar, uCasifica, mostrar;
  
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
  int imagen, numbytes;
	unsigned int numero;
  char* buffer = (char*)malloc(sizeof(char)*MAX);
  imagen = open("imagen_0.bmp", O_RDONLY);
  
   /* Lectura BM */
	numbytes = read(imagen, buffer, sizeof(char));
	printf("%s\n", buffer);
	numbytes = read(imagen, buffer, sizeof(char));
	printf("%s\n", buffer);
	
	
	numbytes = read(imagen, numero, sizeof(unsigned int));
	printf("%d\n", numero);
	numbytes = read(imagen, numero, sizeof(unsigned int));
	printf("%d\n", numero);
	numbytes = read(imagen, numero, sizeof(unsigned int));
	printf("%d\n", numero);
	/*
	numbytes = read(imagen, buffer, sizeof(uint32_t));
		printf("%s\n", buffer);
	numbytes = read(imagen, buffer, sizeof(uint32_t));
		printf("%s\n", buffer);
	*/
	exit(0);
	
  /* while ((numbytes = read(imagen, buffer, sizeof(char))) > 0){
    printf("%s", buffer);
    //write(fd2, &buffer, numbytes);
		
  }
   printf("\n");

 
  Cierre de archivos */
  close(imagen);
 
	return 0;
}






















