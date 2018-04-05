#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 
#define MAX 1024

//http://www.aprendeaprogramar.com/mod/resource/view.php?id=630

//https://poesiabinaria.net/2011/06/leyendo-archivos-de-imagen-en-formato-bmp-en-c/

//https://os.mbed.com/handbook/C-Data-Types    Conversion 

typedef struct bmpFileHeader
{
  /* 2 bytes de identificación */
  unsigned int size;        /* Tamaño del archivo */
  unsigned short resv1;       /* Reservado */
  unsigned short resv2;       /* Reservado */
  unsigned int offset;      /* Offset hasta hasta los datos de imagen */
} bmpFileHeader;

typedef struct bmpInfoHeader
{
  unsigned int headersize;      /* Tamaño de la cabecera */
  unsigned int width;               /* Ancho */
  unsigned int height;          /* Alto */
  unsigned short planes;                  /* Planos de color (Siempre 1) */
  unsigned short bpp;             /* bits por pixel */
  unsigned int compress;        /* compresión */
  unsigned int imgsize;     /* tamaño de los datos de imagen */
  unsigned int bpmx;                /* Resolución X en bits por metro */
  unsigned int bpmy;                /* Resolución Y en bits por metro */
  unsigned int colors;              /* colors used en la paleta */
  unsigned int imxtcolors;      /* Colores importantes. 0 si son todos */
} bmpInfoHeader;



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
	
	bmpFileHeader header;     /* cabecera */
  unsigned char *imgdata;   /* datos de imagen */
	char* bm = (char*)malloc(sizeof(char)*2);
  int imagen, numbytes;
	
	
	
  imagen = open("imagen_0.bmp", O_RDONLY);
	
	
  
   /* Lectura BM */
	numbytes = read(imagen, bm, sizeof(char)*2);
	printf("%s\n", bm);
	
	//numbytes = read(imagen, buffer, sizeof(char));
	//printf("%s\n", buffer);
	
	numbytes = read(imagen, header, sizeof(bmpFileHeader));
	printf("%d\n", header.size);
	
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






















