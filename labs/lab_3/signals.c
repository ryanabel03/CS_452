#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sigHandler(int sigNum) {

}

int main() {
  pid_t pid;
  if((pid = fork()) < 0) {
    perror("fork failure");
    exit(1);
  } else if (pid == 0) {
    printf("Spawned child PID# %ld\n", (long) getpid());
    printf("waiting...");
    signal(SIGINT, sigHandler); 
  } else {
    child = wait(&status);
  } 
}
