#include <stdio.h>

int *front;
int end;
int *offset;

void mem_init(unsigned char *my_memory, unsigned int my_mem_size) {
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
}
void *my_malloc(unsigned size) {
  /*pass the memory size and move the offset pointer to accomodate your size of
   * memory*/
  /*point to the begining of the variable*/
  int *header = offset;
  /* at the offset have a variable that tells you how big the memory is*/
  int var_size = size;
  /* set the adress of var size to be the same as header so that header is
   * pointng to the size */
  header = &var_size;
  offset += var_size + sizeof(int);
};
void my_free(void *mem_pointer) {
  /*pass a pointer that is pointing to memory where the memory is , the header
  should show you how big the data is in the part of the stack, move the offset
  pointer back depending on size of the variable*/
  /* need the value of mem_pointer minus size of int, which would be the
   * header*/
  int free_space = *mem_pointer - sizeof(int);
  /* moveoffset back the amt of free space*/
  offset -= free_space + sizeof(int)
};
void mem_get_stats(mem_stats_ptr mem_stats_ptr) {

  mem_stats_ptr typedef struct {
    int num_blocks_used;
    int num_blocks_free;
    int smallest_block_free;
    int smallest_block_used;
    int largest_block_free;
    int largest_block_used;
  };
  mem_stats_struct, *mem_stats_ptr;
};
