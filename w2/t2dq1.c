#include<stdio.h>
#include<stdlib.h>

int main()
{
  int turn = 0;
  while (turn != 0){ printf("while loop p0\n"); }
  printf("critical section p0\n");
  turn = 0;

  while (turn != 1){ printf("while loop p1\n"); }
  printf("critical section p1\n");
  turn = 1;

  return 0;
}
