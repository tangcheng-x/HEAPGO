#include <gtest/gtest.h>

#include "../include/FindSum.hpp"

TEST(testFindSumBySqueeze, find) {
  int a[10] = {1,2,3,4,5,6,7,8,9,0};
  std::pair<int,int> p = findSumBySqueeze(a, 10, 15);
  EXPECT_EQ(6, p.first);
  EXPECT_EQ(9, p.second);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
