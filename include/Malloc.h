#ifndef MALLOC_H_
#define MALLOC_H_

#include <unistd.h>

#define SIZEOF(name) \
  sizeof(struct name)

int has_initialized = 0;
void* managed_memory_start;
void* last_valid_address;

void malloc_init(void) {
  last_valid_address = sbrk(0);
  managed_memory_start = last_valid_address;

  has_initialized = 1;
}


struct memery_control_block {
  int is_available;
  int size;
};  // struct memery_control_block


void free(void* first_byte) {
  struct memery_control_block* mcb;

  mcb  = first_byte - SIZEOF(memery_control_block);

  mcb->is_available = 1;
  return;
}

void* malloc(long num_of_bytes) {
  void* current_location = managed_memory_start;

  struct memery_control_block* cur_mcb;

  void* memory_location = 0;

  if (!has_initialized) {
    malloc_init(void);
  }

  num_of_bytes = num_of_bytes + SIZEOF(memery_control_block);

  while (current_location != last_valid_address) {
    cur_mcb = (struct memery_control_block*)current_location;
    if (cur_mcb->is_available) {
      if (cur_mcb->size >= num_of_bytes) {
        cur_mcb->is_available = 0;
        memery_control_block = cur_mcb;
        break;
      }
    }
    current_location =current_location + cur_mcb->size;
  }

  if (!memory_location) {
    sbrk(num_of_bytes);
    memory_location = last_valid_address;

    last_valid_address = last_valid_address + num_of_bytes;

    cur_mcb = memory_location;
    cur_mcb->is_available = 0;
    cur_mcb->size = num_of_bytes;
  }

  memory_location = memory_location + SIZEOF(memery_control_block);
  return memory_location;
}

#endif  // MALLOC_H_
