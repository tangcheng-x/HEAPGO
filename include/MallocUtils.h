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

#define HAVE_TLS 1   // Set support TLS as default

#define HAVE___ATTRIBUTE__ 1

static const size_t kMaxSize = 256 * 1024;
static const size_t kNumClasses = 78;

#ifndef pthread_t
typedef DWORD pthread_t
#endif


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
<<<<<<< HEAD
  return ret;
}


inline void SLL_PushRange(void** head, void* start, void* end) {
  if (!start) return;
  SLL_SetNext(end, *head);
  *head = start;
}

inline void SLL_PopRange(void** head, int n, void** start, void** end) {
  if (n == 0) {
    *start = NULL;
    *end = NULL;
    return;
  }

  void* temp = *head;
  for (int i = 1; i < n; ++i) {
    temp = SLL_Next(temp);
  }

  *start = *head;
  *end = temp;
  *head = SLL_Next(temp);
  SLL_SetNext(temp, NULL);
}

#endif  // MALLOC_UTILS_H_
