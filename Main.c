#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

//Maximo Largo Linea 50
//Formato archivo : sin salto de linea al final del archivo

//Structura guarda registros
typedef struct registros{
	char** nombreReg;
	int* registros;
	int** memoria;
}reg;


int main(int argc, char const *argv[]){

  int cantidadImg, uBnarizar, uCasifica, mostrar;
  
    
  while ((c = getopt (argc, argv, "c:u:n:b:")) != -1){
	    switch (c){
	      	case 'c':
	        	sscanf(optarg, "%d", &cantidadImg);
	        	break;
	      	case 'u':
	        	sscanf(optarg, "%d", &uBnarizar);
	        	break;
	      	case 'n':
		    	sscanf(optarg, "%d", &uCasifica);
	        	break;
	   	   	case 'b':
		      	mostrar = 1;
	        	break;
	      	case '?':
		        if (optopt == 'c' || optopt == 'u' || optopt == 'n' || optopt == 'b')
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
  exit(0);
  
	//Ingreso del codigo
	//printf("Ingrese el nombre del Archivo que contiene el codigo del programa (Incluyendo la extencion de este)\n");
	//char* nombreArchivo = (char*)malloc(sizeof(char)*20);
	//scanf("%s",nombreArchivo);
	//strcpy(nombreArchivo, "mipsEjemplo1.asm");
	archivoCodigo = fopen("mipsEjemplo2.asm", "rb");
	if (archivoCodigo==NULL){
		printf("El Archivo de lectura no existe o no se tiene permiso de acceso al archivo\n");
		return 0;
	}

	//Ingreso lineas de control
	//printf("Ingrese el nombre del archivo con las lineas de control correspondientes (Incluyendo la extencion de este)\n");
	//strcpy(nombreArchivo, "lineasControl1.txt");
	//scanf("%s",nombreArchivo);
	archivoLineas = fopen("lineasControl2.txt", "rb");
	if (archivoLineas==NULL){
		printf("El Archivo no existe o no se tiene permiso de acceso al archivo\n");
		return 0;
	}
	char* basura = (char*)malloc(sizeof(char)*100);
	fscanf(archivoLineas, "%s" , basura);
	fscanf(archivoLineas, "%s" , basura);
	fscanf(archivoLineas, "%s" , basura);
	fscanf(archivoLineas, "%s" , basura);
	fscanf(archivoLineas, "%s" , basura);
	fscanf(archivoLineas, "%s" , basura);
	fscanf(archivoLineas, "%s" , basura);
	fscanf(archivoLineas, "%s" , basura);
	fscanf(archivoLineas, "%s" , basura);
	

	//printf("Ingrese el nombre del Archivo de salida (Incluyendo la extencion de este)\n");
	//strcpy(nombreArchivo, "Salida.txt");
	//scanf("%s",nombreArchivo);
	
	archivoSalida = fopen("Salida.txt","wb");
	fprintf(archivoSalida, "Estado		RegDst Jump Branch MemRead MemToReg ALUOp MemWrite ALUSrc RegWrite\n");
	
	char** Funciones = (char**)malloc(sizeof(char*)* 15);
	for (i = 0; i < 15; ++i){
		Funciones[i] = (char*)malloc (sizeof(char) * 5);
	}
	
	Funciones = inicializaFunciones(Funciones);


	reg* registros = (reg*)malloc(sizeof(reg));
	registros = inicializarReg();

	char** codigo = (char**)malloc(sizeof(char*)* MAX);
	int** lineasDeControl =(int**)malloc(sizeof(int*)*MAX);
	int **resultados = (int**)malloc(sizeof(int*)*MAX);
	for (i = 0; i < MAX; ++i){
		resultados[i] = (int*)malloc(sizeof(int)*9);
		lineasDeControl[i] = (int*)malloc(sizeof(int)*9);
		for (j = 0; j < 9; ++j){
			resultados[i][j] = 0;
			lineasDeControl[i][j] = 0;
		}
		codigo[i]=(char*)malloc(sizeof(char)*50);
	}

	int cuentaLineas = 0;
	char* Linea = (char*)malloc(sizeof(char)*50);
	char* Fun = (char*)malloc(sizeof(char)*50);




	while(feof(archivoCodigo)==0){
		fgets(codigo[cuentaLineas], 50, archivoCodigo);
		strcpy(Linea ,codigo[cuentaLineas]);
		if (strcmp( Linea ,"") == 0 || strcmp(Linea,"\n")== 0 )
		{
			continue;
		}
		Fun = strtok(Linea," ");
		Fun = strtok(Fun,":");
		numFn = buscarFuncion(Funciones, Fun);
		if (numFn != -1){
			fscanf(archivoLineas, "%d " , &lineasDeControl[cuentaLineas][0]);
			fscanf(archivoLineas, "%d " , &lineasDeControl[cuentaLineas][1]);
			fscanf(archivoLineas, "%d " , &lineasDeControl[cuentaLineas][2]);
			fscanf(archivoLineas, "%d " , &lineasDeControl[cuentaLineas][3]);
			fscanf(archivoLineas, "%d " , &lineasDeControl[cuentaLineas][4]);
			fscanf(archivoLineas, "%d " , &lineasDeControl[cuentaLineas][5]);
			fscanf(archivoLineas, "%d " , &lineasDeControl[cuentaLineas][6]);
			fscanf(archivoLineas, "%d " , &lineasDeControl[cuentaLineas][7]);
			fscanf(archivoLineas, "%d " , &lineasDeControl[cuentaLineas][8]);
		}
		cuentaLineas = cuentaLineas + 1;
	}
	//RegDst Jump Branch MemRead MemToReg ALUOp MemWrite ALUSrc RegWrite
	int lcR[9] =  	{1,0,0,0,0,10,0,0,1};
	int lclw[9] = 	{0,0,0,1,1,00,0,1,1};
	int lcsw[9] = 	{2,0,0,0,2,00,1,1,0};
	int lcbeq[9]= 	{2,0,1,0,2,01,0,0,0};
	int lcj[9] =  	{2,1,0,0,2,2,0,0,0};
	int lcsubi[9] = {0,0,0,0,0,01,0,1,1};
	int lcaddi[9] = {0,0,0,0,0,00,0,1,1};

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////Ejecucion////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	return 0;
}
