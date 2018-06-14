#ifndef FUNCIONES_H
#define FUNCIONES_H
#include "Headers.h"



// Funcion: Se encarga de la ejecucion del "datapath" completo, llamando a las demas imagenes para que realizen su función
// Entrada: cantidad de imagenes, umbral de binarizacion, umbral de clasificacion y instruccion si se debe moistrar resultado por pantalla o no
// Salida: Ejecucción del Programa

void datapath(int cantidadImg,int numeroHebras, int uBinarizacion, int uClasificacion, int mostrar){
	int i, j;
	unsigned char* imgdata;
	bmpFileHeader* fh =(bmpFileHeader*)malloc(sizeof(bmpFileHeader));
	bmpInfoHeader* ih =(bmpInfoHeader*)malloc(sizeof(bmpInfoHeader));
	char* nImagen = (char*)malloc(sizeof(char)*10);
	char* numero = (char*)malloc(sizeof(char)*5);
	iniciador(fh, ih);
	if (mostrar == 1){
		printf("| 	Numero Imagen 	| 	Nearly black 	|\n-------------------------------------------------\n");
	}

	pthread_barrier_t mybarrier;
	pthread_t* hebras;
	hebras = (pthread_t*)malloc(sizeof(pthread_t)*numeroHebras);


	for (i = 1; i <= cantidadImg; ++i){

		pthread_barrier_init(&mybarrier, NULL, numeroHebras+1);
		sprintf(nImagen, "imagen_%d.bmp",i);
		// Hebra 1 tiene que leer la imagen
		pthread_create(&hebras[0], NULL, lectura, (void*)&imgdata, (void*)&nImagen , (void*)&fh, (void*)&ih,)
		//n Hebras tienen que pasar a gris imagen y binarizar.
		
		//esperar hebras
		pthread_barrier_wait(&mybarrier);
		gris(imgdata, ih);
		
		//esperar hebras
		pthread_barrier_wait(&mybarrier);

		binarizacion(uBinarizacion, imgdata, ih);
		
		//esperar hebras
		pthread_barrier_wait(&mybarrier);
		
		//hebras deben contar los negros que existen en la imagen luego de binarizarla 
		if (mostrar == 1){
		printf("| 	%s	|",nImagen);
		}
		clasificacion(uClasificacion, imgdata, ih, mostrar);
		
		//esperar hebras
		pthread_barrier_wait(&mybarrier);

		// esto debe hacerlo main, no proceso
		escribir(ih, fh, imgdata, i);
 		for (j=0; j<numeroHebras; j++) {
    		pthread_join(hebras[j], NULL);
  		}
		pthread_barrier_destroy(&mybarrier);
	}
	
}

// Funcion: Se encarga de leer los archivos de imagen y guardarlo en variables correspondientes
// Entrada: Nombre de archivo a leer, puntero estructura FileHeader y InfoHeader vacios
// Salida: puntero estructura FileHeader y InfoHeader vacios y imagen leida
void lectura(void* imgdata, void* nombreEntrada,bmpFileHeader* fh, bmpInfoHeader* ih){
	char** img = imgdata;
	char* nombre = nombreEntrada;
	// agregar casteos
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

	imgdata = (unsigned char*)malloc(sizeof(unsigned char)*ih->imgsize[0]);   
	unsigned char* basura = (unsigned char*)malloc(sizeof(unsigned char));;

	lseek(imagen,fh->offset[0],SEEK_SET);
	for (int i = 0; i < ih->imgsize[0]; ++i){
		read(imagen, basura, sizeof(unsigned char));
		imgdata[i] = basura[0];
	}
  	close(imagen);
  	return;
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

void gris(unsigned char* imagen, bmpInfoHeader* ih){
	unsigned int x, y, r, g ,b, gris;

    for (int i = 0; i < ih->imgsize[0]; i+=4){
      	b=(imagen[i]);
      	g=(imagen[i+1]);
      	r=(imagen[i+2]);
      	gris = r*0.3+g*0.59+b*0.11;
      	imagen[i] = gris;
      	imagen[i+1] = gris;
      	imagen[i+2] = gris;
      	imagen[i+3] = 255;
	}
  	
}

// Funcion: Se encarga de convertir valores de grises de la imagen en blanco y negro segun umbral de binarizacion
// Entrada: Imagen en escala de grises y umbral de binarizacion
// Salida: imagen binarizada
void binarizacion(int umbral, unsigned char* imagen, bmpInfoHeader* ih){
	for (int i = 0; i < ih->imgsize[0]; i+=4){
		if(imagen[i] > umbral)
			imagen[i] = 255;
		else{
			imagen[i] = 0;
		}
		if(imagen[i+1] > umbral)
			imagen[i+1] = 255;
		else{
			imagen[i+1] = 0;
		}
		if(imagen[i+2] > umbral)
			imagen[i+2] = 255;
		else{
			imagen[i+2] = 0;
		}
	}
}


// Funcion: Se encarga de contar pixeles blancos y negros de la imagen y calcular % de negro de la imagen, decidiendo si pasa el uimbral de clasificacion
// Entrada: Imagen binarizada y uimbral de clasificacion
// Salida: resultado uimbral de clasificacion
void clasificacion(int umbral, unsigned char* imagen, bmpInfoHeader* ih, int mostrar){
	float blanco = 0, negro = 0, porcentaje = 0;
	for (int i = 0; i < ih->imgsize[0]; i+=4){
		if(imagen[i] == 255){
			blanco++;
		}
		else if(imagen[i] == 0){
			negro++;
		}
		if(imagen[i+1] == 255){
			blanco++;
		}
		else if(imagen[i+1] == 0){
			negro++;
		}
		if(imagen[i+2] == 255){
			blanco++;
		}
		else if(imagen[i+2] == 0){
			negro++;
		}
	}
	porcentaje = (negro / (blanco + negro))*100;
	
	if(porcentaje >= umbral){
		if (mostrar == 1){
			printf(" 	Yes		|\n");
		}
	}
	else{
		if (mostrar == 1){
			printf(" 	No		|\n");
		}
	}
	
}

// Funcion: Se encarga de escribir la imagen binarizada
// Entrada: Imagen binarizada, numerod de imagen y cabeceras
// Salida: Imagen en formato .bmp
void escribir(bmpInfoHeader* ih, bmpFileHeader* fh, unsigned char* imagen, int nImagen){
	int escribir, numbytes, x, y;
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
	for (int i = 0; i < ih->imgsize[0]; ++i){
		basura[0] = imagen[i];
		write(escribir, basura, sizeof(unsigned char));
	}
	
	close(escribir);
}

#endif