#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

int filesRequested = 0;

void* processFile(void* arg) {
  char* file = arg;

  return arg;
}

static void printStatsAndClose(int signo) {
  printf("\nReceived %d file requests\n", filesRequested);
  printf("Shutting down... <ENTER>\n");
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

    char line[200];
    char* file;
    printf("Enter File Name: ");

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
