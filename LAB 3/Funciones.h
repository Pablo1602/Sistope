#ifndef FUNCIONES_H
#define FUNCIONES_H
#include "Headers.h"


img* iniciadorImagen(img* contenido, int* num, int* binarizacion, int* clasificacion){
	contenido = (img*)malloc(sizeof(img));
	contenido->file =(bmpFileHeader*)malloc(sizeof(bmpFileHeader));
	contenido->info =(bmpInfoHeader*)malloc(sizeof(bmpInfoHeader));
	contenido->numero = (int*)malloc(sizeof(int));
	contenido->numero = num;
	contenido->clasificacion = (int*)malloc(sizeof(int));
	contenido->clasificacion = clasificacion;
	contenido->binarizacion = (int*)malloc(sizeof(int));
	contenido->binarizacion = binarizacion;
	iniciador(contenido->file, contenido->info);
	return contenido;
}


// Funcion: Se encarga de la ejecucion del "datapath" completo, llamando a las demas imagenes para que realizen su función
// Entrada: cantidad de imagenes, umbral de binarizacion, umbral de clasificacion y instruccion si se debe moistrar resultado por pantalla o no
// Salida: Ejecucción del Programa

void datapath(int cantidadImg,int numeroHebras, int uBinarizacion, int uClasificacion, int mostrar){
	int i, j, check;
	img* contenidoImagen;
	char* numero = (char*)malloc(sizeof(char)*5);
	if (mostrar == 1){
		printf("| 	Numero Imagen 	| 	Nearly black 	|\n-------------------------------------------------\n");
	}
	
	pthread_t* hebras;
	hebras = (pthread_t*)malloc(sizeof(pthread_t)*numeroHebras);
	pthread_mutex_init(&lock, NULL);
	check = pthread_barrier_init(&mybarrier, NULL, numeroHebras + 1);
	if(check){
		fprintf(stderr, "pthread_barrier_init: %s\n", strerror(check));
        exit(1);
	}

	for (i = 1; i <= cantidadImg; ++i){
		contenidoImagen = iniciadorImagen(contenidoImagen, &i, &uBinarizacion, &uClasificacion);
		negro = 0; 
		blanco = 0;
		porcentaje = 0;
		
		// Hebra 1 tiene que leer la imagen
		pthread_create(&hebras[0], NULL, (void*)lectura, (void*)contenidoImagen);
		pthread_create(&hebras[1], NULL, (void*)lectura, (void*)contenidoImagen);
		pthread_create(&hebras[2], NULL, (void*)lectura, (void*)contenidoImagen);
		pthread_create(&hebras[3], NULL, (void*)lectura, (void*)contenidoImagen);
		printf("fin lectura %d\n",contenidoImagen->file->size[0]); 
		
		printf("Imagen de tamaño %d\n", contenidoImagen->info->imgsize[0]); 
		for (j = 0; j < contenidoImagen->info->imgsize[0]; ++j)
		{
			printf("%d ", contenidoImagen->imgdata[j]);
		}
		printf("\n");

		//n Hebras tienen que pasar a gris imagen.

		pthread_create(&hebras[0], NULL, (void*)gris, (void*)contenidoImagen);
		printf("fin gris %d\n",contenidoImagen->imgdata[100]); 

		//n Hebras tienen que binarizar imagen .

		pthread_create(&hebras[0], NULL, (void*)binarizacion, (void*)contenidoImagen);
		printf("fin binarizacion %d\n",contenidoImagen->imgdata[100]); 
		
		//hebras deben contar los negros que existen en la imagen luego de binarizarla 
		if (mostrar == 1){
		printf("| 	%d	|",i);
		}
		pthread_create(&hebras[0], NULL, (void*)clasificacion, (void*)contenidoImagen);

		if(porcentaje >= uClasificacion){
			if (mostrar == 1){
				printf(" 	Yes		|\n");
			}
		}
		else{
			if (mostrar == 1){
				printf(" 	No		|\n");
			}
		}

		
		// esto debe hacerlo main, no proceso
		escribir(contenidoImagen->info, contenidoImagen->file, contenidoImagen->imgdata, i); 
 		
 		/*for (j=0; j<numeroHebras; j++) {
    		pthread_join(hebras[j], NULL);
  		}*/
		pthread_barrier_destroy(&mybarrier);
		pthread_mutex_destroy(&lock);
		printf("TERMINE :)\n");
	}
	
}

