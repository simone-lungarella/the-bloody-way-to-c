#include <stdio.h>

int sum(int a, int b) {
  return a + b;
}

int main(void) {
  int a = 10;
  int c = 20;

  printf("Hello World %d\n", sum(a, c));
  return 0;
}
