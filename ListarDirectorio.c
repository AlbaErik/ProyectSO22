#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char* argv[]){

	DIR *ruta = opendir(argv[1]);
	struct dirent *dir;
	
	if (ruta){
        while ((dir = readdir(ruta)) != NULL)
            printf("%s\n", dir->d_name);
        closedir(ruta);
    }else{
		fprintf(stderr, "\nERROR No se pudo abrir el directorio %s\n", argv[1]);
		printf("Pruebe introduciendo la ruta completa\n");
	}

	return 0;
}
