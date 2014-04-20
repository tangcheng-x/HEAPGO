#include "../include/FirstNotRepeat.h"

#include <gtest/gtest.h>
#include <iostream>

TEST(firstNotRepeatTest, retChar) {
  char* str = "afaccde";
  EXPECT_EQ('f', firstNotRepeatCharByArray(str));
}


TEST(firstNotRepeatTest, notFind) {
  char* str = "afafccdd";
  EXPECT_EQ('\0', firstNotRepeatCharByArray(str));
}


int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
