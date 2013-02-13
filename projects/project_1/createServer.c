#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main() {

  pid_t servers[10];
  int i = 0;
  pid_t pid;
  int status;
  ssize_t num;
  char str[1024];
  int fd[2];

  if(pipe(fd) < 0) {
    perror("pipe error");
  }

  if((pid = fork()) < 0) {
    perror("fork error 1");


  } else if(pid == 0) {
    pid = getpid();
    char* serverName;
    pid_t childpid;
    int minNum = 0;
    int maxNum = 0;
    int activeNum = 0;
    char* flag[5];

    close(fd[1]);

    while(1) {
      read(fd[0], str, sizeof(str));

      if(strstr(str, serverName) != NULL) {
        printf("We have a match!");
        fflush(stdout);
      }

      if(strstr(str, "createServer") != NULL) {
        printf("we will be creating a server today");
        fflush(stdout);
        char* throwaway = strtok(str, " ");
        flag[0] = strtok(NULL, " ");

        int m = 0;
        while(flag[m] != NULL) {
          m++;
          flag[m] = strtok(NULL, " ");
        }

        minNum = atoi(flag[0]);
        maxNum = atoi(flag[1]);
        flag[2][strlen(flag[2]) - 1] = '\0';
        serverName = flag[2];

        while(i < minNum) {
          fflush(stdout);
          if((childpid = fork()) < 0) {
            perror("fork error");
          } else if(childpid == 0) {
            childpid = getpid();
            exit(status);
          } else {
            servers[i] = wait(&status);
            i++;
          }
        }
      }
    }
    exit(status);
  } else {
    while(1) {
      char* flags[5];
      printf("Prompt: ");
      fflush(stdout);

      fgets(str, 1024, stdin);

      close(fd[0]);

      if(strstr(str, "createServer") != NULL) {
        write(fd[1], str, strlen(str) + 1);
      }
    }
    servers[i] = wait(&status);
  }
  return 0;
}
