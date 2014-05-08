#ifndef V8_THREAD_H_
#define V8_THREAD_H_

#include "Utils.h"

#include <climits>
#include <cstdlib>  // For malloc and free
#include <cstring>  // strncpy

#include <pthread.h>
#include <semaphore.h>
#include <stdint.h>  // For intptr_t using
#include <sys/prctl.h>  // prctl method

static const pthread_t kNoThread = (pthread_t)0;

class Malloced {
 public:
  void* operator new(size_t size) { return New(size); }
  void operator delete(void* p) { Delete(p); }
  
  static void* New(size_t size);
  static void Delete(void* p);
};  // class Mallocd


void* Malloced::New(size_t size) {
  void* result = malloc(size);
  if (result == NULL) {
    LOG_OUT("Out of memory\n");
  }
  return result;
}


void Malloced::Delete(void* p) {
  free(p);
}

// ----------------------------------------------------------------------------
// class Semaphore
//
class Semaphore {
 public:
  explicit Semaphore(int count);
  ~Semaphore();

  // Increments the semaphore counter
  void Signal();

  // Suspends the calling thread until the semaphore counter is non zero
  // and then decrements the semaphore counter
  void Wait();
 
  // Suspends the calling thread until the counter is non zero or the timeout
  // time has passed. If timeout happens the return value is false and the
  // counter is unchanged. Otherwise the semaphore counter is decremented and
  // true is returned.
  // WAIT FOR IMPLEMENTED
  //bool WaitFor(const TimeDelta& rel_time);
  
  typedef sem_t NativeHandle;

  NativeHandle& native_handle() {
    return native_handle_;
  }
  
  const NativeHandle& native_handle() const {
    return native_handle_;
  }

 private:
  NativeHandle native_handle_;
  DISALLOW_COPY_AND_ASSIGN(Semaphore);
};  // class Semaphore


Semaphore::Semaphore(int count) {
  CHECK(count >= 0);
  int result = sem_init(&native_handle_, 0, count);
  CHECK_EQ(0, result);
  USE(result);
}


Semaphore::~Semaphore() {
  int result = sem_destroy(&native_handle_);
  CHECK_EQ(0, result);
  USE(result);
}


void Semaphore::Signal() {
  int result = sem_post(&native_handle_);
  CHECK_EQ(0, result);
  USE(result);
}

void Semaphore::Wait() {
  while (true) {
    int result = sem_wait(&native_handle_);
    if (result == 0) return;

    CHECK_EQ(-1, result);
    //CHECK_EQ(EINTR, errno);
  }
}



class Thread {
 public:
  enum LocalStorageKey {
    LOCAL_STORAGE_KEY_MIN_VALUE = kMinInt,
    LOCAL_STORAGE_KEY_MAX_VALUE = kMaxInt
  };  // enum LocalStorageKey

  class Options {
   public:
    Options() : name_("<unknown>"), stack_size_(0) {}
    Options(const char* name, int stack_size = 0)
      : name_(name), stack_size_(stack_size) {}

    const char* name() const { return name_; }
    int stack_size() const { return stack_size_; }

   private:
    const char* name_;
    int stack_size_;
  };  // internal class Options

  // Create new thread
  explicit Thread(const Options& options);
  virtual ~Thread();

  // Start new thread by calling the Run method on the new thread.
  void Start();

  // Start new thread and wait until Run() is called on the new thread.
  void StartSynchronously() {
    start_semaphore_ = new Semaphore(0);
    Start();
    start_semaphore_->Wait();
    delete start_semaphore_;
    start_semaphore_ = NULL;
  }

  // Wait until thread terminates
  void Join();

  const char* name() const {
    return name_;
  }

  virtual void Run() = 0;

  static LocalStorageKey CreateThreadLocalKey();
  static void DeleteThreadLocalKey(LocalStorageKey key);
  static void* GetThreadLocal(LocalStorageKey key);
  static int GetThreadLocalInt(LocalStorageKey key) {
    return static_cast<int>(reinterpret_cast<intptr_t>(GetThreadLocal(key)));
  }
  static bool HasThreadLocal(LocalStorageKey key) {
    return GetThreadLocal(key) != NULL;
  }

