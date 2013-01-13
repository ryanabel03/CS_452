#include <stdio.h>
#include <term.h>
#include <curses.h>
#include <stdlib.h>

int main() {
  int rows, cols;

  setupterm(NULL, fileno(stdout), (int *)0);

  char *clearSequence = tigetstr("clear");
  char *clearAndHome = tparm(clearSequence);
  putp(clearAndHome);

  rows = tigetnum("lines");
  cols = tigetnum("cols");
  printf("ROWS: %d \t COLUMNS: %d \n", rows, cols);

  return 0;
}
