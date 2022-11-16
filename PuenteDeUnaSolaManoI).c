#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>


#define CANT_HILOS_NORTE 3
#define CANT_HILOS_SUR 3
#define ST 5



pthread_t autosNorte, autosSur;

pthread_mutex_t mutexNorte, mutexSur;

sem_t sem_autosSur, sem_autosNorte, sem_puente;

int sleepTime=0;

void randTimeSleep(){
	sleepTime= rand() % 10;
}

void *entradaDelNorte(){
	while(1){
		
		pthread_mutex_lock(&mutexNorte);
		printf("Auto llego a la entrada Norte.\n");
		fflush(stdout);
		if(sem_trywait(&sem_autosNorte) == -1){
			sem_wait(&sem_puente);
			printf("Puente vacio. ");
			fflush(stdout);
		}
		else{
			sem_post(&sem_autosNorte);
		}
		sem_post(&sem_autosNorte);
		pthread_mutex_unlock(&mutexNorte);
	
		printf("Arranca a cruzar auto del Norte.\n");
		fflush(stdout);
		sleep(ST);
		printf("Auto Norte saliendo...\n");
		fflush(stdout);
		
		pthread_mutex_lock(&mutexNorte);
		
		sem_wait(&sem_autosNorte);
		if(sem_trywait(&sem_autosNorte) == -1){
			printf("El norte libera el puente.\n");
			fflush(stdout);
			sem_post(&sem_puente);
		}
		else{
			sem_post(&sem_autosNorte);
		}
		
		pthread_mutex_unlock(&mutexNorte);
		
			
	}
	return 0;
}

void *entradaDelSur(){
	while(1){	
		
		pthread_mutex_lock(&mutexSur);
		printf("Auto llego a la entrada Sur.\n");
		fflush(stdout);
		if(sem_trywait(&sem_autosSur) == -1){
			sem_wait(&sem_puente);
			printf("Puente vacio. ");
			fflush(stdout);
		}
		else{
			sem_post(&sem_autosSur);
		}
		sem_post(&sem_autosSur);
		
		pthread_mutex_unlock(&mutexSur);
		
		printf("Arranca a cruzar auto del Sur.\n");
		fflush(stdout);
		sleep(ST);
		printf("Auto Sur saliendo...\n");
		fflush(stdout);
		
		pthread_mutex_lock(&mutexSur);
		
		sem_wait(&sem_autosSur);
		if(sem_trywait(&sem_autosSur) == -1){
			printf("El sur librea el punete.\n");
			fflush(stdout);
			sem_post(&sem_puente);
			
		}
		else{
			sem_post(&sem_autosSur);
		}
		
		pthread_mutex_unlock(&mutexSur);
		
	}
	return 0;
}

void inicializarSemaforos(){
	sem_init(&sem_autosNorte, 0, 0);
	sem_init(&sem_autosSur, 0, 0);	
	sem_init(&sem_puente, 0, 1);
	pthread_mutex_init(&mutexSur, NULL);
	pthread_mutex_init(&mutexNorte, NULL);
}
/*
 * Crea una cantidad de hilos (autosSur y autosNorte) difinida por las macros CANT_HILOS_SUR y CANT_HILOS_NORTE.
 * */
void crearHilos(){
		for(int i=0; i<CANT_HILOS_NORTE; i++){
			pthread_create(&autosNorte, NULL, *entradaDelNorte, NULL);
		}
		for(int i=0; i<CANT_HILOS_SUR; i++){
			pthread_create(&autosSur, NULL, *entradaDelSur, NULL);
		}
		for(int i=0; i<CANT_HILOS_SUR;i++){
			pthread_join(autosSur, NULL);
		}
		for(int i=0; i<CANT_HILOS_NORTE;i++){
			pthread_join(autosNorte, NULL);
		}
}

int main(){

	inicializarSemaforos();

	crearHilos();

	return 0;
}
