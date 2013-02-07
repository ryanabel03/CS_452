#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

int filesRequested = 0;
float fileAccessTime = 0;

void* processFile(void* arg) {
  char* file = arg;

  int num = rand() % 5;
  int sleepTime = 0;
  if(num == 1) {
    sleepTime = rand() % 10 + 7;
    fileAccessTime += sleepTime;
    sleep(sleepTime);
    printf("\nFile %s was not found.\n", file);
    fflush(stdout);
  } else {
    fileAccessTime += 1.0;
    sleep(1);
    printf("\nFile %s found!\n", file);
    fflush(stdout);
  }

  return arg;
}

static void printStatsAndClose(int signo) {
  printf("\nShutting down...\n\n");
  printf("SUMMARY:\n");
  printf("\tReceived %d file requests\n", filesRequested);
  printf("Average file access time was: %2.f seconds", fileAccessTime / filesRequested);
  fflush(stdout);
  kill(getpid(), SIGTERM);

  getchar();
  exit(0);
}

void* getFileFromUser(void* arg) {

  while(1) {
    pthread_t childThread;
    int status;

    if(signal(SIGINT, printStatsAndClose) == SIG_ERR) {
      perror("Could not gracefully shut down");
    }

    printf("Enter File Name: ");
    char line[200];
    char* file;
    fflush(stdout);

    fgets(line, 200, stdin);
    line[strlen(line) - 1] = '\0';
    file = strtok(line, " ");


    if((status = pthread_create(&childThread, NULL, processFile, file)) != 0) {
      fprintf(stderr, "error on thread creation, status: %d", status);
      exit(1);
    }

    filesRequested++;

    pthread_detach(childThread);
  }
  return NULL;
}

int main() {
  pthread_t dispatchThread;
  int status;

  if((status = pthread_create(&dispatchThread, NULL, getFileFromUser, NULL)) != 0) {
    fprintf(stderr, "error on thread creation, status: %d", status);
    exit(1);
  }

  if((status = pthread_join(dispatchThread, NULL)) != 0) {
    fprintf(stderr, "error on thread join, status: %d", status);
    exit(1);
  }

  printf("WTF?");


  return 0;
}
