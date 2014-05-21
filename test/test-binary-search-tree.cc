#include "../include/BinarySearchTree.h"

#include <string>

using namespace std;

int main() {
  BinarySearchTree<int, string>  tree;
  tree.Insert(2, "mango");
  tree.Insert(0, "apple");
  tree.Insert(4, "banana");
  tree.Insert(3, "walnut");
  tree.Insert(1, "cherry");
  tree.InorderTravel();

  int a = 0;
  tree.Delete(a);
  tree.InorderTravel();

  int b = 2;
  tree.Delete(b);
  tree.InorderTravel();

  return 0;
}
