#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <unistd.h>

#define TIME_CROSSING 1

pthread_t autoNorte, autoSur;
sem_t sem_norte, sem_sur, sem_puente;

void *curzarNorte(){
	while(1){
		
		if(sem_trywait(&sem_sur) != 0){
			printf("No hay autos que vienen del sur\n");
			
			sem_post(&sem_norte);
			printf("Estoy cruzando el puente desde el norte\n");
			sleep(TIME_CROSSING);
			printf("Termine de cruzar desde el norte\n");
			
			sem_wait(&sem_norte);
			break;
		}else{
			sem_post(&sem_sur);
		}
	}
}

void *cruzarSur(){
	while(1){
		if(sem_trywait(&sem_norte) != 0){
			printf("No hay autos que vienen del norte\n");
			
			sem_post(&sem_sur);
			printf("Estoy cruzando el puente desde el sur\n");
			sleep(TIME_CROSSING);
			printf("Termine de cruzar desde el sur\n");
			
			sem_wait(&sem_sur);
			break;
		}else{s
			sem_post(&sem_norte);
		}
	}
}

int main(){
	
	sem_init(&sem_norte, 0, 0);
	sem_init(&sem_sur, 0, 0);	
	sem_init(&sem_puente, 0, 1);
	
	pthread_create(&autoNorte, NULL, *curzarNorte, NULL);
	pthread_create(&autoSur, NULL, *cruzarSur, NULL);	

	pthread_join(autoNorte, NULL);
	pthread_join(autoSur, NULL);

	
	return 0;
}
