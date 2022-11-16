
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>


#define timeSleep 15
#define KEY ((key_t) (9741))
#define sizeMsg sizeof(msg)-sizeof(long)
/*
 * IMPORTANTE: -cambiar el int de la KEY por cada ejecucion o reiniciar la VM (para crear otra cola), 
 * 				ya que sino la cola queda cargada junto con los mensajes de la ejecucion anterior.
 * 				
 * 			   - RV: 2 , RC : 3 , RA: 5, RP: 4. (tipo de mensaje). 
 * 
 * */

typedef struct mensaje{
	long tipo;
	char material;
} msg;

int ayudarReciclador(int tipo, int qId){
	msg msjRecibido;
	switch(tipo){
		case 2 :	if(msgrcv(qId, &msjRecibido, sizeMsg, 3, IPC_NOWAIT)!=-1){
						printf("RV: ayuda a RC reciclando Carton.\n");
						fflush(stdout);
						return 0;
					}
					if(msgrcv(qId, &msjRecibido, sizeMsg, 4, IPC_NOWAIT)!=-1){
						printf("RV: ayuda a RP reciclando Plastico.\n");
						fflush(stdout);
						return 0;
					}
					if(msgrcv(qId, &msjRecibido, sizeMsg, 5, IPC_NOWAIT)!=-1){
						printf("RV: ayuda a RA reciclando Aluminio.\n");
						fflush(stdout);
						return 0;
					}
					break;
		
		case 3 :	if(msgrcv(qId, &msjRecibido, sizeMsg, 2, IPC_NOWAIT)!=-1){
						printf("RC: ayuda a RV reciclando Vidrio.\n");
						fflush(stdout);
						return 0;
					}
					if(msgrcv(qId, &msjRecibido, sizeMsg, 4, IPC_NOWAIT)!=-1){
						printf("RC: ayuda a RP reciclando Plastico.\n");
						fflush(stdout);
						return 0;
					}
					if(msgrcv(qId, &msjRecibido, sizeMsg, 5, IPC_NOWAIT)!=-1){
						printf("RC: ayuda a RA reciclando Aluminio.\n");
						fflush(stdout);
						return 0;
					}
					break;
					
		case 4:		if(msgrcv(qId, &msjRecibido, sizeMsg, 3, IPC_NOWAIT)!=-1){
						printf("RP: ayuda a RC reciclando Carton.\n");
						fflush(stdout);
						return 0;
					}
					if(msgrcv(qId, &msjRecibido, sizeMsg, 2, IPC_NOWAIT)!=-1){
						printf("RP: ayuda a RV reciclando Vidrio.\n");
						fflush(stdout);
						return 0;
					}
					if(msgrcv(qId, &msjRecibido, sizeMsg, 5, IPC_NOWAIT)!=-1){
						printf("RP: ayuda a RA reciclando Aluminio.\n");
						fflush(stdout);
						return 0;
					}
					break;
					
		case 5 :	if(msgrcv(qId, &msjRecibido, sizeMsg, 3, IPC_NOWAIT)!=-1){
						printf("RA: ayuda a RC reciclando Carton.\n");
						fflush(stdout);
						return 0;
					}
					if(msgrcv(qId, &msjRecibido, sizeMsg, 4, IPC_NOWAIT)!=-1){
						printf("RA: ayuda a RP reciclando Plastico.\n");
						fflush(stdout);
						return 0;
					}
					if(msgrcv(qId, &msjRecibido, sizeMsg, 2, IPC_NOWAIT)!=-1){
						printf("RA: ayuda a RV reciclando Vidrio.\n");
						fflush(stdout);
						return 0;
					}
					break;
	}
	return -1;
}

void reciclador(int qId,char rec){
	msg msjRecibido;
	int tipo;
	switch(rec){
		case 'V': tipo=2;
				  break;
		
		case 'C': tipo=3;
				  break;
		
		case 'A': tipo=5;
				  break;
		
		case 'P': tipo=4;
				  break;
	}
	while(1){
		if(msgrcv(qId,&msjRecibido,sizeMsg,tipo,IPC_NOWAIT)!=-1){
			printf("R%c: recibo %c y reciclo.\n",rec,msjRecibido.material);
			fflush(stdout);
		}
		else{
			if(ayudarReciclador(tipo,qId)==-1){
				printf("R%c: tomo mate.\n",rec);
				fflush(stdout);
			}
		}
		sleep(timeSleep);
	}
}
 
