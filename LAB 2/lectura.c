#include "Headers.h"
#include "Funciones.h"

int main(int argc, char const *argv[])
{
	unsigned char* imgdata;
	int nImagen    =  atoi(argv[4]);
	bmpFileHeader* fh =(bmpFileHeader*)malloc(sizeof(bmpFileHeader));
	bmpInfoHeader* ih =(bmpInfoHeader*)malloc(sizeof(bmpInfoHeader));
	int status,p[2];
	iniciador(fh, ih);
	imgdata = lectura(nImagen,fh,ih);
	pid_t pid;
	pipe(p);
	switch(pid = fork()){
		case 0:
			close(p[1]);
			dup2(fd[0],STDIN_FILENO);
			execValor = execvp("./convagris",argexec);
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