#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
  char* line;
  char* command;
  char* flags;
  char* quit = "quit";
  char* fullCommand[3];
  int status, x;
  x = 1; 

  while(x == 1) {
    pid_t pid, child;

    printf("Prompt: ");
    fgets(line, 100, stdin);
    line[strlen(line) - 1] = '\0';
    command = strtok(line, " ");
    flags = strtok(NULL, " ");

    fullCommand[0] = command;
    fullCommand[1] = flags;
    fullCommand[2] = NULL;

    if(strcmp(quit, command) == 0){
      puts("Exiting shell...");
      break;
    }

    if((pid = fork()) < 0) {
      perror("fork failure");
      exit(1);
    }
    else if (pid == 0) {
      if(execvp(fullCommand[0], &fullCommand[0]) < 0) {
        perror("Command execution failed.");
        exit(1);
      } else {
        exit(status);
      }
    } else {
      child = wait(&status);
    }
  }
  return 0;
}
