#include "my_mem.c"
#include <stdlib.h>

// check to make sure node is inserted and that you  can add more then 1 node
struct Node *head;
int main(void) {
  struct Node *head;
  unsigned char *mem_add = head->mem_add_head;
  push(&head, mem_add, 10);
  push(&head, mem_add, 20);
  printf("%d\n", head->size);
  printf("%d\n", head->next->size);
  deleteNode(&head, 10, head->next->mem_add_head);
  printf("%d\n", head->next->size);
}