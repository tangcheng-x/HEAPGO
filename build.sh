#!/bin/bash

g++ -o bin/test-simple-function test/test-simple-function.cc  -lpthread -lgtest
g++ -o bin/test-find-sum test/test-find-sum.cc -lpthread -lgtest
g++ -o bin/test-big-data-sort test/test-big-data-sort.cc
g++ -o bin/test-k-way-extern-sort  test/test-k-way-extern-sort.cc \
  include/K-WayExternSort/K-WayExternSort.cc -Xlinker -zmuldefs

g++ -o bin/test-quick-sort-basic test/test-quick-sort-basic.cc \
  include/Sort.cc -lpthread -lgtest -Xlinker -zmuldefs

g++ -o bin/test-quick-sort-3way test/test-quick-sort-3way.cc \
  include/Sort.cc -lpthread -lgtest -Xlinker -zmuldefs

g++ -o bin/test-max-sum test/test-max-sum.cc -lpthread -lgtest

g++ -o bin/test-str-to-int test/test-str-to-int.cc -lpthread -lgtest

g++ -o bin/test-factorial-template test/test-factorial-template.cc -lpthread \
  -lgtest
