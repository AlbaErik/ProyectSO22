#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char* argv[]){

	char* nombre = argv[1];
	
	int res = mkdir(nombre, 0777);
	
	if(res == 0)
		printf("\nSe creo el directorio '%s' satisfactoriamente\n", nombre);
	else
		printf("No se pudo crear el directorio\n");

	return 0;
}
