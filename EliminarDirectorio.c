#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <dirent.h>
#include <sys/sysmacros.h>

int elimDirectorio(char* nombre);

int main(int argc, char* argv[]){

	char* directorio = argv[1];
	int resultado = elimDirectorio(directorio);
	if(resultado == 0)
		printf("\nSe elimino el directorio\n");
	else
		fprintf(stderr, "\nERROR No se pudo eliminar el directorio ingresado\n");

	return 0;
}


int elimDirectorio(char* nombre){

	size_t sizeDireccion = strlen(nombre);
	DIR *directorio = opendir(nombre);
	struct dirent *dir;
	char *buffer;
	size_t tamanio;

	int resultado = -1;

	if(directorio != NULL){
		resultado = 0;
		while(resultado == 0 && ((dir = readdir(directorio)) != NULL)){
			
			//No se itera en los directorios ".." y "."
			if(strcmp(dir->d_name, "..") != 0 && strcmp(dir->d_name, ".") != 0) {
				
				tamanio = sizeDireccion + strlen(dir->d_name) + 2;
				buffer = malloc(tamanio);

				if(buffer != 0){

					struct stat statbuffer;

					//Guarda en el buffer la ruta del archivo
					snprintf(buffer, tamanio, "%s/%s", nombre, dir->d_name);
					resultado = stat(buffer, &statbuffer);

					if(resultado == 0){
						//Revisa si el contenido es un directorio
						if(S_ISDIR(statbuffer.st_mode))
							resultado = elimDirectorio(buffer);
						else
							resultado = unlink(buffer);
					}

					free(buffer);
				}
			}
		}
		closedir(directorio);
	}

	if(resultado == 0)
		if(rmdir(nombre) < 0){
			perror("Error al eliminar el directorio");
	}

	return resultado;
}
