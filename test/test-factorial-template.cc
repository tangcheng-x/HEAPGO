#include "../include/FactorialTemplate.h"

#include <gtest/gtest.h>

TEST(testFactorial, check) {
  EXPECT_EQ(120, Factorial<5>::value);
  EXPECT_EQ(3628800, Factorial<10>::value);
  EXPECT_EQ(1, Factorial<0>::value);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
