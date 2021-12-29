#include <stdio.h>

int *front;
int end;
int *offset;
int total_mem_size;
int cur_mem_used;

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

void mem_init(unsigned char *my_memory, unsigned int my_mem_size) {
  /*pointer pointing to the struct*/
  mem_stats_p = &mem_stats_s;
  mem_stats_s.num_blocks_used = 0;
  mem_stats_s.num_blocks_free = 1;
  mem_stats_s.smallest_block_free = my_mem_size;
  mem_stats_s.smallest_block_used = 0;
  mem_stats_s.largest_block_free = my_mem_size;
  mem_stats_s.largest_block_used = 0;
  /*memory size and where it will start , create a stack , first pointer and
  offset pointer to
  keep track as to where it ends, set them to equal bc no data in the function*/
  /* pointer to the begining of the stack*/
  int *front = 0;
  /*size of the stack*/
  int end = my_mem_size;
  /*pointer to the offset of the stack*/
  int *offset = 0;
  /* keep track of smallest block*/
  int smallestHeader = 0;
  /*keep track of biggest block*/
  int biggestHeader = 0;
  /*set total memory size*/
  total_mem_size = my_mem_size;
  /*set current memory size*/
  cur_mem_used = 0;
};
void *my_malloc(unsigned size) {
  /*pass the memory size and move the offset pointer to accomodate your size of
   * memory*/
  /*point to the begining of the variable*/
  int *header = offset;
  /* at the offset have a variable that tells you how big the memory is*/
  int var_size = size;
  /*increment cur mem by size and size of header*/
  cur_mem_used += size + sizeof(int);
  /* set the adress of var size to be the same as header so that header is
   * pointng to the size */
  header = &var_size;
  offset += var_size + sizeof(int);

  mem_stats_s.num_blocks_used += 1;
  if (cur_mem_used == total_mem_size) {
    mem_stats_s.num_blocks_free = 0;
  }
  if (cur_mem_used > total_mem_size) {
    printf("%s\n", "Error,not enough free memory");
  }
  mem_stats_s.smallest_block_free = total_mem_size - cur_mem_used;
  /*check if this block is the smallest*/
  if (*header < mem_stats_s.smallest_block_used) {
    mem_stats_s.smallest_block_used = size;
  }
  mem_stats_s.largest_block_free = total_mem_size - cur_mem_used;
  /*check if this block is the largest*/
  if (*header > mem_stats_s.largest_block_used) {
    mem_stats_s.largest_block_used = size;
  }
};
void my_free(void *mem_pointer) {
  /*pass a pointer that is pointing to memory where the memory is , the header
  should show you how big the data is in the part of the stack, move the offset
  pointer back depending on size of the variable*/
  /* need the value of mem_pointer minus size of int, which would be the
   * header*/
  int free_space = sizeof(mem_pointer);
  /* moveoffset back the amt of free space*/
  offset -= free_space + sizeof(int);
  /*how to change the stats of the free*/
  cur_mem_used -= free_space;
  mem_stats_s.num_blocks_used -= 1;
  mem_stats_s.num_blocks_free = 1;
  /*should I add in an error message here if you cant remove a variable */
  mem_stats_s.smallest_block_free = total_mem_size - cur_mem_used;
  /*find the smallest, with a pointer?*/
  if () {
    mem_stats_s.smallest_block_used = ;
  }
  mem_stats_s.largest_block_free = total_mem_size - cur_mem_used;
  /*find the largest block, with a pointer?*/
  if () {
    mem_stats_s.largest_block_used = ;
  }
};
void mem_get_stats(mem_stats_ptr mem_stats_ptr) {
  mem_stats_struct mem_struct = *mem_stats_ptr;
  printf("%d\n", mem_struct.num_blocks_used);
  printf("%d\n", mem_struct.num_blocks_free);
  printf("%d\n", mem_struct.smallest_block_free);
  printf("%d\n", mem_struct.smallest_block_used);
  printf("%d\n", mem_struct.largest_block_free);
  printf("%d\n", mem_struct.largest_block_used);
};
