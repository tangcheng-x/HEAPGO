#ifndef FIND_SUM_H_
#define FIND_SUM_H_

#include <algorithm>

std::pair<int, int>
findSumBySqueeze(int* s, int n, int x) {
  int* begin = s;
  int* end = s + n - 1;
  std::sort(s, s + n);

  while (begin < end) {
    if (*begin + *end > x) {
      --end;
    } else if (*begin + *end < x) {
      ++begin;
    } else {
      return std::pair<int, int>(*begin, *end);
    }
  }
  return std::pair<int, int>(-1, -1);
}


#endif  // FIN_SUM_H_


