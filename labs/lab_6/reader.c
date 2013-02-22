/*
 * Simple Writer
 * Author: Ryan Abel, Corey Jones
 *
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
	strcpy(flag, "w"); //Writers write
	while(1){
		while(flag[0] == 'w');// Writers turn
		fprintf(stderr, "%s", shmPtr);
		strcpy(flag, "w");
	}

	return 0; 
}
void sigHandler(int sigNum) {
	fprintf(stderr, "Exiting...\n");
	exit(0);
}
