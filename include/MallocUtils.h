#ifndef MALLOC_UTILS_H_
#define MALLOC_UTILS_H_

#include <cstdio>

#define __THROW throw()


#define HAVE_TLS 1

#if defined(__LP64__) || defined(_LP64)
#define BUILD_64   1
#endif

#ifndef NULL
#define NULL 0x00
#endif

#undef LOG_OUT
#define LOG_OUT(args...)                                \
  fprintf(stdout, args);


#undef CHECK_CONDITION
#define CHECK_CONDITION(cond)                            \
do {                                                     \
  if (!(cond)) {                                         \
    LOG_OUT("Crashed in %s : %d with condtion:%s",       \
        __FILE__, __LINE__, #cond)                       \
  }                                                      \
} while (0)

#ifndef NDEBUG
#define ASSERT(cond) CHECK_CONDITION(cond)
#else
#define ASSERT(cond) ((void) 0)
#endif



#define UNLIKELY(x) (x)

static const size_t kMaxSize = 256 * 1024;

// Get the free block next to the |t|, and the |t| is a free block too
//+-------------+
//| t |         |
//+-|-----------+
//  |    +--------------+
//  +--->| result       |
//       +--------------+
inline void* SLL_Next(void* t) {
  return *(reinterpret_cast<void**>(t));
}


// Make the first 4 bytes or 8 bytes as a pointer, and make it point to the
// |n|
inline void* SLL_SetNext(void* t, void* n) {
  *(reinterpret_cast<void**>(t)) = n;
}


// Add a free memory block in the fornt of the list
// +-------+  +---------------+
// |list  --->|     |  data   |       
// +-------+  +--|------------+
//               |    +---------------+
//               +--->|     |  data   | 
//                    +--|------------+
//                       |    +---------------+
//                       +--->|     |   data  |
//                            +---------------+
//
inline void SLL_Push(void** list, void* element) {
  SLL_SetNext(element, *list);
  *list = element;
}

inline void* SLL_Pop(void** list) {
  void* ret = *list;
  *list = SLL_Next(*list);
  return result;
}



#endif  // MALLOC_UTILS_H_
