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
	
	
	unsigned char *imgdata;   /* datos de imagen */
	char* bm = (char*)malloc(sizeof(char)*2);
	int imagen, numbytes;
	
	unsigned int* size 		= (unsigned int*)malloc(sizeof(unsigned int));        /* Tamaño del archivo */
  unsigned short* resv1 = (unsigned short*)malloc(sizeof(unsigned short));       /* Reservado */
  unsigned short* resv2 	= (unsigned short*)malloc(sizeof(unsigned short));      /* Reservado */
  unsigned int* offset 	= (unsigned int*)malloc(sizeof(unsigned int));


  unsigned int* headersize	= (unsigned int*)malloc(sizeof(unsigned int));      /* Tamaño de la cabecera */
  unsigned int* width = (unsigned int*)malloc(sizeof(unsigned int));               /* Ancho */
  unsigned int* height = (unsigned int*)malloc(sizeof(unsigned int));          /* Alto */
  unsigned short* planes= (unsigned short*)malloc(sizeof(unsigned short));                  /* Planos de color (Siempre 1) */
  unsigned short* bpp = (unsigned short*)malloc(sizeof(unsigned short));             /* bits por pixel */
  unsigned int* compress = (unsigned int*)malloc(sizeof(unsigned int));        /* compresión */
  unsigned int* imgsize = (unsigned int*)malloc(sizeof(unsigned int));     /* tamaño de los datos de imagen */
  unsigned int* bpmx = (unsigned int*)malloc(sizeof(unsigned int));                /* Resolución X en bits por metro */
  unsigned int* bpmy = (unsigned int*)malloc(sizeof(unsigned int));                /* Resolución Y en bits por metro */
  unsigned int* colors = (unsigned int*)malloc(sizeof(unsigned int));              /* colors used en la paleta */
  unsigned int* imxtcolors = (unsigned int*)malloc(sizeof(unsigned int));      /* Colores importantes. 0 si son todos */
  
	
	
	
  imagen = open("imagen_1.bmp", O_RDONLY);
	
	
  
   /* Lectura BM */
	numbytes = read(imagen, bm, sizeof(char)*2);
	printf("%s\n", bm);
	
	//numbytes = read(imagen, buffer, sizeof(char));
	//printf("%s\n", buffer);
	
	numbytes = read(imagen, size, sizeof(unsigned int));
	printf("%d\n",size[0]);


	numbytes = read(imagen, resv1, sizeof(unsigned short));
	printf("%d\n",resv1[0] );
	
	numbytes = read(imagen, resv2, sizeof(unsigned short));
	printf("%d\n",resv2[0] );

	numbytes = read(imagen, offset, sizeof(unsigned int));
	printf("%d\n",offset[0]);



	numbytes = read(imagen, headersize, sizeof(unsigned int));
	printf("%d\n",headersize[0]);

	numbytes = read(imagen, width, sizeof(unsigned int));
	printf("%d\n",width[0]);

	numbytes = read(imagen, height, sizeof(unsigned int));
	printf("%d\n",height[0]);

	numbytes = read(imagen, planes, sizeof(unsigned short));
	printf("%d\n",planes[0] );

	numbytes = read(imagen, bpp, sizeof(unsigned short));
	printf("%d\n",bpp[0] );

	numbytes = read(imagen, compress, sizeof(unsigned int));
	printf("%d\n",compress[0]);

	numbytes = read(imagen, imgsize, sizeof(unsigned int));
	printf("%d\n",imgsize[0]);

	numbytes = read(imagen, bpmx, sizeof(unsigned int));
	printf("%d\n",bpmx[0]);

	numbytes = read(imagen, bpmy, sizeof(unsigned int));
	printf("%d\n",bpmy[0]);

	numbytes = read(imagen, colors, sizeof(unsigned int));
	printf("%d\n",colors[0]);

	numbytes = read(imagen, imxtcolors, sizeof(unsigned int));
	printf("%d\n",imxtcolors[0]);

	numbytes = read(imagen, imxtcolors, sizeof(unsigned int));
	printf("%d\n",imxtcolors[0]);



  close(imagen);
	exit(0);
	
  /* while ((numbytes = read(imagen, buffer, sizeof(char))) > 0){
	printf("%s", buffer);
	//write(fd2, &buffer, numbytes);
		
  }
   printf("\n");

 
  Cierre de archivos */
 
	return 0;
}






