// Funcion: Se encarga de leer los archivos de imagen y guardarlo en variables correspondientes
// Entrada: Nombre de archivo a leer, puntero estructura FileHeader y InfoHeader vacios
// Salida: puntero estructura FileHeader y InfoHeader vacios y imagen leida
// void *lectura(void* imgdata, void* nombreEntrada, void* fh, void* ih){}
void *lectura(void* contenido){
	img* contenidoImagen = (img*)contenido;
	contenidoImagen->info = (bmpInfoHeader*)contenidoImagen->info;
	contenidoImagen->file = (bmpFileHeader*)contenidoImagen->file;
	contenidoImagen-> imgdata = (unsigned char*)contenidoImagen -> imgdata;
	int * a = (int*)contenidoImagen -> numero;

	char* nImagen = (char*)malloc(sizeof(char)*10);	
	sprintf(nImagen, "imagen_%d.bmp",*contenidoImagen->numero);
	
	int imagen, numbytes, x, y;
	char* bm = (char*)malloc(sizeof(char)*2);
  	imagen = open(nImagen, O_RDONLY);	
	numbytes = read(imagen, bm, sizeof(char)*2);
	numbytes = read(imagen, contenidoImagen->file->size, sizeof(unsigned int));
	numbytes = read(imagen, contenidoImagen->file->resv1, sizeof(unsigned short));
	numbytes = read(imagen, contenidoImagen->file->resv2, sizeof(unsigned short));
	numbytes = read(imagen, contenidoImagen->file->offset, sizeof(unsigned int));

	numbytes = read(imagen, contenidoImagen->info->headersize, sizeof(unsigned int));
	numbytes = read(imagen, contenidoImagen->info->width, sizeof(unsigned int));
	numbytes = read(imagen, contenidoImagen->info->height, sizeof(unsigned int));
	numbytes = read(imagen, contenidoImagen->info->planes, sizeof(unsigned short));
	numbytes = read(imagen, contenidoImagen->info->bpp, sizeof(unsigned short));
	numbytes = read(imagen, contenidoImagen->info->compress, sizeof(unsigned int));
	numbytes = read(imagen, contenidoImagen->info->imgsize, sizeof(unsigned int));
	numbytes = read(imagen, contenidoImagen->info->bpmx, sizeof(unsigned int));
	numbytes = read(imagen, contenidoImagen->info->bpmy, sizeof(unsigned int));
	numbytes = read(imagen, contenidoImagen->info->colors, sizeof(unsigned int));
	numbytes = read(imagen, contenidoImagen->info->imxtcolors, sizeof(unsigned int));

	unsigned char* imgdata1 = (unsigned char*)malloc(sizeof(unsigned char)*contenidoImagen->info->imgsize[0]);
	contenidoImagen->imgdata = (unsigned char*)malloc(sizeof(unsigned char)*contenidoImagen->info->imgsize[0]);
	unsigned char* basura = (unsigned char*)malloc(sizeof(unsigned char));;
	

	lseek(imagen,contenidoImagen->file->offset[0],SEEK_SET);

	for (int i = 0; i < contenidoImagen->info->imgsize[0]; ++i){
		read(imagen, basura, sizeof(unsigned char));
		imgdata1[i] = basura[0];
	}
	contenidoImagen-> imgdata = imgdata1;
  	close(imagen);
  	contenido = (void*) contenidoImagen;
  	pthread_barrier_wait(&mybarrier);
  	return NULL;
  }



// Funcion: Se encarga de asignar memoria a los punteros para guardar header de imagen con informacion de estas
// Entrada: Puntero estructura FileHeader y InfoHeader vacios
// Salida: puntero estructura FileHeader y InfoHeader con memoria asignada

void iniciador(bmpFileHeader* fh, bmpInfoHeader* ih){
	fh->size = (unsigned int*)malloc(sizeof(unsigned int));        
	fh->resv1 = (unsigned short*)malloc(sizeof(unsigned short));     
	fh->resv2 = (unsigned short*)malloc(sizeof(unsigned short));      
	fh->offset = (unsigned int*)malloc(sizeof(unsigned int));
	ih->headersize = (unsigned int*)malloc(sizeof(unsigned int));     
	ih->width = (unsigned int*)malloc(sizeof(unsigned int));             
	ih->height = (unsigned int*)malloc(sizeof(unsigned int));         
	ih->planes= (unsigned short*)malloc(sizeof(unsigned short));                
	ih->bpp = (unsigned short*)malloc(sizeof(unsigned short));           
	ih->compress = (unsigned int*)malloc(sizeof(unsigned int));        
	ih->imgsize = (unsigned int*)malloc(sizeof(unsigned int));    
	ih->bpmx = (unsigned int*)malloc(sizeof(unsigned int));               
	ih->bpmy = (unsigned int*)malloc(sizeof(unsigned int));                
	ih->colors = (unsigned int*)malloc(sizeof(unsigned int));          
	ih->imxtcolors = (unsigned int*)malloc(sizeof(unsigned int));    
}


