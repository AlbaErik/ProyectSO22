#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/wait.h>

#define TAMANIOBUFFER 1024
#define FALSE 0
#define TRUE 1

char cwd[PATH_MAX];

char* obtenerComando(){

	int indice = 0;
	int tamanioBuffer = TAMANIOBUFFER;
	char* buffer = malloc(tamanioBuffer * sizeof(char));
	int caracter;
	int seguir = TRUE;
	int argc = 0;

	while(seguir){
		caracter = getchar();
		if((caracter == EOF) || (caracter == '\n')){
			buffer[indice++] = '\0';
			seguir = FALSE;
			argc++;
		}else{
			buffer[indice++] = caracter;
			if(caracter == ' ')
				argc++;
		}

		//Incrementa tamaño buffer
		if(indice >= tamanioBuffer){
			buffer = realloc(buffer, tamanioBuffer*2);
			if(!buffer){
				printf("\nERROR en el buffer\n");
				exit(EXIT_FAILURE);
			}
		}
	}

	if(argc>3)
		buffer = NULL;

	return buffer;
}

void prompt(){
	printf("%s $ ", getcwd(cwd, sizeof(cwd)) );
}

int main(){

	char *comando = "";
	int continuar = TRUE;
	
	prompt();

	while(continuar){
		//Obtiene los argumentos de consola y los almacena en el comando
		comando = obtenerComando();
		
		if((comando != NULL) && (comando[0] != '\n')){

			//Almacena los argumentos en un arreglo
			char *argv[3];
			int ind = 0;
			
			argv[ind] = strtok(comando, " ");
			ind++;
			argv[ind] = strtok(NULL, " ");			
			ind++;
			argv[2] = strtok(NULL, " ");

			int pid = fork();
			if(pid > 0){
				wait(NULL);
			}else 
				if(pid == 0){
					execv(argv[0], argv);
					printf("Error ingrese un comando valido - para obtener ayuda ingrese 'MostarAyuda' \n");
				}else 
					printf("Error al crear el proceso");
		}else{
			printf("\nIntroduzca el nombre de una funcion y su parametro correspondiente\n");
			printf("\nPara mas informacion ejecute MostrarAyuda\n");
		}

		prompt();
	}

	return 0;
}
