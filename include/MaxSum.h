#ifndef MAX_SUM_H_
#define MAX_SUM_H_

int maxSum(const int* a, int n) {
  int sum = a[0];
  int temp = 0;

  for (int i = 0; i < n; ++i) {
    if (temp < 0)
      temp = a[i];
    else
      temp += a[i];
    if (sum < temp)
      sum = temp;
  }

  return sum;
}

#endif  // MAX_SUM_H_
