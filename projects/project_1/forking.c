#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main() {
  pid_t pid;
  int i = 0;



  while(i < 2) {
    pid = fork();

    if(pid == 0) {
      printf("Child process %d\n", getpid());
      fflush(stdout);
      break;
    }
    i++;
  }

  if(pid) {
    printf("What is pid? %d", getpid());

    printf("I got here\n");
    fflush(stdout);
  }

  return 0;

}
