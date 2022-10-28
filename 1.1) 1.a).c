#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#define timeSleep 20 
#define READ 0
#define WRITE 1



int main(int argc, char **argv){
	time_t t;
	
	int buffSize=sizeof(char); //Tamanio de un char
	
	char materiales[4]={'V','C','P','A'};
	
	int R_pdf_C[2];
	
	int pdf_RV[2];
	int pdf_RP[2];
	int pdf_RA[2];
	int pdf_RC[2];
	
	int pidR1;
	int pidR2;
	int pidR3;
	int pidC1;
	int pidC2;
	int pidRV;
	int pidRC;
	int pidRP;
	int pidRA;
	
	if(pipe(R_pdf_C)+pipe(pdf_RV)+pipe(pdf_RP)+pipe(pdf_RA)+pipe(pdf_RC)!=0){
		printf("Algun pipe fallo en su creacion.\n");
	}
	else{
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
											for(int i=0;i<9;i++){
												wait(NULL);
											}
										}
										else{
											//Reciclador A
											close(pdf_RA[WRITE]);
											fcntl(pdf_RA[READ], F_SETFL, O_NONBLOCK);
											
											char material;
											while(1){
												if(read(pdf_RA[READ], &material, buffSize)==-1){
													printf("RA: Matesiiiiiito.\n");
													fflush(stdout);
												}
												else{
													printf("RA: recivi %c y reciclo.\n",material);
													fflush(stdout);
												}
												sleep(timeSleep);
											}
										}
									}
									else{
										//Reciclador P
										close(pdf_RP[WRITE]);
										fcntl(pdf_RP[READ], F_SETFL, O_NONBLOCK);
										
										char material;
										while(1){
											if(read(pdf_RP[READ], &material, buffSize)==-1){
												printf("RP: Matesiiiiiito.\n");
												fflush(stdout);
											}
											else{
												printf("RP: recivi %c y reciclo.\n",material);
												fflush(stdout);
											}
											sleep(timeSleep);
										}
									}
								}
								else{
									//Reciclador C
									close(pdf_RC[WRITE]);
									fcntl(pdf_RC[READ], F_SETFL, O_NONBLOCK);
									
									char material;
									while(1){
										if(read(pdf_RC[READ], &material, buffSize)==-1){
											printf("RC: Matesiiiiiito.\n");
											fflush(stdout);
										}
										else{
											printf("RC: recivi %c y reciclo.\n",material);
											fflush(stdout);
										}
										sleep(timeSleep);
									}
								}
							}
							else{
								//Reciclador V
								close(pdf_RV[WRITE]);
								fcntl(pdf_RV[READ], F_SETFL, O_NONBLOCK);
								
								char material;
								while(1){
									if(read(pdf_RV[READ], &material, buffSize)==-1){
										printf("RV: Matesiiiiiito.\n");
										fflush(stdout);
									}
									else{
										printf("RV: recivi %c y reciclo.\n",material);
										fflush(stdout);
									}
									sleep(timeSleep);
								}
								
							}
						}
						else{
							//Clasificador 2
							close(R_pdf_C[WRITE]);
							close(pdf_RV[READ]);
							close(pdf_RC[READ]);
							close(pdf_RP[READ]);
							close(pdf_RA[READ]);
							
							char material;
							while(1){
								read(R_pdf_C[READ], &material, buffSize);
								switch(material){
									case('V'):  write(pdf_RV[WRITE], &material, buffSize);
												printf("C2 recivio %c y envio a RV.\n",material);
												fflush(stdout);
												break;
								
									case('C'):  write(pdf_RC[WRITE], &material, buffSize);
												printf("C2 recivio %c y envio a RC.\n",material);
												fflush(stdout);
												break;
												
									case('P'):  write(pdf_RP[WRITE], &material, buffSize);
												printf("C2 recivio %c y envio a RP.\n",material);
												fflush(stdout);
												break;
												
									case('A'):  write(pdf_RA[WRITE], &material, buffSize);
												printf("C2 recivio %c y envio a RA.\n",material);
												fflush(stdout);
												break;
								}
								sleep(timeSleep);
							}
						}
					}
					else{
						//Clasificador 1
						close(R_pdf_C[WRITE]);
						close(pdf_RV[READ]);
						close(pdf_RC[READ]);
						close(pdf_RP[READ]);
						close(pdf_RA[READ]);
						
						char material;
						while(1){
							read(R_pdf_C[READ],&material,buffSize);
							switch(material){
								case('V'):  write(pdf_RV[WRITE], &material, buffSize);
											printf("C1 recivio %c y envio a RV.\n",material);
											fflush(stdout);
											break;
								
								case('C'):  write(pdf_RC[WRITE], &material, buffSize);
											printf("C1 recivio %c y envio a RC.\n",material);
											fflush(stdout);
											break;
											
								case('P'):  write(pdf_RP[WRITE], &material, buffSize);
											printf("C1 recivio %c y envio a RP.\n",material);
											fflush(stdout);
											break;
											
								case('A'):  write(pdf_RA[WRITE], &material, buffSize);
											printf("C1 recivio %c y envio a RA.\n",material);
											fflush(stdout);
											break;
							}
							sleep(timeSleep);
						}
					}
				}
				else{
					//Recolector 3 
					close(R_pdf_C[READ]);
					char material;
					while(1){
						srand (getpid()*(unsigned)time(&t));
						material=materiales[rand() % 4];
						write(R_pdf_C[WRITE], &material,buffSize);
						printf("R3 envio %c .\n",material);
						fflush(stdout);
						sleep(timeSleep);
					}
				}
			}
			else{
				//Recolector 2
				close(R_pdf_C[READ]);
				char material;
				while(1){
					srand (getpid()*(unsigned)time(&t));
					material=materiales[rand() % 4];
					write(R_pdf_C[WRITE], &material, buffSize);
					printf("R2 envio %c .\n",material);
					fflush(stdout);
					sleep(timeSleep);
				}
			}
		}
		else{
			//Recolector 1 
			close(R_pdf_C[READ]);
			char material;
			while(1){
				srand (getpid()*(unsigned)time(&t));
				material=materiales[rand() % 4];
				write(R_pdf_C[WRITE], &material, buffSize);
				printf("R1 envio %c .\n",material);
				fflush(stdout);
				sleep(timeSleep);
			}
		}
	}
	
	return 0;
	
	
	/*Preguntar o justo se hacen los cambio de contexto de esa forma o hay algo mal en el codigo que no encuentro
		RC: Matesiiiiiito.
		RV: Matesiiiiiito.
		RP: Matesiiiiiito.
		C1 recivio A y envio a RA.
		C2 recivio P y envio a RP.
		R2 envio A .
		R1 envio P .
		R3 envio P .
		RA: recivi A y reciclo.
	 
	 */
}
