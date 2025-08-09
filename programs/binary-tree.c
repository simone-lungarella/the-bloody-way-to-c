/* Showcases a simple binary tree implementation making use of `malloc` and `free`
 * and a defined strcuture: node. */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Define a single node of the tree. */
struct node {
  struct node *left;
  struct node *right;
  int value;
};

/* Inserts a value as a node in the right branch of the tree. */
void bt_insert(struct node *root, int value) {
  if (root == NULL) { return; }

  if (value < root->value) {
    printf("Found value to insert to the left\n");
    if (root->left == NULL) { 
      struct node *new_node = malloc(sizeof(struct node));
      new_node->left = NULL;
      new_node->right = NULL;
      new_node->value = value;

      root->left = new_node;
    } else {
      bt_insert(root->left, value);
    }
  } else if (value > root->value) {
    printf("Found value to insert to the right\n");
    if (root->right == NULL) { 
      struct node *new_node = malloc(sizeof(struct node));
      new_node->left = NULL;
      new_node->right = NULL;
      new_node->value = value;

      root->right = new_node;
    } else {
      bt_insert(root->right, value);
    }
  } else {
    printf("[Warning] Item with value: %d, already exists\n", value);
  }
}

/* Recursively prints values of the tree, starting from the lower existing value (far left branch). */
void bt_print(struct node *root) {
  if (root == NULL) { return; }

  bt_print(root->left);
  printf("%d ", root->value);
  bt_print(root->right);
}

/* Recursively frees all nodes of the tree. */
void bt_free(struct node *root) {
  if (root == NULL) { return; }

  bt_free(root->left);
  bt_free(root->right);
  free(root);
}

int main(void) {
  struct node *root = malloc(sizeof(struct node));
  root->left = NULL;
  root->right = NULL;
  root->value = 10;

  bt_insert(root, 15);
  bt_print(root);

  bt_free(root);

  return 0;
}