  static void SetThreadLocal(LocalStorageKey key, void* value);
  static void SetThreadLocalInt(LocalStorageKey key, int value) {
    SetThreadLocal(key, reinterpret_cast<void*>(static_cast<intptr_t>(value)));
  }

  static inline void* GetExistingThreadLocal(LocalStorageKey key) {
    return GetThreadLocal(key);
  }

  static void YieldCPU();

  static const int kMaxThreadNameLength = 16;

  class PlatformData;
  PlatformData* data() { return data_; }

  void NotifyStartedAndRun() {
    if (start_semaphore_) start_semaphore_->Signal();
    Run();
  }
 private:
  void set_name(const char* name);
  PlatformData* data_;
  
  char name_[kMaxThreadNameLength];
  int stack_size_;
  
  Semaphore* start_semaphore_;

  DISALLOW_COPY_AND_ASSIGN(Thread);
};  // class Thread


class Thread::PlatformData : public Malloced {
 public:
  PlatformData() : thread_(kNoThread) {}

  pthread_t thread_;
};  // class Thread::PlatformData

Thread::Thread(const Options& options)
  : data_(new PlatformData),
    stack_size_(options.stack_size()),
    start_semaphore_(NULL) {
  if (stack_size_ > 0 && stack_size_ < PTHREAD_STACK_MIN) {
    stack_size_ = PTHREAD_STACK_MIN;
  }
  set_name(options.name());
}


Thread::~Thread() { delete data_; }


static void SetThreadName(const char* name) {
  prctl(PR_SET_NAME, reinterpret_cast<unsigned long>(name),
      0, 0, 0);
}


static void* ThreadEntry(void* arg) {
  Thread* thread = reinterpret_cast<Thread*>(arg);
  thread->data()->thread_ = pthread_self();
  SetThreadName(thread->name());
  CHECK(thread->data()->thread_ != kNoThread);
  thread->NotifyStartedAndRun();
  return NULL;
}


void Thread::set_name(const char* name) {
  strncpy(name_, name, sizeof(name_));
  name_[sizeof(name_) - 1] = '\0';
}


void Thread::Start() {
  int result;
  pthread_attr_t attr;
  memset(&attr, 0, sizeof(attr));
  result = pthread_attr_init(&attr);
  CHECK_EQ(0, result);
  
  result = pthread_create(&data_->thread_, &attr, ThreadEntry, this);
  CHECK_EQ(0, result);
  result = pthread_attr_destroy(&attr);
  CHECK_EQ(0, result);
  CHECK(data_->thread_ != kNoThread);
  USE(result);
}


void Thread::Join() {
  pthread_join(data_->thread_, NULL);
}


void Thread::YieldCPU() {
  int result = sched_yield();
  CHECK_EQ(0, result);
  USE(result);
}


static Thread::LocalStorageKey PthreadKeyToLocalKey(pthread_key_t local_key) {
  return static_cast<Thread::LocalStorageKey>(local_key);
}


static pthread_key_t LocalKeyToPthreadKey(Thread::LocalStorageKey local_key) {
  return static_cast<pthread_key_t>(local_key);
}


void Thread::DeleteThreadLocalKey(LocalStorageKey key) {
  pthread_key_t pthread_key = LocalKeyToPthreadKey(key);
  int result = pthread_key_delete(pthread_key);
  CHECK_EQ(0, result);
  USE(result);
}


void* Thread::GetThreadLocal(LocalStorageKey key) {
  pthread_key_t pthread_key = LocalKeyToPthreadKey(key);
  return pthread_getspecific(pthread_key);
}


void Thread::SetThreadLocal(LocalStorageKey key, void* value) {
  pthread_key_t pthread_key = LocalKeyToPthreadKey(key);
  int result = pthread_setspecific(pthread_key, value);
  CHECK_EQ(0, result);
  USE(result);
}

#endif  // V8_THREAD_H_
