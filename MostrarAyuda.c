#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]){

	printf("\nLista de comandos:\n");
	printf(" <CrearDirectorio> 'nombre': Crea un directorio con el nombre del parametro\n");
	printf(" <CrearArchivo> 'nombre': Crea un archivo de texto con el nombre del parametro\n");
	printf(" <MostrarArchivo> 'nombre': Muestra el contenido de 'nombre'\n");
	printf(" <ListarDirectorio> 'nombre': Lista el contenido del directorio correspondiente al nombre del parametro\n");
	printf(" <EliminarDirectorio> 'nombre': Elimina el directorio correspondiente al nombre del parametro\n");
	printf(" <ModificarPermisosArchivo> 'nombre' 'permisos': Modifica los permisos de 'nombre' con los nuevos permisos 'permisos'\n");
	printf(" <MostrarAyuda> : Muestra el texto con la ayuda\n\n");
	printf("Se debe especificar la ruta completa para trabajar con archivos\n");
	printf("\n");

	return 0;
}
