#include <stdio.h>
#include <stdlib.h>
/*global variables*/
int total_mem_size;
// keep track of current memory being used
int cur_mem_used;
/* keep track of prev smallest block*/
int prevSmallestHeader = 0;
/*keep track of prev biggest block*/
int prevBiggestHeader = 0;
int prev_size;
typedef struct {
  int num_blocks_used;
  int num_blocks_free;
  int smallest_block_free;
  int smallest_block_used;
  int largest_block_free;
  int largest_block_used;
} mem_stats_struct, *mem_stats_ptr;

mem_stats_ptr mem_stats_p;
mem_stats_struct mem_stats_s;

/*initialize the linked list */
// A linked list node
struct Node {
  int size;
  unsigned char *mem_add_head;
  struct Node *next;
  struct Node *prev;
};
// used and free list
struct Node *head_free = NULL;
struct Node *head_used = NULL;
void push(struct Node **head_ref, unsigned char *mem_add_head, int new_data) {
  /* 1. allocate node */
  struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));

  /* 2. put in the data  */
  new_node->size = new_data;
  new_node->mem_add_head = mem_add_head;

  /* 3. Make next of new node as head */
  new_node->next = (*head_ref);

  /* 4. move the head to point to the new node */
  (*head_ref) = new_node;
}
void deleteNode(struct Node **head_ref, int key, unsigned char *mem_add_head) {
  // Store head node
  struct Node *temp = *head_ref, *prev;

  // If head node itself holds the key to be deleted
  if (temp != NULL && temp->size == key) {
    *head_ref = temp->next; // Changed head
    free(temp);             // free old head
    return;
  }

  // Search for the key to be deleted, keep track of the
  // previous node as we need to change 'prev->next'
  while (temp != NULL && temp->size != key) {
    prev = temp;
    temp = temp->next;
  }

  // If key was not present in linked list
  if (temp == NULL)
    return;

  // Unlink the node from linked list
  prev->next = temp->next;

  free(temp); // Free memory
}

void mem_init(unsigned char *my_memory, unsigned int my_mem_size) {
  /*pointer pointing to the struct*/
  mem_stats_p = &mem_stats_s;
  mem_stats_s.num_blocks_used = 0;
  mem_stats_s.num_blocks_free = 1;
  mem_stats_s.smallest_block_free = my_mem_size;
  mem_stats_s.smallest_block_used = 0;
  mem_stats_s.largest_block_free = my_mem_size;
  mem_stats_s.largest_block_used = 0;

  /* pointer to the begining of the linked list free, the mem adress of it */
  head_free = (struct Node *)malloc(sizeof(struct Node));
  head_free->mem_add_head = my_memory;
  head_free->size = my_mem_size;
  head_free->next = NULL;
  head_free->prev = NULL;
  /*initialize the used list as empty*/
  head_used = (struct Node *)malloc(sizeof(struct Node));
  head_used->mem_add_head = NULL;
  head_used->size = 0;
  head_used->next = NULL;
  head_used->prev = NULL;

  cur_mem_used = sizeof(struct Node);
  total_mem_size = my_mem_size;
};
void *my_malloc(unsigned size) {
  /*check if there is enough space in free for size*/
  if (size + cur_mem_used > total_mem_size) {
    fprintf(stderr, " Error: not enough free memory ");
    return NULL;
    exit(-1);
  }
  /*if there is enough space continue:*/
  struct Node *ptr = head_free;
  // temp pointer set to head , as long as ptr is not null ,set the ptr to next
  while (ptr != NULL) {
    if (head_free->size >= size) {
      push(&head_used, head_free->mem_add_head, size);
      deleteNode(&head_free, size, head_free->mem_add_head);
      //  head_used->mem_add_head = head_free->mem_add_head;
      //  head_free->mem_add_head = head_free->mem_add_head - size;
      //  head_used->size = size;
      break;
    }
    ptr = ptr->next;
  }
  /*increment cur mem by size and size of header*/
  cur_mem_used += size;
  /*increment number of blocks used*/
  mem_stats_s.num_blocks_used += 1;
  /* if all the space is used set the num of free blocks to 0*/
  if (cur_mem_used == total_mem_size) {
    mem_stats_s.num_blocks_free = 0;
  }
  /* change the smallest free block to the new size of the free block*/
  mem_stats_s.smallest_block_free = total_mem_size - cur_mem_used;
  /*check if this block is the smallest*/
  if (mem_stats_s.smallest_block_used == 0) {
    mem_stats_s.smallest_block_used = size;
    prevSmallestHeader = size;
  } else if ((size < mem_stats_s.smallest_block_used) &&
             (size < prevSmallestHeader)) {
    prevSmallestHeader = mem_stats_s.smallest_block_used;
    mem_stats_s.smallest_block_used = size;
  } else if ((size > mem_stats_s.smallest_block_used) &&
             (size < prevSmallestHeader)) {
    prevSmallestHeader = size;
  }
  /* change the largest free block to the new size of the free block*/
  mem_stats_s.largest_block_free = total_mem_size - cur_mem_used;
  /*check if this block is the largest*/
  if ((size > mem_stats_s.largest_block_used) && (size > prevBiggestHeader)) {
    prevBiggestHeader = mem_stats_s.largest_block_used;
    mem_stats_s.largest_block_used = size;
  } else if ((size < mem_stats_s.largest_block_used) &&
             (size > prevBiggestHeader)) {
    prevBiggestHeader = size;
  }
  /*return pointer to the memory location of the insert*/

  return head_used->mem_add_head;
};

