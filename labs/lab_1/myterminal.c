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
  printf("ROWS: %d \t COLUMNS: %d", rows, cols);

  char *moveCursor = tigetstr("cup");
  char *translateMove = tparm(moveCursor, 10, 3);
  putp(translateMove);
  printf("I am here!!");

  char *translateMove2 = tparm(moveCursor, 26, 9);
  putp(translateMove2);
  printf("Now I am here!");

  return 0;
}
