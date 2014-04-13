#include <iostream>
#include "../include/BigDataSort.h"

int main() {
  generateBigData();
  std::cout << "Generate data.txt" << std::endl;
  std::cout << "Sorting..." << std::endl;
  if (bigDataSort()) {
    DEBUG_STDOUT("Sort Success");
  } else {
    DEBUG_STDERR("Sort Failed");
  }
  return 0;
}
