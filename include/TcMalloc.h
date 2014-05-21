#ifndef TC_MALLOC_H_
#define TC_MALLOC_H_

#include "MallocUtils.h"

/*
extern "C" void* tc_malloc(size_t size) __THROW {
  void* result = do_malloc(size);
  return result;
}

inline void* domalloc(size_t size) {
  void* ret = do_malloc_no_errno(size);
  if (UNLIKELY(ret == NULL)) errno = ENOMEM;
  return ret;
}

inline void* do_malloc_no_errno(size_t size) {
  
}
*/
#endif  // TC_MALLOC_H_
