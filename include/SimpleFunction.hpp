#ifndef SIMPLE_FUNCTION_HPP_
#define SIMPLE_FUNCTION_HPP_

#include "Utils.h"
#include <limits>
#define LETTER_NUM 26

int myStrstr(const char* str, const char* subStr) {
  if (str == NULL || subStr == NULL)
    return -1;
  size_t lenStr = strlen(str);
  size_t lenSubStr = strlen(subStr);

  if (lenStr < lenSubStr)
    return -1;

  size_t len = lenStr - lenSubStr;

  for (size_t i = 0; i <= len; ++i) {
    size_t j = 0;
    for (; j < lenSubStr; ++j) {
      if (str[i + j] != subStr[j])
        break;
    }
    if (j == lenSubStr)
      return i + 1;
  }
  return -1;
}

int findNoRepeat(const char* s) {
  size_t len = strlen(s);
  int bitmap[LETTER_NUM] = {0};
  for (size_t i = 0; i < len; ++i) {
    int index = s[i] - 'a';
    ++bitmap[index];
  }

  for (size_t i = 0; i < len; ++i) {
    if (bitmap[s[i]-'a'] == 1)
      return i;
  }
  return -1;
}

char* myStrcpy(char* dest, const char* s) {
  if (dest == s) return dest;
  CHECK((dest != NULL) && (s != NULL));
  char* ret = dest;
  while ((*dest++ = *s++) != '\0');
  return ret;
}

char* myStrncpy(char* dest, const char* s, unsigned int n) {
  CHECK((dest != NULL) && (s != NULL));
  char* ret = dest;
  while (n-- && *s != '\0')
    *dest++ = *s++;
  *dest = '\0';
  return ret;
}

int myStrchr(const char* str, const char c) {
  CHECK(str != NULL);
  int count = 0;
  while (*str++ != c) {
    if (str == '\0')
      return -1;
    ++count;
  }
  return count;
}

// Find the member of the array which number is biger than half of array length
int findNum(int arr[], int n) {
  int can = -1;
  int times = 0;
  for (int i = 0; i < n; ++i) {
    if (times == 0) {
      can = arr[i];
      times = 1;
    } else {
      if (can != arr[i]) {
        --times;
      } else {
        ++times;
      }
    }
  }
  return can;
}

// Find the member of array which number is equal to the length / 2 of array
int EqualToHalf(int arr[], int n) {
  int can = -1;
  int times = 0;
  int e_times = 0;
  for (int i = 0; i < n; ++i) {
    if (arr[i] == arr[n-1])
      ++e_times;
    if (times == 0) {
      can = arr[i];
      times = 1;
    } else if (arr[i] == can){
      ++times;
    } else {
      --times;
    }
  }
  if ((e_times + 1) == n / 2)
    return arr[n-1];
  else
    return can;
}

#endif  // SIMPLE_FUNCTION_HPP_


