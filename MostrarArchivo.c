#include <stdlib.h>
#include <stdio.h>
#include "MostrarArchivo.h"

int main(int argc, char* argv[]){
	
	FILE *archivo = fopen(argv[1], "r");
	int c;

	if(archivo == NULL)
		fprintf(stderr, "\nEl archivo no pudo abrirse\n");
	else{

		printf("\n");
		while((c = fgetc(archivo)) != EOF)
			printf("%c", c);
		printf("\n");
	}

	fclose(archivo);

	return 0;
}
