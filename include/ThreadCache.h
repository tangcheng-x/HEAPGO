#ifndef THREAD_CACHE_H_
#define THREAD_CACHE_H_

#include "stdint.h"

#include "MallocUtils.h"

class FreeList {
  private:
   void*       list_;       // Linked list of nodes;
#ifdef BUILD_64
   // On 64-bit hardware, manipulating 16-bit values may be sightly slow
   uint32_t length_;         // Current length
   uint32_t lowater_;        // Low water mark for list length
   uint32_t max_length_;     // Dynamix max list length based on usage
   // Tracks the number of times a deallocation has caused
   uint32_t length_overages_;
#else
   uint16_t length_;
   uint16_t lowater_;
   uint16_t max_length_;
   uint16_t length_overages_;
#endif
  public:
   void Init() {
     list_ = NULL;
     length_ = 0;
     lowater_ = 0;
     max_length_ = 1;
     length_overages_ = 0;
   }

   // Return current length of list
   size_t length() const {
     return length_;
   }

   // Return the maximum length of the list
   size_t max_length() const {
     return max_length_;
   }

   // Set the maximum length of the list. if the new max_lentgth > length(),
   // the client is responsible for removing objects from the list
   void set_max_length(size_t new_max) {
     max_length_ = new_max;
   }


   size_t length_overages() const {
     return length_overages_;
   }

   size_t set_length_overages(size_t new_count) {
     length_overages_ = new_count;
   }

   bool empty() const {
     return list_ == NULL;
   }

   int lowatermark() const { return lowater_; }
   void clear_lowwatermark() { lowater_ = length_; }

   // Push the element to the front of the list_
   void Push(void* element) {
     SLL_Push(&list_, element);
     ++length_;
   }

   // Pop the front of the list_
   void* Pop() {
     ASSERT(list_ != NULL);
     --length_;
     if (length_ < lowater_) lowater_ = length_;
     return SLL_Pop(&list_);
   }


   // Push range of free memory block
   void PushRange(int n, void* start, void* end) {
     SLL_PushRange(&list_, start, end);
     length_ += n;
   }

   // Pop range of free memory block from the head of the list
   void PopRange(int n, void** start, void** end) {
     SLL_PopRange(&list_, n, start, end);
     ASSERT(length_ >= n);
     length_ -= n;
     if (length_ < lowater_) lowater_ = length_;
   }

   void* GetHead() {
     return list_;
   }
};  // class FreeList for ThreadCache

class ThreadCache {
 private:
#ifdef HAVE___ATTRIBUTE__
#define ATTR_INITIAL_EXEC __attribute__ ((tls_model ("initial-exec)))
#else
#define ATTR_INITIAL_EXEC
#endif

#ifdef HAVE_TLS
   struct ThreadLocalData {
    ThreadLocal *heap;
    // min_size_for_slow_path is 0 if heap is NULL or kMaxSize + 1 otherwise.
    // The latter is the common case and allows allocation to be faster
    // than it would be otherwise: typically a single branch will
    // determine that the requested allocation is no more than kMaxSize
    // and we can then proceed, knowing that global and thread-local tcmalloc
    // state is initialzed.
    size_t min_size_for_slow_path;
   }; // struct ThreadLocalData

   static __thread ThreadLocalData threadlocal_data_ ATTR_INITIAL_EXEC;

#endif

   // Whether initialize the thread local data
   static bool tsd_inited_;
   // If use the pthread thread local data solution
   static pthread_key_t heap_key_;

   // TC linked list
   static ThreadCache* thread_heaps_;

   // The number of TC
   static int thread_heap_count_;

   // The next steal TC
   static ThreadCache* next_memory_steal_;
   
   // Overall thread cache size
   static size_t overall_thread_cache_size_;

   // Each TC's size
   static size_t per_thread_cache_size_;

   // The size of free memory which can be used in TC
   static size_t unclaimed_cache_space_;
   
   // This class is laid out with the most frequently used fields
   // accross all ThreadCaches.
   size_t size_;                 // Combined size of data
   size_t max_size_;             // size_ > max_size_ --> Scavenge()

   FreeList list_[kNumClasses];  // Array indexed by size-classes

   pthread_t tid_;
   
   bool in_setspecific_;         // In call to pthread_setspecific?

   
};  // class ThreadCache


#endif  // THREAD_CACHE_H_
