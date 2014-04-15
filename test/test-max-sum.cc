#include <gtest/gtest.h>

#include "../include/MaxSum.h"

TEST(maxSumTest, equal) {
  const int a[5] = {-4, -2, -3, -1,-5};
  int ret = maxSum(a, 5);
  EXPECT_EQ(-1, ret);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
