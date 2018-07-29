#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <pthread.h>
#include <fcntl.h>
#include <ctype.h>

typedef struct dat{
    int* numero1;
    char* texto;
}ass;


typedef struct dato{
    ass* prueba;

}datos;

void* funcion1( void* arg){

    datos* datoA = (datos*)arg;
    ass* a = datoA->prueba;
    printf("el texto es %s\n", a->texto); 
    printf("el num es %d\n", a->numero1[0]); 
}

int main(int argc, char const *argv[]){

    datos* datoA = (datos*)malloc(sizeof(datos));
    datoA->prueba = (ass*)malloc(sizeof(ass));
    datoA->prueba->numero1 = (int*)malloc(sizeof(int));
    datoA->prueba->texto = (char*)malloc(sizeof(char)*10);
    pthread_barrier_t mybarrier;
    *datoA->prueba->numero1 = 20;
    datoA->prueba->texto = "HOLA";
    pthread_t hebras;

    pthread_barrier_init(&mybarrier, NULL, 1);
    pthread_create(&hebras, NULL, (void*)funcion1, (void*)datoA);
    printf("Que tal\n");
    pthread_barrier_wait(&mybarrier);
    return 0;
}
