#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

#define KEY ((key_t) (8589))
#define sizeMsg sizeof(msg)-sizeof(long)
#define CANT_PROCESOS_NORTE 3
#define CANT_PROCESOS_SUR 3
#define ST 10
#define LIMITE_DE_RAFAGA 6


pthread_mutex_t mutexNorte, mutexSur;
/*
 * Los autos del sur son de tipo 1, los del norte de tipo 2, el puente de tipo 3, el permiso del oficial para el norte tipo 4,
 * el permiso del oficial para el Sur tipo 5, tipo 6 cont Oficial del Norte, tipo 7 cont Oficial del Sur
 */
typedef struct mensaje{
	long tipo;
	char m;
} msg;

void *oficialDelNorte(){	
}
void *oficialDelSur(){
}

void autosNorte(int qId){
	qId=msgget(KEY, 0666);
	msg msjRecibido;
	msg msjEnviado;
	while(1){
		pthread_mutex_lock(&mutexNorte);
		printf("Auto llego a la entrada Norte.\n");
		fflush(stdout);
		
		msjEnviado.tipo= 2,
		msjEnviado.m='.';
		
		if(msgrcv(qId, &msjRecibido, sizeMsg, 2, IPC_NOWAIT)==-1){
			msgrcv(qId, &msjRecibido, sizeMsg, 3, 0);
			printf("Puente vacio. ");
			fflush(stdout);
		}
		else{
			msgsnd(qId, &msjEnviado, sizeMsg, 0);//Recupero el del try wait
		}
		msgsnd(qId, &msjEnviado, sizeMsg, 0);
		pthread_mutex_unlock(&mutexNorte);
		
		printf("Arranca a cruzar auto del Norte.\n");
		fflush(stdout);
		sleep(ST);
		printf("Auto Norte saliendo...\n");
		fflush(stdout);
		
		pthread_mutex_lock(&mutexNorte);
		msgrcv(qId, &msjRecibido, sizeMsg, 2,0);
		if(msgrcv(qId, &msjRecibido, sizeMsg, 2, IPC_NOWAIT)== -1){
			printf("El norte libera el puente.\n");
			fflush(stdout);
			
			msjEnviado.tipo=3,
			msjEnviado.m='.';
			
			msgsnd(qId, &msjEnviado, sizeMsg, 0);
		}
		else{
			msjEnviado.tipo=2,
			msjEnviado.m='.';
			msgsnd(qId, &msjEnviado, sizeMsg, 0);
		}
		pthread_mutex_unlock(&mutexNorte);
	}
}

void autosSur(int qId){
	qId=msgget(KEY, 0666);
	msg msjRecibido;
	msg msjEnviado;
	while(1){
		pthread_mutex_lock(&mutexSur);
		printf("Auto llego a la entrada Sur.\n");
		fflush(stdout);
		
		msjEnviado.tipo= 1,
		msjEnviado.m='.';
		
		if(msgrcv(qId, &msjRecibido, sizeMsg, 1, IPC_NOWAIT)==-1){
			msgrcv(qId, &msjRecibido, sizeMsg, 3, 0);
			printf("Puente vacio. ");
			fflush(stdout);
		}
		else{
			msgsnd(qId, &msjEnviado, sizeMsg, 0);//Recupero el del trywait
		}
		msgsnd(qId, &msjEnviado, sizeMsg, 0);
		pthread_mutex_unlock(&mutexSur);
		
		printf("Arranca a cruzar auto del Sur.\n");
		fflush(stdout);
		sleep(ST);
		printf("Auto Sur saliendo...\n");
		fflush(stdout);
		
		pthread_mutex_lock(&mutexSur);
		msgrcv(qId, &msjRecibido, sizeMsg, 1,0);
		if(msgrcv(qId, &msjRecibido, sizeMsg, 1, IPC_NOWAIT)== -1){
			printf("El Sur libera el puente.\n");
			fflush(stdout);
			
			msjEnviado.tipo=3,
			msjEnviado.m='.';
			
			msgsnd(qId, &msjEnviado, sizeMsg, 0);
		}
		else{
			msjEnviado.tipo=1,
			msjEnviado.m='.';
			msgsnd(qId, &msjEnviado, sizeMsg, 0);
		}
		pthread_mutex_unlock(&mutexSur);
	}
}

void crearProcesos(){
	int queueId= msgget(KEY,IPC_CREAT|0666);
	int pid;
	//Inicializar punete
	msg msjEnviado;
	msjEnviado.tipo=3,
	msjEnviado.m='.';
	msgsnd(queueId, &msjEnviado, sizeMsg, 0);
	
	for(int i=0; i<CANT_PROCESOS_NORTE; i++){
		pid= fork();
		if(pid>0){
			autosNorte(queueId);
			
			exit(0);
		}
	}
	
	for(int i=0;i<CANT_PROCESOS_SUR; i++){
		pid= fork();
		if(pid>0){
			autosSur(queueId);
			
			exit(0);
		}
	}
	
	for(int i=0; i<CANT_PROCESOS_NORTE+CANT_PROCESOS_SUR; i++){
		wait(NULL);
	}
}



int main(){
	
	crearProcesos();
	
}
