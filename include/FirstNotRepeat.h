#ifndef FIRST_NOT_REPEAT_CHAR_H_
#define FIRST_NOT_REPEAT_CHAR_H_

#include <cstring>

char firstNotRepeatCharByArray(char* str) {
  int data[256];
  char* p;
  
  if (str == NULL)
    return '\0';

  memset(data, 0, sizeof(data));

  p = str;
  while (*p != '\0') {
    int index = *p - 'a';
    ++data[index];
    ++p;
  }

  while (*str != '\0') {
    int index = *str - 'a';
    if (data[index] == 1)
      return *str;
    ++str;
  }

  return '\0';
}


#endif  // FIRST_NOT_REPEAT_CHAR_H_
