#ifndef BIG_DATA_SORT_H_
#define BIG_DATA_SORT_H_
#include <iostream>
#include <cstdio>
#include <bitset>
#include <ctime>
#include <cstdlib>
#include "Utils.h"


const int MaxSearchNum = 500000;
const int MaxSize = 1000000;

int num[MaxSize];


void generateBigData() {
  FILE* fp = fopen("../data/data.txt", "w");
  CHECK(fp);

  for (int i = 0; i < MaxSize; ++i) {
    num[i] = i+1;
  }

  srand((unsigned)time(NULL));

  int a, b;
  for (int i = 0; i < MaxSize; ++i) {
    a = rand() % 1000000;
    b = rand() % 1000000;
    swap_int(num[a], num[b]);
  }

  for (int i = 0; i < MaxSize; ++i) {
    fprintf(fp, "%d ", num[i]);
  }

  fclose(fp);
}



bool bigDataSort() {
  std::bitset<MaxSearchNum> bit_map;

  FILE* unsort_data_fp = fopen("../data/data.txt", "r");
  CHECK(unsort_data_fp);
  
  int num;
  while (fscanf(unsort_data_fp, "%d", &num) != EOF) {
    if (num < MaxSearchNum)
      bit_map.set(num, 1);
  }

  FILE* sorted_data_fp = fopen("../data/sort.txt", "w");
  CHECK(sorted_data_fp);

  for (int i = 0; i < MaxSearchNum; ++i) {
    if (bit_map[i] == 1)
      fprintf(sorted_data_fp, "%d ", i);
  }

  int ret = fseek(unsort_data_fp, 0, SEEK_SET);
  if (ret) {
    DEBUG_STDERR("fseek failed!");
    return false;
  }
  bit_map.reset();
  while (fscanf(unsort_data_fp, "%d", &num) != EOF) {
    if (num >= MaxSearchNum && num < 1000000) {
      num -= MaxSearchNum;
      bit_map.set(num, 1);
    }
  }
  for (int i = 0; i < MaxSearchNum; ++i) {
    if (bit_map[i] == 1) {
      fprintf(sorted_data_fp, "%d ", i + MaxSearchNum);
    }
  }

  fclose(unsort_data_fp);
  fclose(sorted_data_fp);
  return true;
}
#endif  // BIG_DATA_SORT_H_
