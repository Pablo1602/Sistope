#include "Headers.h"
#include "Funciones.h"

int main(int argc, char *const argv[]){

  
	char* mostrar = (char*)malloc(sizeof(char)*10);
	strcpy(mostrar, "0");
	char*  cantidadImg = (char*)malloc(sizeof(char)*10);
	char* uBnarizar = (char*)malloc(sizeof(char)*10);
	char* uCasifica = (char*)malloc(sizeof(char)*10);
  	int c;
  	int execValor;
  	while ((c = getopt (argc, argv, "c:u:n:b")) != -1){
		switch (c){
			case 'c':
				sscanf(optarg, "%s", cantidadImg);
				break;
			case 'u':
				sscanf(optarg, "%s", uBnarizar);
				break;
			case 'n':
				sscanf(optarg, "%s", uCasifica);
				break;
			case 'b':
				strcpy(mostrar,"1");
				break;
			case '?':
				if (optopt == 'c' || optopt == 'u' || optopt == 'n')
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

	pid_t pid;
	int status,i;
	int cantImg  = atoi(cantidadImg);
	char** argexec = (char**)malloc(sizeof(char*)*6);
	for (i = 0; i < 6; ++i){
		argexec[i]= (char*)malloc(sizeof(char)*15);
	}

	for (i = 1; i <= cantImg; ++i){
		printf("INICIO %d de %d\n", i, cantImg);
		sprintf(argexec[0], "%s",cantidadImg);
		sprintf(argexec[1], "%s",uBnarizar);
		sprintf(argexec[2], "%s",uCasifica);
		sprintf(argexec[3], "%s",mostrar);
		sprintf(argexec[4], "%d",i);
		argexec[5] = (char*)NULL;

		switch(pid = fork()){
			case 0:
				//printf("Soy Hijo\n");
				execValor = execvp("./lectura",argexec);
				printf("Error en exec\n");
				break;
			case -1:
				printf("Error en fork en imagen %d\n",i);
			 	exit(0);
			default:
				break;
		}
		waitpid(pid,&status,0);
	}
	printf("Finalizacion del main\n");
	return 0;
}

