#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main() {
  pid_t pid;
  char str[1024];
  int fd[2];

  if(pipe(fd) < 0) {
    perror("pipe error");
  }

  if((pid = fork()) < 0) {


  } else if(pid == 0) {
    close(fd[1]);

    read(STDIN_FILENO, str, sizeof(str));

    printf("Child read %s from pipe", str);


  } else {
    printf("Prompt: ");
    fflush(stdout);
    fgets(str, 1024, stdin);

    close(fd[0]);

    write(STDOUT_FILENO, str, strlen(str) + 1);
  }

  return 0;
}
