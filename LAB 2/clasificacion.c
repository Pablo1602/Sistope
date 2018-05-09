#include "Headers.h"
#include "Funciones.h"

int main(int argc, char const *argv[])
{
	unsigned char* imgdata;
	int uClasificacion =  atoi(argv[2]);
	bmpFileHeader* fh =(bmpFileHeader*)malloc(sizeof(bmpFileHeader));
	bmpInfoHeader* ih =(bmpInfoHeader*)malloc(sizeof(bmpInfoHeader));
	int status,p[2];
	iniciador(fh, ih);
	imgdata = lecturaPipe(0, nImagen,fh,ih);
	clasificacion(uClasificacion,nImagen,ih,argv[3],argv[4]);

	pid_t pid;
	pipe(p);
	switch(pid = fork()){
		case 0:
			close(p[1]);
			dup2(fd[0],STDIN_FILENO);
			execValor = execvp("./escritura",argexec);
			printf("Error en exec\n");
			break;
		case -1:
			printf("Error en fork en imagen %d\n",i);
		 	exit(0);
		default:
			close(p[0]);
			dup2(fd[1],STDOUT_FILENO);
			escribirPipe(1,ih,fh,imgdata);
			//todoo
			break;
	}
	waitpid(pid,&status,0);
	return 0;
}