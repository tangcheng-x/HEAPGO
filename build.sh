#!/bin/bash

g++ -o bin/test-simple-function test/test-simple-function.cc  -lpthread -lgtest
g++ -o bin/test-find-sum test/test-find-sum.cc -lpthread -lgtest
g++ -o bin/test-big-data-sort test/test-big-data-sort.cc
g++ -o bin/test-k-way-extern-sort  test/test-k-way-extern-sort.cc \
  include/K-WayExternSort/K-WayExternSort.cc -Xlinker -zmuldefs
