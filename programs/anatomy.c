/* #include tells to the compiler to copy the content of other files. 
 * In this case the copied files has the signature of `printf` which is required 
 * from the compiler since the main function uses it. */
#include <stdio.h>

/* Sums two parameters which are variables of type `int`.
 * When the function returns the result, `a` and `b` are removed from the stack. */
int sum(int a, int b) {
  return a + b;
}

/* The main function is automatically called when the program start. */
int main(void) {
  /* These variables have a local scope, can have the same name of other function's local variables. */
  int a = 10;
  int c = 20;

  /* A function can call other functions. */
  printf("Hello World %d\n", sum(a, c));

  /* Each function must return a value if defined in its signature. */
  return 0;
}
