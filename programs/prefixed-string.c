/* Simple implementation of prefix length strings. In C, strings have the null terminator that tells the program where
 * a string ends. This implementation wants to provide a different approach, similar to how pascal handles strings,
 * which defines the length in the first byte of the string. 
 *
 * It is a showcase of functions that allocates and frees memory in C. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Creates a string that has its length prefixed.
 *
 * +-+-----------+
 * |L|My String  |
 * +-+-----------+
 *
 * Where `L` is the size of the following string. */
char* ps_create(char *str, int size) {
  char *mem = malloc(size + 1);

  // First byte of the string is the length of the string.
  mem[0] = size;

  // Set each character of the string after the first byte.
  for (int i = 0; i < size; i++) {
    mem[i + 1] = str[i];
  }
  return mem;
}

/* Prints a string char by char starting from the second byte and iterating
 * until reaching the size declared in the first byte. */
void ps_print(char *str) {
  int len = str[0];

  for (int i = 1; i <= len; i++) {
    putchar(str[i]);
  }
}

/* Frees the memory allocated by the string. */
void ps_free(char *str) {
  free(str);
}

/* Interestingly, this approach to defining strings has the nice side effect
 * of allowing a size_of function with O(1) complexity instead of the classic O(n). */
int ps_size(char *str) {
  return str[0];
}

int main(void) {

  char *mystr = ps_create("Hello\000 World", 12);
  printf("Created a string of %d size\n", ps_size(mystr));

  ps_print(mystr);
  ps_free(mystr);
  return 0;
}

