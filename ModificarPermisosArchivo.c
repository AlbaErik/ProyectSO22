#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char* argv[]){

	char* archivo = argv[1];

	long int i = strtol(argv[2], 0, 8);
	int res = chmod(archivo, i);

	if(res < 0)
		fprintf(stderr, "\nERROR Archivo Invalido\n");
	else
		printf("\nLos permisos del archivo fueron modificados\n");

	return 0;
}
