#include "../include/StrToInt.h"

#include <gtest/gtest.h>

TEST(testStrToInt, testValue) {
  const char* s1 = "    -123";
  const char* s2 = "123bg";
  const char* s3 = "123456789012345";
  const char* s4 = "-123456789012345";
  const char* s5 = "123 456";
  
  EXPECT_EQ(-123, strToInt(s1));
  EXPECT_EQ(123, strToInt(s2));
  EXPECT_EQ(INT_MAX, strToInt(s3));
  EXPECT_EQ(INT_MIN, strToInt(s4));
  EXPECT_EQ(123, strToInt(s5));
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
