#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main() {
  pid_t pid;
  char str[1024];
  int fd[5][2];
  int i = 0;
  int status;
  int child_index = -1;

  while(i < 2) {

    if(pipe(fd[i]) < 0) {
      perror("pipe error");
    }

    pid = fork();
    if(pid == 0) {
      child_index = i;
      printf("what is child index? %d", child_index);
      fflush(stdout);
      printf("Created child %d\n", getpid());
      char str2[1024];

      close(fd[child_index][1]);

      read(fd[child_index][0], str2, sizeof(str2));
      printf("Child %d read %s from pipe\n",getpid(), str2);
      fflush(stdout);

      break;
    }
    i++;
  }


  if(pid) {
    printf("Prompt: ");
    fflush(stdout);
    fgets(str, 1024, stdin);

    close(fd[0][0]);
    close(fd[1][0]);
    
    write(fd[0][1], str, strlen(str) + 1);
    write(fd[1][1], str, strlen(str) + 1);
    fflush(stdout);
  }
  return 0;
}
