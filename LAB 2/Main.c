#include "Headers.h"
#include "Funciones.h"

int main(int argc, char *const argv[]){

  //int cantidadImg, uBnarizar, uCasifica, mostrar;
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

	char* argexec[] = {"./Datapath",cantidadImg, uBnarizar, uCasifica, mostrar, (char*)NULL};

	pid_t pid;
	int status;
	switch(pid = fork()){
		case 0:
			printf("Soy Hijo\n");
			execValor = execvp(argexec[0],argexec);
			printf("Error en ejecucion de programa\n");
			break;
		case -1:
			printf("error en fork\n");
		 	break;
		default:
			waitpid(pid,&status,0);
			printf("soy padre\n");
			break;
	}
	//datapath(cantidadImg, uBnarizar, uCasifica, mostrar);
	return 0;
}

