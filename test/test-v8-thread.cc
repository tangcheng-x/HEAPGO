#include "../include/V8-Thread.h"

#include <gtest/gtest.h>

class ThreadA : public Thread {
 public:
  ThreadA() : Thread("ThreadA") { }
  void Run() {
    Join();
  }
}; // class ThreadA

TEST(testV8Thread, threadJoinSelf) {
  ThreadA thread;
  thread.Start();
  thread.Join();
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
