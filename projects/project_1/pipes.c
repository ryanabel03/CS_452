#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void abortServer(int fd[5][2], char server[], int numServers) {
    int k = 0;
    while(k < numServers) {
      close(fd[k][0]);
      close(fd[k][0]);
      
      write(fd[k][1], server, strlen(server) + 1);
      write(fd[k][1], server, strlen(server) + 1);
      fflush(stdout);
      k++;
    }
}

void abortChild(char* childName, char* serverToAbort) {
  if(strcmp(serverToAbort, childName) == 0) {
    printf("Aborting server %s...\n", childName);
    fflush(stdout);
    exit(0);
  }
}

int main() {
  pid_t server[5];
  char str[1024];
  int fd[5][2];
  int serverNum = 0;
  int status;
  int child_index = -1;

  while(1) {
    printf("Prompt: ");
    fflush(stdout);

    fgets(str, 1024, stdin);

    if(strstr(str, "createServer") != NULL) {
      if(serverNum == 4) {
        printf("cannot spawn anymore servers");
        fflush(stdout);
        exit(0);
      }

      if(pipe(fd[serverNum]) < 0) {
        perror("pipe error");
      }

      server[serverNum] = fork();

      //Child
      if(server[serverNum] == 0) {
        char* serverName = NULL;
        int minProcs = 0;
        int maxProcs = 0;
        int activeProcs = 0;
        char* flag[3];
        int fd2[10][2];

        char* throwAway = strtok(str, " ");
        flag[0] = strtok(NULL, " ");

        int m = 0;
        while(flag[m] != NULL) {
          m++;
          flag[m] = strtok(NULL, " ");
        }

        minProcs = atoi(flag[0]);
        maxProcs = atoi(flag[1]);
        activeProcs = minProcs;
        serverName = flag[2];
        serverName[strlen(serverName) - 1] = '\0';
        child_index = serverNum;

        printf("Creating Child PID: %d Name: %s Min Procs:%d Max Procs:%d\n", getpid(), serverName, minProcs, maxProcs);
        fflush(stdout);

        close(fd[child_index][1]);

        while(1) {
          char fromPipe[1024];

          read(fd[child_index][0], fromPipe, sizeof(fromPipe));
          fromPipe[strlen(fromPipe) - 1] = '\0';

          printf("Child %d read %s from pipe\n",getpid(), fromPipe);
          fflush(stdout);
          
          if(strstr(fromPipe, "abortServer") != NULL) {
            char* doNothing = strtok(fromPipe, " ");
            char* serverToAbort = strtok(NULL, " ");
            abortChild(serverName, serverToAbort);
          }
          break;
        }
      }
      //Parent
      if(server[serverNum]) {
        serverNum++;
      }
    } else if(strstr(str, "abortServer") != NULL) {
      abortServer(fd, str, serverNum);
      serverNum--;
    }
  }
  return 0;
}

