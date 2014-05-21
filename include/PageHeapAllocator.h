#ifndef PAGE_HEAP_ALLOCATOR_H_
#define PAGE_HEAP_ALLOCATOR_H_

#include "MallocUtils.h"

template <class T>
class PageHeapAllocator {
 private:
  // Each time get free memory form system size is 128 KB
  static const int kAllocIncrement = 128 << 10;

  // Free area from which to carve new objects
  char* free_area_;
  size_t free_avail_;

  // Free list of alreay carved objects
  void* free_list_;

  // Number of allocated but unfreed objects
  int inuse_;

 public:
  void Init() {
    ASSERT(sizeof(T) < kAllocIncrement);
    inuse_ = 0;
    free_area_ = NULL;
    free_list_ = NULL;
    free_avail_ = 0;
  }

  T* New() {
    void* result;
    if (free_list_ != NULL) {
      
    }
  }
};  // class PageHeapAllocator

#endif  // PAGE_HEAP_ALLOCATOR_H_
