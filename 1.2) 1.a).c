#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#define timeSleep 1
#define READ 0
#define WRITE 1



int main(int argc, char **argv){
	
	int buffSize=sizeof(char); //Tamanio de un char
	
	int pidPA;
	int pidPB;
	int pidPC;
	int pidPD;
	int pidPE;
	int pidPF;
	
	int pdfB[2];
	int pdfA[2];
	int pdfC[2];
	int pdfDE[2];
	int pdfF[2];
	
	
	
	
	
	int checkPipe=pipe(pdfA)+pipe(pdfB)+pipe(pdfDE)+pipe(pdfF)+pipe(pdfC);
	
	if(checkPipe!=0){
		printf("Error al crear el pipe");
	}
	else{
		pidPA=fork();
		if(pidPA>0){
			pidPB=fork();
			if(pidPB>0){
				pidPD=fork();
				if(pidPD>0){
					pidPE=fork();
					if(pidPE>0){
						pidPC=fork();
						if(pidPC>0){
							pidPF=fork();
							if(pidPF>0){
								for(int i =0; i<6; i++){
									wait(NULL);
								}
							}
							else{
								//Proceso F
								char s;
								while(1){
									read(pdfF[READ],&s,buffSize);
									printf("F \n");
									fflush(stdout);
									write(pdfA[WRITE],"F",buffSize);
									sleep(timeSleep);
								}
							}
						}
						else{
							//Proceso C
							char s;
							while(1){
								read(pdfC[READ],&s,buffSize);
								printf("C ");
								fflush(stdout);
								write(pdfDE[WRITE],"C",buffSize);
								sleep(timeSleep);
							}
						}
					}
					else{
						//Proceso E
						char s;
						while(1){
							read(pdfDE[READ],&s,buffSize);
							printf("E ");
							fflush(stdout);
							if(s=='B'){
								write(pdfA[WRITE],&s,buffSize);
							}
							else{
								write(pdfF[WRITE],&s,buffSize);
							}
							sleep(timeSleep);
						}
					}
				}
				else{
					//Proceso D
					char s;
					while(1){
						read(pdfDE[READ],&s,buffSize);
						printf("D ");
						fflush(stdout);
						if(s=='B'){
							write(pdfA[WRITE],&s,buffSize);
						}
						else{
							write(pdfF[WRITE],&s,buffSize);
						}
						sleep(timeSleep);
					}
				}
			}
			else{
				//Proceso B
				char s;
				while(1){
					read(pdfB[READ],&s,buffSize);
					printf("B ");
					fflush(stdout);
					write(pdfDE[WRITE],"B",buffSize);
					sleep(timeSleep);
				}
			}
		}
		else{
			//Proceso A
			char s;
			close(pdfB[READ]);
			close(pdfDE[READ]);
			write(pdfA[WRITE],"F",buffSize);
			close(pdfA[WRITE]);
			while(1){
				read(pdfA[READ],&s,buffSize);
				printf("A ");
				fflush(stdout);
				if(s=='F'){
					write(pdfB[WRITE],"",buffSize);
				}
				else{
					write(pdfC[WRITE],"",buffSize);
				}
			sleep(timeSleep);
			}
		}
	}
}
