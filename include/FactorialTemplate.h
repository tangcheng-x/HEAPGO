#ifndef FACTORIAL_TEMPLATE_H_
#define FACTORIAL_TEMPLATE_H_

template <unsigned n>
struct Factorial {
  enum { value = n * Factorial<n-1>::value };
};

template <>
struct Factorial<0> {
  enum { value = 1 };
};

#endif  // FACTORIAL_TEMPLATE_H_
