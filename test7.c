#include "my_mem.c"
#include <stdlib.h>

// check to make sure node is inserted
struct Node *head;
int main(void) {
  struct Node *head;
  unsigned char *mem_add = head->mem_add_head;
  push(&head, mem_add, 10);
  printf("%d\n", head->size);
  printf("%x\n", head->mem_add_head);
}