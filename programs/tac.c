/* Simple implementation of `tac`, a CLI tool that prints each line
 * of a file in reverse order. Used to increase understandings on structures. */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct line {
  char *s;
  struct line *next;
};

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Missing file name");
    return 1;
  }

  // Open file in read mode
  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL) {
    printf("File does not exist");
    return 1;
  }

  /* In this example will be ignored all errors relative to string length or malloc
   * for the sake of simplicity. */
  char buf[1024];
  struct line *head = NULL;

  while (fgets(buf, sizeof(buf), fp) != NULL) {
    struct line *l = malloc(sizeof(struct line));
    size_t linelen = strlen(buf);
    l->s = malloc(linelen + 1);

    for (size_t j = 0; j <= linelen; j++) {
      l->s[j] = buf[j];
    }
    l->next = head;
    head = l;
  }

  fclose(fp);

  while (head != NULL) {
    printf("%s", head->s);
    head = head->next;
  }

  return 0;
}
