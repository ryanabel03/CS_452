#include <stdio.h>
#include <term.h>
#include <curses.h>
#include <stdlib.h>
#include <unistd.h>

void moveCursor(int row, int column) {
  char *moveCursor = tigetstr("cup");
  char *translateMove = tparm(moveCursor, column, row);
  putp(translateMove);
  printf("I am here!!\n");
}

void clearAndHome() {
  char *clearSequence = tigetstr("clear");
  char *clearAndHome = tparm(clearSequence);
  putp(clearAndHome);
}

void showRowsAndColumns() {
  int rows, cols;

  rows = tigetnum("lines");
  cols = tigetnum("cols");
  printf("ROWS: %d \t COLUMNS: %d", rows, cols);
}

int main() {

  setupterm(NULL, fileno(stdout), (int *)0);

  clearAndHome();

  showRowsAndColumns();

  moveCursor(28, 9);
  sleep(3);
  moveCursor(10, 3);

  return 0;
}