void sendToReciclator(msg msj,char clasf,int qId){
	switch(msj.material){
		
		case 'V': 	msj.tipo=2;
					if(msgsnd(qId,&msj,sizeMsg,0)==0){
						printf("C%c: envio %c a RV.\n",clasf,msj.material);
						fflush(stdout);
					}
					break;
		
		case 'C':	msj.tipo=3;
					if(msgsnd(qId,&msj,sizeMsg,0)==0){
						printf("C%c: envio %c a RC.\n",clasf,msj.material);
						fflush(stdout);
					}
					break;
		
		case 'P': 	msj.tipo=4;
					if(msgsnd(qId,&msj,sizeMsg,0)==0){
						printf("C%c: envio %c a RP.\n",clasf,msj.material);
						fflush(stdout);
					}
					break;
		
		case 'A': 	msj.tipo=5;
					if(msgsnd(qId,&msj,sizeMsg,0)==0){
						printf("C%c: envio %c a RA.\n",clasf,msj.material);
						fflush(stdout);
					}
					break;
	}
}


int main(){
	
	
	time_t t;
	
	int queueId;
	
	char materiales[4]={'V','C','P','A'};
	
	int pidR1;
	int pidR2;
	int pidR3;
	int pidC1;
	int pidC2;
	int pidRV;
	int pidRC;
	int pidRP;
	int pidRA;
	
	pidR1=fork();
	if(pidR1>0){
		pidR2=fork();
		if(pidR2>0){
			pidR3=fork();
			if(pidR3>0){
				pidC1=fork();
				if(pidC1>0){
					pidC2=fork();
					if(pidC2>0){
						pidRV=fork();
						if(pidRV>0){
							pidRC=fork();
							if(pidRC>0){
								pidRP=fork();
								if(pidRP>0){
									pidRA=fork();
									if(pidRA>0){
										queueId = msgget(KEY,IPC_CREAT|0666);
										for(int i=0; i<9; i++){
											wait(NULL);
										}
									}
									else{
										//Reciclador Aluminio
										queueId= msgget(KEY,0666);
										reciclador(queueId,'A');
									}
								}
								else{
									//Reciclador Plastico
									queueId= msgget(KEY,0666);
									reciclador(queueId,'P');
								}
							}
							else{
								//Reciclador Carton
								queueId= msgget(KEY,0666);
								reciclador(queueId,'C');
							}
						}
						else{
							//Reciclador Vidrio
							queueId= msgget(KEY,0666);
							reciclador(queueId,'V');
						}
					}
					else{
						//Clasificador 2
						queueId= msgget(KEY,0666);
						msg msjRecibido;
						while(1){
							
							if(msgrcv(queueId,&msjRecibido,sizeMsg,1,0)!=-1){
								printf("C2: Mensaje recibido %c.\n",msjRecibido.material);
								fflush(stdout);
								sendToReciclator(msjRecibido,'2',queueId);
							}
							else{
								printf("Error al enviar %c desde C2\n.",msjRecibido.material);
								fflush(stdout);
							}
							sleep(timeSleep);
						}
					}
				}
				else{
					//Clasificador 1
					queueId = msgget(KEY,0666);
					msg msjRecibido;
					while(1){
						
						if(msgrcv(queueId,&msjRecibido,sizeMsg,1,0)!=-1){
							printf("C1: Material recibido %c.\n",msjRecibido.material);
							fflush(stdout);
							sendToReciclator(msjRecibido,'1',queueId);
						}
						else{
							printf("Error al enviar %c desde C1\n.",msjRecibido.material);
							fflush(stdout);
						}
						sleep(timeSleep);
					}
				}
			}
			else{
				//Recolector 3
				queueId= msgget(KEY,0666);
				msg msj;
				while(1){
					srand (getpid()*(unsigned)time(&t));
					
					msj.tipo=1;
					msj.material=materiales[rand() % 4];;
					
					if(msgsnd(queueId,&msj,sizeMsg,0)==0){
						printf("R3: envio %c a los clasificadores.\n",msj.material);
						fflush(stdout);
					}
					else{
						printf("Error al enviar %c desde R1.\n",msj.material);\
						fflush(stdout);
					}
					sleep(timeSleep);
				}
				
			}
		}
		else{
			//Recolector 2
			queueId= msgget(KEY,0666);
			msg msj;
			while(1){
				srand (getpid()*(unsigned)time(&t));
				
				msj.tipo=1,
				msj.material=materiales[rand() % 4];
				
				if(msgsnd(queueId,&msj,sizeMsg,0)==0){
					printf("R2: envio %c a los clasificadores.\n",msj.material);
					fflush(stdout);
				}
				else{
					printf("Error al enviar %c desde R2.\n",msj.material);\
					fflush(stdout);
				}
				sleep(timeSleep);
			}
		}
	}
	else{
		//Recolector 1
		queueId = msgget(KEY,0666);
		msg msj;
		while(1){
			srand (getpid()*(unsigned)time(&t));
			
			msj.tipo = 1;
			msj.material = materiales[rand() % 4];
			
			if(msgsnd(queueId,&msj,sizeMsg,0)==0){
				printf("R1: envio %c a los clasificadores.\n",msj.material);
				fflush(stdout);
			}
			else{
				printf("Error al enviar %c desde R1.\n",msj.material);\
				fflush(stdout);
			}
			sleep(timeSleep);
		}
		
	}
}
