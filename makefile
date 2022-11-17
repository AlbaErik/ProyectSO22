plantaRecicladoPipes : PlantaDeRecicladoConPipes.c
	@gcc PlantaDeRecicladoConPipes.c -o plantaRecicladoPipes

plantaRecicladoColas : PlantaDeRecicladoConCola.c
	@gcc PlantaDeRecicladoConCola.c -o plantaRecicladoColas
	
secuenciaHilos : sincronizacionA.c
	@gcc sincronizacionA.c -o secuenciaHilos -lpthread

secuenciaPipes : SecuenciaConPipes.c
	@gcc SecuenciaConPipes.c -o secuenciaPipes -lpthread
	
puenteHilos : PuenteDeUnaSolaManoI.c
	@gcc PuenteDeUnaSolaManoI.c -o puenteHilos -lpthread

puenteColas : PuenteDeUnaSolaManoIII.c
	@gcc PuenteDeUnaSolaManoIII.c -o puenteColas -lpthread

miniShell : Minishell.c CrearArchivo CrearDirectorio EliminarDirectorio ListarDirectorio ModificarPermisosArchivo MostrarArchivo MostrarAyuda
	@gcc Minishell.c -o miniShell

CrearArchivo : CrearArchivo.c
	@gcc CrearArchivo.c -o CrearArchivo
	
CrearDirectorio : CrearDirectorio.c
	@gcc CrearDirectorio.c -o CrearDirectorio
	
EliminarDirectorio : EliminarDirectorio.c
	@gcc EliminarDirectorio.c -o EliminarDirectorio
	
ListarDirectorio : ListarDirectorio.c
	@gcc ListarDirectorio.c -o ListarDirectorio

ModificarPermisosArchivo : ModificarPermisosArchivo.c
	@gcc ModificarPermisosArchivo.c -o ModificarPermisosArchivo

MostrarArchivo : MostrarArchivo.c
	@gcc MostrarArchivo.c -o MostrarArchivo
	
MostrarAyuda : MostrarAyuda.c
	@gcc MostrarAyuda.c -o MostrarAyuda
