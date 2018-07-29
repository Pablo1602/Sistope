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
}img;

pthread_mutex_t lock;
float negro, blanco, porcentaje;

void datapath(int cantidadImg,int numeroHebras, int uBinarizacion, int uClasificacion, int mostrar);
void iniciador(bmpFileHeader* fh, bmpInfoHeader* ih);
// void *lectura(void* imgdata, void* nombreEntrada, void* fh, void* ih);
void *lectura(void *arg);
void *gris(void* imagen, void* ih);
void *binarizacion(void* umbral, void* imagen, void* ih);
void *clasificacion(void* imagen, void* ih);
void *escribir(bmpInfoHeader* ih, bmpFileHeader* fh, unsigned char* imagen, int nImagen);
pthread_barrier_t mybarrier;
#endif  