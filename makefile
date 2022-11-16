compile: CrearArchivo.c CrearDirectorio.c EliminarDirectorio.c ListarDirectorio.c Minishell.c ModificarPermisosArchivo.c MostrarArchivo.c MostrarAyuda.c SalirShell.c
	gcc CrearArchivo.c -c -Wall
	gcc CrearDirectorio.c -c -Wall
	gcc EliminarDirectorio.c -c -Wall
	gcc ListarDirectorio.c -c -Wall
	gcc ModificarPermisosArchivo.c -c -Wall
	gcc MostrarArchivo.c -c -Wall
	gcc MostrarAyuda.c -c -Wall
	gcc SalirShell.c -c -Wall
	gcc CrearArchivo.o CrearDirectorio.o EliminarDirectorio.o ListarDirectorio.o ModificarPermisosArchivo.o MostrarArchivo.o MostrarAyuda.o SalirShell.o Minishell.c -o Minishell -Wall