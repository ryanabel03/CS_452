#include <stdio.h>
#include <string.h>

void processCommand(char *, char *);

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
  processCommand(command, *flags);

}

void processCommand(char* command, char* flags) {
  if(strcmp(command, "createServer") == 0) {
    printf("create server!");
  } else if (strcmp(command, "abortServer") == 0) {
    printf("abortServer");
  } else if (strcmp(command, "displayStatus") == 0) {
    printf("displayStatus");
  } else if (strcmp(command, "createProc") == 0) {
    printf("createProc");
  } else if(strcmp(command, "abortProc") == 0) {
    printf("abortProc");
  } else {
    printf("Please enter a valid command.\n");
  }
}

int main() {
  getCommand();
}
