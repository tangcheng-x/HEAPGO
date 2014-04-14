#include "Sort.h"

void QuickSortBasic::Sort(int input[], const int& length) {
  instric_sort(input, 0, length - 1);
}

void QuickSortBasic::instric_sort(int input[],
                                  int lowIndex,
                                  int highIndex) {
  if (highIndex <= lowIndex)
    return;
  int partIndex = partition(input, lowIndex, highIndex);

  instric_sort(input, lowIndex, partIndex - 1);
  instric_sort(input, partIndex + 1, highIndex);
}


int QuickSortBasic::partition(int input[],
                              int lowIndex,
                              int highIndex) {
  int i = lowIndex;
  int pivotIndex = lowIndex;
  int j = highIndex + 1;

  while (true) {
    while (input[++i] < input[pivotIndex]) {
      if (i == highIndex)
        break;
    }
    while (input[pivotIndex] < input[--j]) {
      if (j == lowIndex)
        break;
    }

    if (i >= j) break;
    swap_int(input[i], input[j]);
  }

  swap_int(input[pivotIndex], input[j]);
  return j;
}


void QuickSort3Way::Sort(int input[], const int& length) {
  QuickSort3Way::instric_sort(input, 0, length - 1);
}

void QuickSort3Way::instric_sort(int input[], int lowIndex, int highIndex) {
  if (highIndex <= lowIndex)
    return;
  int lt = lowIndex;
  int gt = highIndex;
  int i = lowIndex + 1;

  int pivotIndex = lowIndex;
  int pivotValue = input[pivotIndex];
  while (i <= gt) {
    if (input[i] < pivotValue) {
      swap_int(input[i++], input[lt++]);
    } else if (pivotValue < input[i]) {
      swap_int(input[i], input[gt--]);
    } else {
      i++;
    }
  }

  instric_sort(input, lowIndex, lt - 1);
  instric_sort(input, gt + 1, highIndex);
}

