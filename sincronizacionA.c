#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

sem_t semA, semB, semC, semE, semD, semF, semAux;
#define DELAY 0

void *producirA(){
	while(1){		
		sem_wait(&semA);
		sem_wait(&semA);
		sleep(DELAY);
		printf("A");
		sem_post(&semB);
		sem_post(&semC);
	}
	return 0;
}

void *producirB(){
	while(1){		
		sem_wait(&semB);
		sem_wait(&semB);
		sleep(DELAY);

		printf("B");
		sem_post(&semA);
		sem_post(&semAux);
		sem_post(&semC);
	}
	return 0;
}

void *producirC(){
	while(1){
		sem_wait(&semC);
		sem_wait(&semC);
		sem_wait(&semC);
		sleep(DELAY);

		printf("C");
		sem_post(&semAux);
	}	
	return 0;
}

void *producirD(){	
	while(1){		
		sem_wait(&semAux);
		sleep(DELAY);

		printf("D");
		sem_post(&semF);
		sem_post(&semA);
	}
	return 0;
}

void *producirE(){
		while(1){		
		sem_wait(&semAux);
		sleep(DELAY);

		printf("E");
		sem_post(&semF);
		sem_post(&semA);
	}
	return 0;
}

void *producirF(){	
	while(1){		
		sem_wait(&semF);
		sem_wait(&semF);
		sleep(DELAY);

		printf("F\n");
		sem_post(&semA);
	}
	return 0;
}


void initSems(){
	sem_init(&semA,0,2);
	sem_init(&semB,0,1);
	sem_init(&semC,0,0);
	sem_init(&semAux,0,0);
	sem_init(&semF,0,0);	
}

void initThreads(){
	int CANTHILOS = 6;
	pthread_t hilos[CANTHILOS];
	
	pthread_create(&hilos[0], NULL, producirA, NULL);
	pthread_create(&hilos[1], NULL, producirB, NULL);
	pthread_create(&hilos[2], NULL, producirC, NULL);
	pthread_create(&hilos[3], NULL, producirD, NULL);
	pthread_create(&hilos[4], NULL, producirE, NULL);
	pthread_create(&hilos[5], NULL, producirF, NULL);

	for (int i=0; i<CANTHILOS; i++){
		pthread_join(hilos[i], NULL);
	}
}

int main(){
	initSems();
	initThreads();
	return 0;
}
