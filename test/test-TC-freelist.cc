#include <iostream>
#include <cstdlib>
#include "../include/malloc/ThreadCache.h"

using namespace std;

int main() {
  FreeList list;
  list.Init();

  void* p1 = (void*)malloc(16);
  void* p2 = (void*)malloc(32);
  void* p3 = (void*)malloc(64);
  void* p4 = (void*)malloc(128);

  list.Push(p1);
  list.Push(p2);
  list.Push(p3);
  list.Push(p4);
  
  cout << list.length() << endl;
  void* cur = list.GetHead();
  while (cur != NULL) {
    cout << cur << endl;
    cur = *(reinterpret_cast<void**>(cur));
  }

  list.Pop();
  cout << list.length() << endl;
  cur = list.GetHead();
  while (cur != NULL) {
    cout << cur << endl;
    cur = *(reinterpret_cast<void**>(cur));
  }
}
