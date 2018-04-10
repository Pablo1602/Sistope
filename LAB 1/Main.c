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

//Funciones llamados a sistema http://sopa.dis.ulpgc.es/prog_c/FICHER.HTM

typedef struct bmpFileHeader
{
  /* 2 bytes de identificación */
  unsigned int* size;        /* Tamaño del archivo */
  unsigned short* resv1;       /* Reservado */
  unsigned short* resv2;       /* Reservado */
  unsigned int* offset;      /* Offset hasta hasta los datos de imagen */
} bmpFileHeader;

typedef struct bmpInfoHeader
{
  unsigned int* headersize;      /* Tamaño de la cabecera */
  unsigned int* width;               /* Ancho */
  unsigned int* height;          /* Alto */
  unsigned short* planes;                  /* Planos de color (Siempre 1) */
  unsigned short* bpp;             /* bits por pixel */
  unsigned int* compress;        /* compresión */
  unsigned int* imgsize;     /* tamaño de los datos de imagen */
  unsigned int* bpmx;                /* Resolución X en bits por metro */
  unsigned int* bpmy;                /* Resolución Y en bits por metro */
  unsigned int* colors;              /* colors used en la paleta */
  unsigned int* imxtcolors;      /* Colores importantes. 0 si son todos */
} bmpInfoHeader;



void iniciador(bmpFileHeader* fh, bmpInfoHeader* ih);
unsigned char* lectura(bmpFileHeader* fh, bmpInfoHeader* ih);
void gris(unsigned char* imagen, bmpInfoHeader* info);
void escribir(bmpInfoHeader* ih, bmpFileHeader* fh, unsigned char* imagen);

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
	
	unsigned char* imgdata;
	bmpFileHeader* fh =(bmpFileHeader*)malloc(sizeof(bmpFileHeader));
	bmpInfoHeader* ih =(bmpInfoHeader*)malloc(sizeof(bmpInfoHeader));
	
	iniciador(fh, ih);
	imgdata = lectura(fh, ih);
	gris(imgdata, ih);
	escribir(ih, fh, imgdata);
	//printf("%d\n", imgdata[0]);

	printf("Tamaño: %d\n",fh->size[0]);
	printf("resv1: %d\n",fh->resv1[0] );
	printf("res2v: %d\n",fh->resv2[0] );
	printf("Inicio de los datos: %d\n",fh->offset[0]);
	printf("Tamaño de la cabecera de bitmap: %d\n",ih->headersize[0]);
	printf("Ancho pixeles: %d\n",ih->width[0]);
	printf("Alto Pixeles: %d\n",ih->height[0]);
	printf("Numero de planos: %d\n",ih->planes[0]);
	printf("Tamaño cada punto: %d\n",ih->bpp[0]);
	printf("Compreso?: %d\n",ih->compress[0]);
	printf("tamaño imagen: %d\n",ih->imgsize[0]);
	printf("Resolucion Horizontal: %d\n",ih->bpmx[0]);
	printf("Resolución vertical: %d\n",ih->bpmy[0]);
	printf("Tamaño de tabla colores: %d\n",ih->colors[0]);
	printf("Contador de colores importantes: %d\n",ih->imxtcolors[0]);
	exit(0);
 
	return 0;
}



unsigned char* lectura(bmpFileHeader* fh, bmpInfoHeader* ih){
	int imagen, numbytes, x, y;
	char* bm = (char*)malloc(sizeof(char)*2);

  	imagen = open("imagen_1.bmp", O_RDONLY);	
  
   /* Lectura BM */
	numbytes = read(imagen, bm, sizeof(char)*2);
	numbytes = read(imagen, fh->size, sizeof(unsigned int));
	numbytes = read(imagen, fh->resv1, sizeof(unsigned short));
	numbytes = read(imagen, fh->resv2, sizeof(unsigned short));
	numbytes = read(imagen, fh->offset, sizeof(unsigned int));


	numbytes = read(imagen, ih->headersize, sizeof(unsigned int));
	numbytes = read(imagen, ih->width, sizeof(unsigned int));
	numbytes = read(imagen, ih->height, sizeof(unsigned int));
	numbytes = read(imagen, ih->planes, sizeof(unsigned short));
	numbytes = read(imagen, ih->bpp, sizeof(unsigned short));
	numbytes = read(imagen, ih->compress, sizeof(unsigned int));
	numbytes = read(imagen, ih->imgsize, sizeof(unsigned int));
	numbytes = read(imagen, ih->bpmx, sizeof(unsigned int));
	numbytes = read(imagen, ih->bpmy, sizeof(unsigned int));
	numbytes = read(imagen, ih->colors, sizeof(unsigned int));
	numbytes = read(imagen, ih->imxtcolors, sizeof(unsigned int));

	unsigned char* imgdata = (unsigned char*)malloc(sizeof(unsigned char)*ih->imgsize[0]);   /* datos de imagen */
	unsigned char* basura = (unsigned char*)malloc(sizeof(unsigned char));;
	/*int i, pos;
	pos = fh->offset[0] - 53;
	for(i=1; i< pos;i++){
		numbytes = read(imagen, basura, sizeof(unsigned char));
	}*/
	lseek(imagen,fh->offset[0],SEEK_SET);
	//numbytes = read(imagen, imgdata, sizeof(unsigned char)*ih->imgsize[0]);	
	for (int i = 0; i < ih->imgsize[0]; ++i){
		read(imagen, basura, sizeof(unsigned char));
		imgdata[i] = basura[0];
		//printf("%d ", basura[0]);
	}
  	close(imagen);
  	return imgdata;
}

