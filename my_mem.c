#include <stdio.h>
#include <stdlib.h>
/*global variables*/
int total_mem_size;
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
typedef struct Node {
  int data;
  struct Node *next;
  struct Node *prev;
  unsigned char *mem_add_head;
} free_list, used_list;
free_list *head_free = NULL;
used_list *head_used = NULL;

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
  head_free->mem_add_head = my_memory + sizeof(struct Node);
  head_free->data = my_mem_size;
  head_free->next = NULL;
  /*initialize the used list as empty*/
  head_used->mem_add_head = NULL;
  head_used->data = 0;
  head_used->next = NULL;

  cur_mem_used = sizeof(struct Node);
  total_mem_size = my_mem_size;
};
void *my_malloc(unsigned size) {
  /*pass the memory size and move the offset pointer to accomodate your size of
   * memory*/
  /*check if there is enough space in free for size*/
  if (size + cur_mem_used > total_mem_size) {
    fprintf(stderr, " Error: not enough free memory ");
    exit(-1);
  }
  /*if there is enough space continue:*/
  while (head_free->next != NULL) {
    if (head_free->data >= size) {
      head_used->mem_add_head = head_free->mem_add_head;
      head_free->mem_add_head =
          head_free->mem_add_head + size + sizeof(struct Node);
      head_used->data = size + sizeof(struct Node);
    }
  }
  /*increment cur mem by size and size of header*/
  cur_mem_used += size + sizeof(struct Node);
  /*increment number of blocks used*/
  mem_stats_s.num_blocks_used += 1;
  /* if all the space is used set the num of free blocks to 0*/
  if (cur_mem_used == total_mem_size) {
    mem_stats_s.num_blocks_free = 0;
  }
  /* change the smallest free block to the new size of the free block*/
  mem_stats_s.smallest_block_free = total_mem_size - cur_mem_used - sizeof(int);
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
  mem_stats_s.largest_block_free = total_mem_size - cur_mem_used - sizeof(int);
  /*check if this block is the largest*/
  if ((size > mem_stats_s.largest_block_used) && (size > prevBiggestHeader)) {
    prevBiggestHeader = mem_stats_s.largest_block_used;
    mem_stats_s.largest_block_used = size;
  } else if ((size < mem_stats_s.largest_block_used) &&
             (size > prevBiggestHeader)) {
    prevBiggestHeader = size;
  }
  /*return pointer to the size of that insert*/
  return head_used->mem_add_head;
};
void my_free(void *mem_pointer) {
  /*pass a pointer that is pointing to memory where the memory is , the header
  should show you how big the data is in the part of the stack, move the offset
  pointer back depending on size of the variable*/
  /*get the size of the space that is being freed*/

  int free_space = *(int *)mem_pointer;

  /* move offset back the amount of free space*/
  offset -= free_space + sizeof(int);

  /*update the cur mem_used*/

  cur_mem_used -= free_space + sizeof(int);

  mem_stats_s.num_blocks_used -= 1;
  mem_stats_s.num_blocks_free = 1;
  /*should I add in an error message here if you cant remove a variable */
  mem_stats_s.smallest_block_free = total_mem_size - cur_mem_used;
  /**/
  if (free_space == mem_stats_s.smallest_block_used) {
    mem_stats_s.smallest_block_used = prevSmallestHeader;
  }
  mem_stats_s.largest_block_free = total_mem_size - cur_mem_used;
  /**/
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
