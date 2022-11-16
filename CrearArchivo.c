#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){

	char* nombre = malloc(sizeof(FILE));

	FILE *file;
	file = fopen(argv[1], "w");

	if(file != NULL)
		printf("\nEl archivo '%s' se creo con exito\n", argv[1]);
	else
		fprintf(stderr, "\nSe produjo un error al crear el archivo\n");

	fclose(file);
	free(nombre);

	return 0;
}
