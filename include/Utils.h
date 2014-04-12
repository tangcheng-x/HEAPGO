#ifndef UTILS_H_
#define UTILS_H_

#ifndef size_t
#include <cstddef>
#endif

#ifndef NULL
#define NULL 0
#endif

#ifndef CHECK
#include <assert.h>
#define CHECK(exp) \
  assert(exp)
#endif

#endif  // UTILS_H_
