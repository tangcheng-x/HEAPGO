#include <gtest/gtest.h>
#include <iostream>

#include <cstdlib>

#include "../include/Sort.h"

void generateUnsortArray(int arr[], int length) {
  for (int i = 0; i < length; ++i) {
    arr[i] = i+1;
  }

  srand((unsigned)time(NULL));
  for (int i = 0; i < length; ++i) {
    int a = rand() % length;
    int b = rand() % length;
    swap_int(arr[a], arr[b]);
  }
}

TEST(quickSortBasicTest, sort) {
  int arr[12];
  generateUnsortArray(arr, 12);
  QuickSort3Way qsb;
  qsb.Sort(arr, int(12));
  for (int i = 0; i < 12; ++i)
    std::cout << arr[i] << std::endl;
  for (int i = 0; i < 12; ++i)
    EXPECT_EQ(i + 1, arr[i]);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
