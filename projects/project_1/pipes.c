#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void sendServerAbort(int fd[5][2], char server[], int numServers) {
    int k = 0;
    while(k < numServers) {
      close(fd[k][0]);
      
      write(fd[k][1], server, strlen(server) + 1);
      fflush(stdout);
      k++;
    }
}

void abortServer(char* childName, char* serverToAbort) {
  if(strcmp(serverToAbort, childName) == 0) {
    printf("Aborting server %s...\n", childName);
    fflush(stdout);
    exit(0);
  }
}

void abortGrandChild(int fd[10][2], int numActive, int numMin, char* childToAbort, char* serverName) {
  if(strcmp(serverName, childToAbort) == 0) {
    if(numActive - 1 > numMin) {
      char message[] = "kill";
      close(fd[numActive - 1][0]);
      write(fd[numActive - 1][1], message, strlen(message) + 1);
      fflush(stdout);
    } else {
      printf("Deleting child on %s will put it under minimum of %d\n", serverName, numMin);
    }
  }
}

void displayPrompt() {
  printf("Prompt: ");
  fflush(stdout);
}

int main() {
  pid_t server[5];
  char str[1024];
  int fd[5][2];
  int serverNum = 0;
  int status;
  int child_index = -1;

  displayPrompt();

  while(1) {

    fgets(str, 1024, stdin);

    if(strstr(str, "createServer") != NULL) {
      if(serverNum == 4) {
        printf("cannot spawn anymore servers\n");
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
        pid_t child[10];

        char* throwAway = strtok(str, " ");
        flag[0] = strtok(NULL, " ");

        int m = 0;
        while(flag[m] != NULL) {
          m++;
          flag[m] = strtok(NULL, " ");
        }

        minProcs = atoi(flag[0]);
        maxProcs = atoi(flag[1]);
        serverName = flag[2];
        serverName[strlen(serverName) - 1] = '\0';
        child_index = serverNum;

        while(activeProcs < minProcs) {
          if(pipe(fd2[activeProcs]) < 0) {
            perror("pipe error 3");
          }

          child[activeProcs] = fork();

          //Child
          if(child[activeProcs] == 0) {
            printf("Creating grandchild for process %d\n", getppid());
            fflush(stdout);
            while(1) {
              char fromParent[1024];
              read(fd2[activeProcs][0], fromParent, sizeof(fromParent));

              printf("Grand child received %s", fromParent);
              fflush(stdout);

              fromParent[strlen(fromParent) - 1] = '\0';

              if(strstr(fromParent, "kill") != NULL) {
                printf("Killing grandchild process\n");
                fflush(stdout);
                displayPrompt();
                exit(0);  
              }
            }
          }
          
          //Parent
          if(child[activeProcs]){
            activeProcs++;
          }
        }

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
            abortServer(serverName, serverToAbort);
          } else if(strstr(fromPipe, "abortProc") != NULL) {
            printf("got abortProc");
            fflush(stdout);
            char* doNothing = strtok(fromPipe, " ");
            char* onServer = strtok(NULL, " ");
            abortGrandChild(fd2, activeProcs, minProcs, onServer, serverName);
          } else if(strstr(fromPipe, "createProc") != NULL) {
            printf("got createProc\n");
            fflush(stdout);

          }
        }
        break;
      }
      //Parent
      if(server[serverNum]) {
        serverNum++;
      }
    } else if(strstr(str, "abortServer") != NULL) {
      sendServerAbort(fd, str, serverNum);
      serverNum--;
    } else if(strstr(str, "abortProc") != NULL) {
      sendServerAbort(fd, str, serverNum); 
    }
  }
  return 0;
}

