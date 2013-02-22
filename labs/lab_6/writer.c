/*
 * Simple Writer to shared memory
 * Author: Ryan Abel, Corey Jones
 */
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/stat.h>
#include <sys/ipc.h> 
#include <sys/shm.h>
#include <unistd.h> 
#include <string.h>
#include <signal.h>

#define SIZE 4096

void sigHandler(int);

int shmId; 
char *shmPtr;

int main () 
{
	signal(SIGINT, sigHandler);
	if ((shmId = shmget (ftok("/home/abelr/CIS_452/labs/lab_3/sample_program1.c", 3), SIZE, IPC_CREAT|S_IRUSR|S_IWUSR)) < 0) { 
	  perror ("i can't get no..\n"); 
	  exit (1); 
	} 
	if ((shmPtr = shmat (shmId, 0, 0)) == (void*) -1) { 
	  perror ("can't attach\n"); 
	  exit (1); 
	}

	char* flag = shmPtr;

	shmPtr += 2;
	strcpy(flag, "r"); // Readers read
	char text[100]; 
	while(1){
		while(flag[0] == 'r');//Readers turn 
		fgets(text, sizeof text, stdin); 
		strcpy(shmPtr, text);
		strcpy(flag, "r");//Make readers turn
	}

	return 0; 
}
void sigHandler(int sigNum) {
	shmdt (shmPtr);
	shmctl (shmId, IPC_RMID, 0);
	fprintf(stderr, "Exiting...\n");
	exit(0);
}
