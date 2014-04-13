#include "../include/K-WayExternSort/K-WayExternSort.h"

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

const unsigned int count = 10000000;

const int num_in_file = 1000000;

const char* unsort_file_path = "../data/unsort_data.txt";
const char* sorted_file_path = "../data/sorted_data.txt";

void init_data() {
  FILE* fp = fopen(unsort_file_path, "w");
  for (int i = 0; i < count; ++i) {
    fprintf(fp, "%d ", rand());
  }

  fclose(fp);
}

int main() {
  srand((unsigned)time(NULL));
  init_data();
  ExternSort externSort(unsort_file_path, sorted_file_path, num_in_file);
  externSort.Sort();
  return 0;
}
