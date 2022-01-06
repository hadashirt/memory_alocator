#include "my_mem.c"
#include <stdlib.h>

// check to make sure node is inserted
struct Node *head;
int main(void) {
  struct Node *head;
  unsigned char *mem_add = head->mem_add_head;
  push(&head, mem_add, 10);
  push(&head, mem_add, 20);
  printf("%d\n", head->size);
  printf("%x\n", head->mem_add_head);
  printf("%d\n", head->next->size);
  printf("%x\n", head->next->mem_add_head);
}