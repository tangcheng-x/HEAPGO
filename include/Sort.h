#ifndef SORT_H_
#define SORT_H_

#include "Utils.h"

// ----------------------------------------------------------------------------
// QuickSortBasic
//
// This is the tranditional quick sort implementation
//
class QuickSortBasic {
 public:
  void Sort(int input[], const int& length);
 private:
  void instric_sort(int input[], int startIndex, int endIndex);
  int partition(int input[], int startIndex, int endIndex);
};  // class QuickSortBasic

// ----------------------------------------------------------------------------
// QuickSort3Way
//
// This is the quick sort with 3 way mode
//
class QuickSort3Way {
 public:
  void Sort(int input[], const int& length);
 private:
  void instric_sort(int input[], int startIndex, int endIndex);
};  // class QuickSort3Way

#endif  // SORT_H_
