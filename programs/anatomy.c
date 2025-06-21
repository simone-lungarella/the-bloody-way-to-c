/* #include tells to the compiler to copy the content of other files. 
 * In this case the copied files has the signature of `printf` which is required 
 * from the compiler since the main function uses it. */
#include <stdint.h>
#include <stdio.h>

/* Sums two parameters which are variables of type `int`.
 * When the function returns the result, `a` and `b` are removed from the stack. */
int sum(int a, int b) {
  return a + b;
}

/* Defines a global variable and initialize it to 0. */
int x = 0;

/* Increments the global variable `x` by one. This function does not return any value
 * and does not receive any parameter. */
void incr(void) {
  x = x + 1;

  /* Static variables' values will be retained through multiple function calls. */
  static int y = 0;
  y = y + 1;
}

/* Recursive functions are functions that call themselves. */
void count(int start, int end) {
  if (start > end) return;
  printf("%d\n", start);
  count(start + 1, end);
}

/* The main function is automatically called when the program start. */
int main(void) {
  /* These variables have a local scope, can have the same name of other function's local variables. */
  int a = 10;
  int c = 20;

  /* A function can call other functions. 
   * Local variables: a and c will be passed by value, hence they won't be altered. */
  printf("Hello World %d\n", sum(a, c));

  incr();
  /* The value of the global value will be affected by the previous function call. */
  printf("Value of global variable x: %d", x);

  char val = 127;
  /* In expression evaluation and in variadic functions
   * types are usually promoted to a higher size compatible variant. */
  int new_val = val + 1;
  printf("%d\n", new_val);

  short s = 2000;
  long l = 10;

  /* Since the size of types depends on CPU architecture, 
   * `sizeof` can be used to get the real size in the specific architecture. */
  printf("Size of variable: %lu\n", sizeof(l));

  /* There are many types in C, some of them are related to the specific architecture
   * and guarantee to be usable in some context.
   * The following types guarantee to allocate enough space for a memory address. */
  intptr_t x;
  uintptr_t y;

  /* Arrays can store multiple values of the same type. */
  int array[5] = {1, 2, 3, 4, 5};
  /* Arrays of chars are named "string" and have a special way of initialization.
   * Strings have the null terminator `\0` that tells the program when the array of chars ends. */
  char string[] = "Hello";

  /* Conditional blocks are executed only when a specific condition is met. */
  if (s > 2500) {
    printf("Variable %d is greater than 2500", s);
  } else {
    printf("Variable %d is not greater than 2500", s);
  }

  /* To iterate over the same code block, there are multiple ways. One of the is the `while loop`.
   * This code block will be executed multiple time, until the condition is not met anymore. */
  while(a > 0) {
    printf("");
    a--;
  }

  /* Each function must return a value if defined in its signature. */
  return 0;
}
