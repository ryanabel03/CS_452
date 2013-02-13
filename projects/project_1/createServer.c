#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main() {

  pid_t servers[10];
  int i = 0;
  int status;
  char str[1024];
  int fd[2];

  if(pipe(fd) < 0) {
    perror("pipe error");
  }

  while(1) {
    char* flags[5];
    printf("Prompt: ");
    fflush(stdout);

    fgets(str, 1024, stdin);
    fflush(stdout);

    if(strstr(str, "createServer") != NULL) {
      if((servers[i] = fork()) < 0) {
        perror("fork error 1");
      } else if(servers[i] == 0) {

        char* serverName = NULL;
        pid_t childpid;
        int minNum = 0;
        int maxNum = 0;
        int activeNum = 0;
        char* flag[5];

        while(1) {
          close(fd[1]);
          char str2[1024];

          read(fd[0], str2, sizeof(str2));

          printf("got string: %s", str2);
          fflush(stdout);

          if(strstr(str2, "createServer") != NULL) {
            printf("we will be creating a server today\n");
            fflush(stdout);
            char* throwaway = strtok(str2, " ");
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

            int k = 0;
            while(k < minNum) {
              if((childpid = fork()) < 0) {
                perror("fork error");
              } else if(childpid == 0) {
                childpid = getpid();
                exit(status);
              } else {
                servers[k] = wait(&status);
                k++;
              }
            }
          } else if(strstr(str2, "abortServer") != NULL) {
            printf("Server name: %s");
          }
        }
      } else {
        i++;
        write(fd[1], str, strlen(str) + 1);
      }
    } else if(strstr(str, "abortServer") != NULL) {
        int k = 0;
        while(k < i) {
          printf("putting %s in the pipe\n", str);
          fflush(stdout);
          write(fd[1], str, strlen(str) + 1);
          k++;
        }
    }
  }
  return 0;
}