// Funcion: Se encarga de convertir valores del rgb de la imagen en gris segun la escala de grises dada
// Entrada: Imagen leida en chars y estructura InfoHeader
// Salida: imagen convertida a escala de grises

void *gris(void* contenido){
	img* contenidoImagen = (img*)contenido;
	unsigned int x, y, r, g ,b, gris;

    for (int i = 0; i < contenidoImagen->info->imgsize[0]; i+=4){
      	b=(contenidoImagen->imgdata[i]);
      	g=(contenidoImagen->imgdata[i+1]);
      	r=(contenidoImagen->imgdata[i+2]);
      	gris = r*0.3+g*0.59+b*0.11;
      	contenidoImagen->imgdata[i] = gris;
      	contenidoImagen->imgdata[i+1] = gris;
      	contenidoImagen->imgdata[i+2] = gris;
      	contenidoImagen->imgdata[i+3] = 255;
	}
	contenido = (void*)contenidoImagen->imgdata;
	pthread_barrier_wait(&mybarrier);
	return NULL;
}

// Funcion: Se encarga de convertir valores de grises de la imagen en blanco y negro segun umbral de binarizacion
// Entrada: Imagen en escala de grises y umbral de binarizacion
// Salida: imagen binarizada
void *binarizacion(void* contenido){
	img* contenidoImagen = (img*)contenido;
	
	for (int i = 0; i < contenidoImagen->info->imgsize[0]; i+=4){
		if(contenidoImagen->imgdata[i] > contenidoImagen->binarizacion[0])
			contenidoImagen->imgdata[i] = 255;
		else{
			contenidoImagen->imgdata[i] = 0;
		}
		if(contenidoImagen->imgdata[i+1] > contenidoImagen->binarizacion[0])
			contenidoImagen->imgdata[i+1] = 255;
		else{
			contenidoImagen->imgdata[i+1] = 0;
		}
		if(contenidoImagen->imgdata[i+2] > contenidoImagen->binarizacion[0])
			contenidoImagen->imgdata[i+2] = 255;
		else{
			contenidoImagen->imgdata[i+2] = 0;
		}
	}
	contenido = (void*)contenidoImagen->imgdata;
	pthread_barrier_wait(&mybarrier);
	return NULL;
}


// Funcion: Se encarga de contar pixeles blancos y negros de la imagen y calcular % de negro de la imagen, decidiendo si pasa el uimbral de clasificacion
// Entrada: Imagen binarizada y uimbral de clasificacion
// Salida: resultado uimbral de clasificacion
void *clasificacion(void* contenido){
	img* contenidoImagen = (img*)contenido;

	//Seccion critica
	pthread_mutex_lock(&lock);
	for (int i = 0; i < contenidoImagen->info->imgsize[0]; i+=4){
		if(contenidoImagen->imgdata[i] == 255){
			blanco++;
		}
		else if(contenidoImagen->imgdata[i] == 0){
			negro++;
		}
		if(contenidoImagen->imgdata[i+1] == 255){
			blanco++;
		}
		else if(contenidoImagen->imgdata[i+1] == 0){
			negro++;
		}
		if(contenidoImagen->imgdata[i+2] == 255){
			blanco++;
		}
		else if(contenidoImagen->imgdata[i+2] == 0){
			negro++;
		}
	}
	porcentaje = (negro / (blanco + negro))*100;
	pthread_mutex_unlock(&lock);
	
	contenido = (void*)contenidoImagen->imgdata;
	pthread_barrier_wait(&mybarrier);
	return NULL;
}

// Funcion: Se encarga de escribir la imagen binarizada
// Entrada: Imagen binarizada, numerod de imagen y cabeceras
// Salida: Imagen en formato .bmp
void *escribir(bmpInfoHeader* ih, bmpFileHeader* fh, unsigned char* imagen, int nImagen){
	int escribir, numbytes, x, y, i;
	unsigned char* basura = (unsigned char*)malloc(sizeof(unsigned char));;
	char* bm = "BM";
	char* nSalida = (char*)malloc(sizeof(char)*20);
	sprintf(nSalida, "salida_%d.bmp",nImagen);

	escribir = open(nSalida, O_CREAT|O_WRONLY, S_IRWXU);
	
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
	for (i = 0; i < ih->imgsize[0]; ++i){
		basura[0] = imagen[i];
		write(escribir, basura, sizeof(unsigned char));
	}
	
	close(escribir);
	return NULL;
}

#endif