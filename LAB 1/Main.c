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


void datapath(int cantidadImg, int uBinarizacion, int uClasificacion, int mostrar);
void iniciador(bmpFileHeader* fh, bmpInfoHeader* ih);
unsigned char* lectura(bmpFileHeader* fh, bmpInfoHeader* ih);
void gris(unsigned char* imagen, bmpInfoHeader* info);
void escribir(bmpInfoHeader* ih, bmpFileHeader* fh, unsigned char* imagen);
void binarizacion(int umbral, unsigned char* imagen, bmpInfoHeader* ih);
void clasificacion(int umbral, unsigned char* imagen, bmpInfoHeader* ih);

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
	
	datapath(cantidadImg, uBnarizar, uCasifica, mostrar);
 
	return 0;
}



void datapath(int cantidadImg, int uBinarizacion, int uClasificacion, int mostrar){
	int i;
	unsigned char* imgdata;
	bmpFileHeader* fh =(bmpFileHeader*)malloc(sizeof(bmpFileHeader));
	bmpInfoHeader* ih =(bmpInfoHeader*)malloc(sizeof(bmpInfoHeader));
	char* nImagen = (char*)malloc(sizeof(char)*10);
	
	iniciador(fh, ih);

	for (i = 1; i <= cantidadImg; ++i){
		strcpy(nImagen,"nombre_");
		strcat(nImagen, (char)i );
		// Lectura de imagen
		imgdata = lectura(nImagen, fh, ih);
		
	}

	//Inicio datapath


	gris(imgdata, ih);
	escribir(ih, fh, imgdata);
	binarizacion(150, imgdata, ih);
	clasificacion(70, imgdata, ih);

	// printf("Tamaño: %d\n",fh->size[0]);
	// printf("resv1: %d\n",fh->resv1[0] );
	// printf("res2v: %d\n",fh->resv2[0] );
	// printf("Inicio de los datos: %d\n",fh->offset[0]);
	// printf("Tamaño de la cabecera de bitmap: %d\n",ih->headersize[0]);
	// printf("Ancho pixeles: %d\n",ih->width[0]);
	// printf("Alto Pixeles: %d\n",ih->height[0]);
	// printf("Numero de planos: %d\n",ih->planes[0]);
	// printf("Tamaño cada punto: %d\n",ih->bpp[0]);
	// printf("Compreso?: %d\n",ih->compress[0]);
	// printf("tamaño imagen: %d\n",ih->imgsize[0]);
	// printf("Resolucion Horizontal: %d\n",ih->bpmx[0]);
	// printf("Resolución vertical: %d\n",ih->bpmy[0]);
	// printf("Tamaño de tabla colores: %d\n",ih->colors[0]);
	// printf("Contador de colores importantes: %d\n",ih->imxtcolors[0]);
	// exit(0);
}

unsigned char* lectura(char* nombre,bmpFileHeader* fh, bmpInfoHeader* ih){
	int imagen, numbytes, x, y;
	char* bm = (char*)malloc(sizeof(char)*2);

  	imagen = open(nombre, O_RDONLY);	
  
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

	lseek(imagen,fh->offset[0],SEEK_SET);
	for (int i = 0; i < ih->imgsize[0]; ++i){
		read(imagen, basura, sizeof(unsigned char));
		imgdata[i] = basura[0];
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

    for (int i = 0; i < ih->imgsize[0]; i+=4){
      	b=(imagen[i]);
      	g=(imagen[i+1]);
      	r=(imagen[i+2]);
      	//printf("(%d.%d.%d) ", b,g,r);
      	gris = r*0.3+g*0.59+b*0.11;
      	//printf("gris %d\n", gris);
      	imagen[i] = gris;
      	imagen[i+1] = gris;
      	imagen[i+2] = gris;
	}
  	
}

void binarizacion(int umbral, unsigned char* imagen, bmpInfoHeader* ih){
	for (int i = 0; i < ih->imgsize[0]; ++i){
		if(imagen[i] > umbral)
			imagen[i] = 1;
		else{
			imagen[i] = 0;
		}
	}
}

void clasificacion(int umbral, unsigned char* imagen, bmpInfoHeader* ih){
	float blanco = 0, negro = 0, porcentaje = 0;
	for (int i = 0; i < ih->imgsize[0]; ++i){
		if(imagen[i] == 1){
			blanco++;
		}
		else if(imagen[i] == 0){
			negro++;
		}
	}
	porcentaje = (negro / (blanco + negro))*100;

	if(porcentaje >= umbral){
		printf("Imagen es nearly black\n");
	}
	else{
		printf("Imagen no es nearly black\n");
	}
	printf("\n");
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

	lseek(escribir,fh->offset[0],SEEK_SET);
	numbytes = write(escribir, imagen, sizeof(ih->imgsize));
	for (int i = 0; i < ih->imgsize[0]; ++i){
		basura[0] = imagen[i];
		write(escribir, basura, sizeof(unsigned char));
	}
	
	close(escribir);
}



















