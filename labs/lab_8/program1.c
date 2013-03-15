#include <stdio.h>
#include <stdlib.h>

int r = 4;
int s;
int main(int argc, char *argv[]) {
  int x = 5;
  int y = 2;

  int w = (int) malloc(sizeof(int));
  int v = (int) malloc(sizeof(int));

  printf("-------------------------------\n");
  printf("TOP OF STACK: %p\n", &x);
  printf("ADDRESS IN STACK:%p\n", &y);
  printf("-------------------------------\n");
  printf("ADRESS IN HEAP: %p\n", &v);
  printf("BOTTOM OF HEAP: %p\n", &w);
  printf("-------------------------------\n");
  printf("TOP OF DATA: %p\n", &w);
  printf("-------------------------------\n");
  printf("INITIALIZED DATA: %p\n", &r);
  printf("UN-INITIALIZED DATA: %p\n", &s);



  printf("\n\n\n");
  printf("INITIALIZED DATA ADDRESS: %p\n", &r);
  printf("UN-INITIALIZED DATA ADDRESS: %p\n", &s);
  printf("RUN TIME DATA: %p\n", &v);
  printf("STACK:%p\n", &y);
  printf("ENVIRONMENTAL DATA:%p\n", &argv[0]);

  return 0;
}
