#include <gtest/gtest.h>

#include "../include/SimpleFunction.hpp"

TEST(strstrTest, find) {
  const char* s1 = "abcdef";
  const char* s2 = "cde";
  EXPECT_EQ(3, myStrstr(s1, s2));
}

TEST(strstrTest, nonFind) {
  const char* s1 = "abcdef";
  const char* s2 = "jk";
  EXPECT_EQ(-1, myStrstr(s1, s2));
}

TEST(findNoRepeatTest, find) {
  const char* s = "abcdeabc";
  EXPECT_EQ(3, findNoRepeat(s));
}

TEST(strcpyTest, copy) {
  const char* s = "abcde098";
  char dest[8];
  char* ret =  myStrcpy(dest, s);
  for (int i = 0; i < strlen(s); ++i) {
    EXPECT_EQ(ret[i], s[i]);
  }
}

TEST(strchrTest, find) {
  const char* s = "abcdefgcde";
  const char c = 'e';
  EXPECT_EQ(4, myStrchr(s, c));
}

TEST(testFindNum, inArray) {
  int a[11] = {1,3,4,3,5,5,3,3,3,6,3};
  EXPECT_EQ(3, findNum(a, 11));
}

TEST(testStrToInt, getValue) {
  const char* str = "-123456";
  int num = 0;
  EXPECT_EQ(true, strToInt(str,num));
  EXPECT_EQ(-123456, num);
}

TEST(testStrInt, notGet) {
  const char* str1 = "123a8";
  int num = 0;
  EXPECT_EQ(false, strToInt(str1, num));
}
int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
