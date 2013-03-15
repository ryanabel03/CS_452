/*
 * Protecting the Critical Section
 * Author: Ryan Abel, Corey Jones
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/sem.h>
#include <signal.h>

#define SIZE 16

void clean_exit(int);

int semId;

int main (int argc, char* argv[])
{
   int status;
   long int i, loop, temp, *shmPtr;
   int shmId;
   pid_t pid;
   struct sembuf WAIT, SIGNAL;

   // get value of loop variable (from command-line argument)
   loop = atoi(argv[1]);

   if ((shmId = shmget (IPC_PRIVATE, SIZE, IPC_CREAT|S_IRUSR|S_IWUSR)) < 0) {
      perror ("i can't get no..\n");
      exit (1);
   }
   if ((shmPtr = shmat (shmId, 0, 0)) == (void*) -1) {
      perror ("can't attach\n");
      exit (1);
   }

   shmPtr[0] = 0;
   shmPtr[1] = 1;

   semId = semget(IPC_PRIVATE, 1, 00600);
   if(semId < 0)
      perror("semget() failed.\n");
   if(semctl(semId, 0, SETVAL, 1) < 0)
      perror("semctl() failed.\n");

   WAIT.sem_num = 0;
   WAIT.sem_op = -1;
   WAIT.sem_flg = SEM_UNDO;
   SIGNAL.sem_num = 0;
   SIGNAL.sem_op = 1;
   SIGNAL.sem_flg = SEM_UNDO;

   signal(SIGINT, clean_exit);

   if (!(pid = fork())) {
      for (i=0; i<loop; i++) {
               // swap the contents of shmPtr[0] and shmPtr[1]
               semop(semId, &WAIT, 1);
               temp = shmPtr[0];
               shmPtr[0] = shmPtr[1];
               shmPtr[1] = temp;
               semop(semId, &SIGNAL, 1);
      }
      if (shmdt (shmPtr) < 0) {
         perror ("just can't let go\n");
         exit (1);
      }
      exit(0);
   }
   else
      for (i=0; i<loop; i++) {
               // swap the contents of shmPtr[1] and shmPtr[0]
               semop(semId, &WAIT, 1);
               temp = shmPtr[0];
               shmPtr[0] = shmPtr[1];
               shmPtr[1] = temp;
               semop(semId, &SIGNAL, 1);
      }

   wait(&status);
   if(semctl(semId, 0, IPC_RMID) < 0)
      perror("semctl() failed.\n");

   printf ("values: %li\t%li\n", shmPtr[0], shmPtr[1]);

   if (shmdt (shmPtr) < 0) {
      perror ("just can't let go\n");
      exit (1);
   }
   if (shmctl (shmId, IPC_RMID, 0) < 0) {
      perror ("can't deallocate\n");
      exit(1);
   }

   return 0;
}

void
clean_exit(int sigNum)
{
   if(semctl(semId, 0, IPC_RMID) < 0)
      perror("semctl() failed.\n");

   exit(0);
}
