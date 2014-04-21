#ifndef STR_TO_INT_H_
#define STR_TO_INT_H_

#include <climits>
#include "Utils.h"


int strToInt(const char* str) {
  int cur;
  int ret = 0;
  if (str == NULL)
    return 0;
  const char* digit = str;

  int sign = 1;

  while(isspace_(*digit)) {
    ++digit;
  }

  if (*digit == '+') {
    ++digit;
  } else if (*digit == '-') {
    ++digit;
    sign = -1;
  }

  while (isdigit_(*digit)) {
    cur = *digit - '0';
    if (sign > 0 && (ret > M_MAX_DIV ||
          (ret == M_MAX_DIV && cur >= M_MAX_R))) {
      return M_INT_MAX;
    } else if (sign < 0 && (ret > M_MIN_DIV ||
          (ret == M_MIN_DIV && cur >= M_MIN_R))) {
      return M_INT_MIN;
    }

    ret = ret * 10 + cur;
    ++digit;
  }
  return sign > 0 ? ret : -ret;
}

#endif  // STR_TO_INT_H_
