#ifndef HEADERS_H
#define HEADERS_H

#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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

unsigned char* lecturaPipe(int pipe, bmpFileHeader* fh, bmpInfoHeader* ih);
void escribirPipe(int pipe, bmpInfoHeader* ih, bmpFileHeader* fh, unsigned char* imagen);
void datapath(int cantidadImg, int uBinarizacion, int uClasificacion, int mostrar);
void iniciador(bmpFileHeader* fh, bmpInfoHeader* ih);
unsigned char* lectura(char* nombre,bmpFileHeader* fh, bmpInfoHeader* ih);
void gris(unsigned char* imagen, bmpInfoHeader* info);
void escribir(bmpInfoHeader* ih, bmpFileHeader* fh, unsigned char* imagen, int nImagen);
void binarizacion(int umbral, unsigned char* imagen, bmpInfoHeader* ih);
void clasificacion(int umbral, unsigned char* imagen, bmpInfoHeader* ih, int mostrar);

#endif