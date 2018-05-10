#include "Headers.h"
#include "Funciones.h"

int main(int argc, char const *argv[])
{
	//printf("Clasificacion %d\n", atoi(argv[4]));
	
	unsigned char* imgdata;
	int uClasificacion =  atoi(argv[2]);
	int mostrar = atoi(argv[3]);
	bmpFileHeader* fh =(bmpFileHeader*)malloc(sizeof(bmpFileHeader));
	bmpInfoHeader* ih =(bmpInfoHeader*)malloc(sizeof(bmpInfoHeader));
	char* nImagen = (char*)malloc(sizeof(char)*10);
	int status, p[2], execValor, i = atoi(argv[4]);
	
	sprintf(nImagen, "imagen_%d.bmp",i);
	if(atoi(argv[3]) == 1){
		printf("| 	%s	|",nImagen);
	}

	iniciador(fh, ih);
	imgdata = lecturaPipe(0,fh,ih);
	clasificacion(uClasificacion,imgdata,ih,mostrar);

	pid_t pid;
	pipe(p);

	char** argexec = (char**)malloc(sizeof(char*)*6);
	for (i = 0; i < 6; ++i){
		argexec[i]= (char*)malloc(sizeof(char)*15);
	}
	sprintf(argexec[0], "%s",argv[0]);
	sprintf(argexec[1], "%s",argv[1]);
	sprintf(argexec[2], "%s",argv[2]);
	sprintf(argexec[3], "%s",argv[3]);
	sprintf(argexec[4], "%s",argv[4]);
	argexec[5] = (char*)NULL;	

	switch(pid = fork()){
		case 0:
			close(p[1]);
			dup2(p[0],STDIN_FILENO);
			execValor = execvp("./escritura",argexec);
			printf("Error en exec\n");
			break;
		case -1:
			printf("Error en fork en imagen %d\n",atoi(argv[4]));
		 	exit(0);
		default:
			close(p[0]);
			dup2(p[1],STDOUT_FILENO);
			escribirPipe(1,ih,fh,imgdata);
			//todoo
			break;
	}
	waitpid(pid,&status,0);
	return 0;
}