void iniciador(bmpFileHeader* fh, bmpInfoHeader* ih){
	fh->size = (unsigned int*)malloc(sizeof(unsigned int));        /* Tamaño del archivo */
	fh->resv1 = (unsigned short*)malloc(sizeof(unsigned short));       /* Reservado */
	fh->resv2 = (unsigned short*)malloc(sizeof(unsigned short));      /* Reservado */
	fh->offset = (unsigned int*)malloc(sizeof(unsigned int));


	ih->headersize = (unsigned int*)malloc(sizeof(unsigned int));      /* Tamaño de la cabecera */
	ih->width = (unsigned int*)malloc(sizeof(unsigned int));               /* Ancho */
	ih->height = (unsigned int*)malloc(sizeof(unsigned int));          /* Alto */
	ih->planes= (unsigned short*)malloc(sizeof(unsigned short));                  /* Planos de color (Siempre 1) */
	ih->bpp = (unsigned short*)malloc(sizeof(unsigned short));             /* bits por pixel */
	ih->compress = (unsigned int*)malloc(sizeof(unsigned int));        /* compresión */
	ih->imgsize = (unsigned int*)malloc(sizeof(unsigned int));     /* tamaño de los datos de imagen */
	ih->bpmx = (unsigned int*)malloc(sizeof(unsigned int));                /* Resolución X en bits por metro */
	ih->bpmy = (unsigned int*)malloc(sizeof(unsigned int));                /* Resolución Y en bits por metro */
	ih->colors = (unsigned int*)malloc(sizeof(unsigned int));              /* colors used en la paleta */
	ih->imxtcolors = (unsigned int*)malloc(sizeof(unsigned int));      /* Colores importantes. 0 si son todos */
}

void gris(unsigned char* imagen, bmpInfoHeader* ih){
	unsigned int x, y, r, g ,b, gris;
	for (y=ih->height[0]; y>0; y--){
      for (x=0; x<ih->width[0]; x++){
      	b=(imagen[3*(x+y*ih->width[0])]);
      	g=(imagen[3*(x+y*ih->width[0])+1]);
      	r=(imagen[3*(x+y*ih->width[0])+2]);
      	//printf("(%d.%d.%d) ", b,g,r);
      	gris = r*0.3+g*0.59+b*0.11;
      	//printf("gris %d\n", gris);
      	imagen[3*(x+y*ih->width[0])] = gris;
      	imagen[3*(x+y*ih->width[0])+1] = gris;
      	imagen[3*(x+y*ih->width[0])+2] = gris;
      	//printf("(%d.%d.%d)", imagen[3*(x+y*ih->width[0])], imagen[3*(x+y*ih->width[0])+1], imagen[3*(x+y*ih->width[0])+2]);
    	}
    	//printf("\n");
    }
  	
}

void escribir(bmpInfoHeader* ih, bmpFileHeader* fh, unsigned char* imagen){
	int escribir, numbytes, x, y;
	unsigned char* basura = (unsigned char*)malloc(sizeof(unsigned char));;
	char* bm = "BM";
	escribir = open("salida.bmp", O_CREAT|O_WRONLY, S_IRWXU);
	
	numbytes = write(escribir, bm, sizeof(char)*2);
	numbytes = write(escribir, fh->size, sizeof(unsigned int));
	numbytes = write(escribir, fh->resv1, sizeof(unsigned short));
	numbytes = write(escribir, fh->resv2, sizeof(unsigned short));
	numbytes = write(escribir, fh->offset, sizeof(unsigned int));
	numbytes = write(escribir, ih->headersize, sizeof(unsigned int));
	numbytes = write(escribir, ih->width, sizeof(unsigned int));
	numbytes = write(escribir, ih->height, sizeof(unsigned int));
	numbytes = write(escribir, ih->planes, sizeof(unsigned short));
	numbytes = write(escribir, ih->bpp, sizeof(unsigned short));
	numbytes = write(escribir, ih->compress, sizeof(unsigned int));
	numbytes = write(escribir, ih->imgsize, sizeof(unsigned int));
	numbytes = write(escribir, ih->bpmx, sizeof(unsigned int));
	numbytes = write(escribir, ih->bpmy, sizeof(unsigned int));
	numbytes = write(escribir, ih->colors, sizeof(unsigned int));
	numbytes = write(escribir, ih->imxtcolors, sizeof(unsigned int));
	
	/*
	int i, pos;
	pos = fh->offset[0] - 53;
	for(i=1; i< pos;i++){
		numbytes = write(escribir, basura, sizeof(unsigned char));
	}*/
	lseek(escribir,fh->offset[0],SEEK_SET);
	numbytes = write(escribir, imagen, sizeof(ih->imgsize));
	for (int i = 0; i < ih->imgsize[0]; ++i){
		basura[0] = imagen[i];
		//printf("%d ", basura[0]);
		write(escribir, basura, sizeof(unsigned char));
	}
	
	close(escribir);
}



















