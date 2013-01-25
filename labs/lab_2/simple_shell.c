#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/resource.h>

int main() {
  char* line;
  char* command;
  char* flags;
  char* quit = "quit";
  char* fullCommand[3];
  int status;
  struct rusage usage;

  while(1) {
    pid_t pid, child;
    printf("Prompt: ");

    //Get and parse user input
    fgets(line, 100, stdin);
    line[strlen(line) - 1] = '\0';
    command = strtok(line, " ");
    flags = strtok(NULL, " ");

    //Create command to execute
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
      getrusage(RUSAGE_SELF, &usage);
      child = wait(&status);
      printf("CPU Usage: %ld.%06d\n", usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);
    }
  }
  return 0;
}
