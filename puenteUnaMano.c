#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <unistd.h>

#define TIME_CROSSING 1

pthread_t autoNorte, autoSur;
sem_t sem_mutexSur, sem_mutexNorte, sem_autoSur, sem_autoNorte, sem_puente;

void *curzarNorte(){
		sem_wait(&sem_mutexNorte);
		//llego a la entrada
		if(sem_trywait(&sem_autoNorte) == -1){
			//No hay autos cruzando el rio
			sem_wait(&sem_puente);
		}else{
				sem_post(&sem_autoNorte);
			}
		sem_post(&sem_autoNorte);
		sem_post(&sem_mutexNorte);
		
		printf("Soy auto del norte y estoy cruzando el rio\n");
		
		sem_wait(&sem_mutexNorte);
		//Termine de cruzar
		sem_wait(&sem_autoNorte);
		if(sem_trywait(&sem_autoNorte) == -1){
			sem_post(&sem_puente);
		}else{
			sem_post(&sem_autoNorte);
		}
		sem_post(&sem_mutexNorte);
	
		
}

void *cruzarSur(){
		sem_wait(&sem_mutexSur);
		//llego a la entrada
		if(sem_trywait(&sem_autoSur) == -1){
			//No hay autos cruzando el rio
			sem_wait(&sem_puente);
		}else{
				sem_post(&sem_autoSur);
			}
		sem_post(&sem_autoSur);
		sem_post(&sem_mutexSur);
		
		printf("Soy auto del sur y estoy cruzando el rio\n");
		
		sem_wait(&sem_mutexSur);
		//Termine de cruzar
		sem_wait(&sem_autoSur);
		if(sem_trywait(&sem_autoSur) == -1){
			sem_post(&sem_puente);
		}else{
			sem_post(&sem_autoSur);
		}
		sem_post(&sem_mutexSur);
	
}

void inicializarSemaforos(){
	sem_init(&sem_autoNorte, 0, 0);
	sem_init(&sem_autoSur, 0, 0);	
	sem_init(&sem_puente, 0, 1);
	sem_init(&sem_mutexSur, 0, 1);
	sem_init(&sem_mutexNorte, 0, 1);

}

void crearAutos(){
	
	while(1){
		int random = rand();
		
		if(random % 2 == 0){
			pthread_create(&autoNorte, NULL, *curzarNorte, NULL);
		}else{
			pthread_create(&autoSur, NULL, *cruzarSur, NULL);	
		}
		
		sleep(1);
	}
	
}

int main(){
	
	inicializarSemaforos();
	
	crearAutos();
	
	return 0;
}