void my_free(void *mem_pointer) {
  /*find the node that  is being removed and change the pointer of mem adress to
   * the free list  */
  struct Node *ptr = head_used;

  while (ptr != NULL) {
    if (head_used->mem_add_head == mem_pointer) {
      push(&head_free, head_used->mem_add_head, head_used->size);
      deleteNode(&head_used, head_used->size, head_used->mem_add_head);

      // head_free->mem_add_head = mem_pointer;
      // head_used->mem_add_head = mem_pointer += ptr->size;
      // head_used->next = NULL;
      break;
    }
    head_used = head_used->next;
    ptr = ptr->next;
    // if the node is not there return NULL
    if (ptr == NULL) {
      printf("%s\n", "Value not there");
      exit(-1);
    }
  }
  // set the size of the space being freed
  int free_space = head_free->size;
  int free = free_space;

  /*update the cur mem_used*/
  cur_mem_used -= free_space;
  if (mem_stats_s.num_blocks_used == 0) {
    printf("%s\n", "Value not there");
    exit(-1);
  }
  mem_stats_s.num_blocks_used -= 1;
  mem_stats_s.num_blocks_free += 1;
  if (free_space < mem_stats_s.smallest_block_free) {
    mem_stats_s.smallest_block_free = free_space;
  }
  if (free_space == mem_stats_s.smallest_block_used) {
    mem_stats_s.smallest_block_used = prevSmallestHeader;
  }
  if (free_space > mem_stats_s.largest_block_free) {
    mem_stats_s.largest_block_free =
        free_space; // total_mem_size - cur_mem_used;
  }

  if (free_space == mem_stats_s.largest_block_used) {
    mem_stats_s.largest_block_used = prevBiggestHeader;
  }
  if (mem_stats_s.num_blocks_used == 0) {
    mem_stats_s.smallest_block_used = 0;
    mem_stats_s.largest_block_used = 0;
  }
};
void mem_get_stats(mem_stats_ptr mem_stats_ptr) {
  mem_stats_struct mem_struct = *mem_stats_ptr;
};
void print_stats(char *prefix) {
  mem_get_stats(&mem_stats_s);
  printf("mem stats: %s: %d free blocks, %d used blocks, free blocks: "
         "smallest=%d largest=%d, used blocks: smallest=%d largest=%d\n",
         prefix, mem_stats_s.num_blocks_free, mem_stats_s.num_blocks_used,
         mem_stats_s.smallest_block_free, mem_stats_s.largest_block_free,
         mem_stats_s.smallest_block_used, mem_stats_s.largest_block_used);
}
