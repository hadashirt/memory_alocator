#include "my_mem.c"
#include <stdlib.h>

/*remove something that is not there */
int main(int argc, char **argv) {
  unsigned int global_mem_size = 50 * 50;
  unsigned char *global_memory = malloc(global_mem_size);

  mem_init(global_memory, global_mem_size);

  print_stats("init");

  unsigned char *ptr_array[10];
  unsigned int sizes[] = {30, 40, 60, 0};

  for (int i = 0; sizes[i] != 0; i++) {
    char buf[50];
    ptr_array[i] = my_malloc(sizes[i]);

    sprintf(buf, "after iteration %d size %d", i, sizes[i]);
    print_stats(buf);
  }

  my_free(ptr_array[2]);
  print_stats("after free #1");
  my_free(ptr_array[0]);
  print_stats("after free #2");
  my_free(ptr_array[1]);
  print_stats("after free #3");
  // this was already removed
  my_free(ptr_array[2]);
  print_stats("after free #1");
}