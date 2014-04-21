#ifndef UTILS_H_
#define UTILS_H_

#include <assert.h>
#include <cstdio>
#include <cstring>
#ifndef size_t
#include <cstddef>
#endif

#ifndef NULL
#define NULL 0
#endif

#ifndef CHECK
#define CHECK(exp) \
  assert(exp)
#endif

#define PRINT_AND_EXIT(ARGS_LIST)  \
  do { printf ARGS_LIST; exit(EXIT_FAILURE); } while (0)

        
#define PLEASE_EMAIL_DAVIN "Please email sysutcheng@gmail.com: \n\n"

#define ASSERT(test)       \
 do {                      \
   if (!(test)){           \
   PRINT_AND_EXIT((PLEASE_EMAIL_DAVIN \
                   "*** Assertion failed at (%s:%d)\n\n"   \
                   "*** TEST: %s\n",                         \
                   __FILE__,                                \
                   __LINE__,                                \
                   #test));                                 \
   }                                                       \
 }  while(0)

#ifdef DEBUG
#define DEBUG_STDERR(x) (std::cerr << (x) << std::endl)
#define DEBUG_STDOUT(x) (std::cout << (x) << std::endl)
#else
#define DEBUG_STDERR(x)
#define DEBUG_STDOUT(x)
#endif

#define LOG_OUT(args...) \
  fprintf(stdout, args)

void swap_int(int& a, int& b) {
  int temp(a);
  a = b;
  b = temp;
}

static const int M_INT_MAX = (int)((unsigned)~0 >> 1);
static const int M_INT_MIN = -(int)((unsigned)~0 >> 1) - 1;
static const int M_MAX_DIV = (int)((unsigned)~0 >> 1) / 10;
static const int M_MIN_DIV = (int)((((unsigned)~0 >> 1) + 1) / 10);
static const int M_MAX_R = (int)((unsigned)~0 >> 1) % 10;
static const int M_MIN_R = (int)((((unsigned)~0 >> 1) + 1) % 10);


static int isspace_(int x) {
  if (x == ' ' || x == '\t' || x == '\f' ||
      x == '\n' || x == '\r' || x == '\b')
    return 1;
  return 0;
}


static int isdigit_(int x) {
  if ( x <= '9' && '0' <= x)
    return 1;
  return 0;
}


#endif  // UTILS_H_
