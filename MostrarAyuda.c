#include <stdlib.h>
#include <stdio.h>
#include "MostrarAyuda.h"

int main(int argc, char* argv[]){

	printf("\nCOMANDOS:\n");
	printf("1 - CrearDirectorio 'nombre': Crea un directorio con el nombre del parametro\n");
	printf("2 - EliminarDirectorio 'nombre': Elimina el directorio correspondiente al nombre del parametro\n");
	printf("3 - CrearArchivo 'nombre': Crea un archivo de texto con el nombre del parametro\n");
	printf("4 - ListarDirectorio 'nombre': Lista el contenido del directorio correspondiente al nombre del parametro\n");
	printf("5 - MostrarArchivo 'nombre.txt': Muestra el contenido del archivo correspondiente al nombre del parametro\n");
	printf("6 - ModificarPermisosArchivo 'nombre': Modifica los permisos del archivo correspondiente al nombre del parametro\n");
	printf("7 - MostrarAyuda: Muestra el texto con la ayuda\n");
	printf("8 - SalirShell: Finaliza la ejecucion\n\n");
	printf("IMPORTANTE: Es debe especificar la ruta completa para trabajar con archivos\n");
	printf("EJEMPLO: Para eliminar un directorio se debe realizar la siguiente llamada: EliminarDirectorio /home/user/Desktop/'nombre del directorio a eliminar'\n");
	printf("Los argumentos deberan estar separados por un espacio\n");
	printf("\n");

	return 0;
}
