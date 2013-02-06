#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void* processFile(void* arg) {
  char* file = arg;

  return arg;
}

void* getFileFromUser(void* arg) {
  int filesRequested = 0;
  while(1) {
    //TODO: ADD SIGNAL HANDLER
    pthread_t childThread;
    int status;

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
  return (void *) filesRequested;
}

int main() {
  pthread_t dispatchThread;
  int status;

  void* filesRequested = NULL;


  if((status = pthread_create(&dispatchThread, NULL, getFileFromUser, NULL)) != 0) {
    fprintf(stderr, "error on thread creation, status: %d", status);
    exit(1);
  }

  if((status = pthread_join(dispatchThread, &filesRequested)) != 0) {
    fprintf(stderr, "error on thread join, status: %d", status);
    exit(1);
  }

  int requests = (int) filesRequested;  

  printf("# of requests %d", requests);
  return 0;
}
