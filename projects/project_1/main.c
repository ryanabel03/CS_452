#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

pid_t servers[10];
pid_t children[10];

void processCommand(char *, char *[]);

void getCommand() {
  char line[200];
  char* command = NULL;
  char* flags[10];

  printf("Enter a command: ");
  fgets(line, 200, stdin);
  line[strlen(line) - 1] = '\0';
  command = strtok(line, " ");
  flags[0] = strtok(NULL, " ");

  int i = 0;
  while(flags[i] != NULL) {
    i++;
    flags[i] = strtok(NULL, " ");
  }
  processCommand(command, flags);

}

void createServer(char* params[]) {

}

void abortServer(pid_t serverPID) {
}

void processCommand(char* command, char* params[]) {

  int i = 0;
  
  if(strcmp(command, "createServer") == 0) {
    createServer(params);
  } else if (strcmp(command, "abortServer") == 0) {
    
  } else if (strcmp(command, "displayStatus") == 0) {
    /* displayStatus(char* params[]); */
  } else if (strcmp(command, "createProc") == 0) {
    /* createProc(char* params[]); */
  } else if(strcmp(command, "abortProc") == 0) {
    /* abortProc(char* params[]); */
  } else {
    printf("Please enter a valid command.\n");
  }
}

int main() {
  while(1) { 
    getCommand();
  }
}
