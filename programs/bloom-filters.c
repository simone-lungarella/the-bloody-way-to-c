/* Simple bloom filter implementation base on a 8-bit filters and 8 very simple hashing functions. */
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/* Simple 8-bit field use to set and check presence bit. */
uint8_t filter = 0b00000000;

/* Hashing function that return 1 or 0 to encode the first bit composing the filter.
 * Sums all digits as integers and returns 1 if the number is odd. Returns 0 if the sum is even. */
int hash_bit_1(char *value) {

  int summed = 0;
  for (int i = 0; i < strlen(value); i++) {
    summed += value[i];
  }

  return (summed % 2) == 0;
}

/* Hashing function that return 1 or 0 to encode the second bit composing the filter. */
int hash_bit_2(char *value) { return 1; }

/* Hashing function that return 1 or 0 to encode the third bit composing the filter. */
int hash_bit_3(char *value) { return 1; }

/* Hashing function that return 1 or 0 to encode the fourth bit composing the filter. */
int hash_bit_4(char *value) { return 1; }

/* Hashing function that return 1 or 0 to encode the fifth bit composing the filter. */
int hash_bit_5(char *value) { return 1; }

/* Hashing function that return 1 or 0 to encode the sixth bit composing the filter. */
int hash_bit_6(char *value) { return 1; }

/* Hashing function that return 1 or 0 to encode the seventh bit composing the filter. */
int hash_bit_7(char *value) { return 1; }

/* Hashing function that return 1 or 0 to encode the eighth bit composing the filter. */
int hash_bit_8(char *value) { return 1; }


/* Updates filter with the newly added item.
 * Applies an hashing function to encode each of the 8 bits composing the filter. */
void bf_add(char *value) {
  if (hash_bit_1(value)) {
    filter |= (1 << 0);
  }
  if (hash_bit_2(value)) {
    filter |= (1 << 1);
  }
  if (hash_bit_3(value)) {
    filter |= (1 << 2);
  }
  if (hash_bit_4(value)) {
    filter |= (1 << 3);
  }
  if (hash_bit_5(value)) {
    filter |= (1 << 4);
  }
  if (hash_bit_6(value)) {
    filter |= (1 << 5);
  }
  if (hash_bit_7(value)) {
    filter |= (1 << 6);
  }
  if (hash_bit_8(value)) {
    filter |= (1 << 7);
  }
}

/* Returns 1 if the value probably exists on the set by checking each hashing function
 * over the value. If no hashing value return zero, the value probably exists in the set.
 * Returns 0 if it does no exists. */
int bf_exists(char *value) {
  if (hash_bit_1(value) && !(filter & (1 << 0))) return 0;
  if (hash_bit_2(value) && !(filter & (1 << 1))) return 0;
  if (hash_bit_3(value) && !(filter & (1 << 2))) return 0;
  if (hash_bit_4(value) && !(filter & (1 << 3))) return 0;
  if (hash_bit_5(value) && !(filter & (1 << 4))) return 0;
  if (hash_bit_6(value) && !(filter & (1 << 5))) return 0;
  if (hash_bit_7(value) && !(filter & (1 << 6))) return 0;
  if (hash_bit_8(value) && !(filter & (1 << 7))) return 0;

  return 1;
}

/* Prints the filter bit by bit in a human readable format. */
void print_filter() {
  for (int i = 7; i >= 0; i--) {
    printf("%d", (filter >> i) & 1);
  }
  printf("\n");
}

int main(void) {

  bf_add("Banana");

  if (!bf_exists("Ananas")) {
    printf("Item does not exists (correct)\n");
  }

  bf_add("Ananas");

  if (bf_exists("Ananas")) {
    printf("Item probably exists (correct)\n");
  }

  if (bf_exists("Avocado")) {
    printf("Item probably exists (false positive)\n");
  }

  return 0;
}
