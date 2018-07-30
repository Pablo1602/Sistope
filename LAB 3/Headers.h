#ifndef HEADERS_H
#define HEADERS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <pthread.h>
#include <fcntl.h>
#include <ctype.h>


typedef struct bmpFileHeader
{
  unsigned int* size;        
  unsigned short* resv1;     
  unsigned short* resv2;     
  unsigned int* offset;      
} bmpFileHeader;

typedef struct bmpInfoHeader
{
  unsigned int* headersize;   
  unsigned int* width;        
  unsigned int* height;      
  unsigned short* planes;    
  unsigned short* bpp;       
  unsigned int* compress;    
  unsigned int* imgsize;     
  unsigned int* bpmx;             
  unsigned int* bpmy;              
  unsigned int* colors;              
  unsigned int* imxtcolors;      
} bmpInfoHeader;

typedef struct imagenCompleta
{
  bmpInfoHeader* info;
  bmpFileHeader* file;
  unsigned char* imgdata;
  int* numero;
  int* clasificacion;
  int* binarizacion;
  int* hebra;
  int* nhebra;
}img;

pthread_mutex_t lock;
pthread_barrier_t mybarrier;
float negro, blanco, porcentaje;

void datapath(int cantidadImg,int numeroHebras, int uBinarizacion, int uClasificacion, int mostrar);
void iniciador(bmpFileHeader* fh, bmpInfoHeader* ih);
img* iniciadorImagen(img* contenido, int* num, int* binarizacion, int* clasificacion, int* nhebra);
void *lectura(void* contenido);
void *gris(void* contenido);
void *binarizacion(void* contenido);
void *clasificacion(void* contenido);
void *escribir(bmpInfoHeader* ih, bmpFileHeader* fh, unsigned char* imagen, int nImagen);
#endif  