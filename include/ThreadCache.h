#ifndef THREAD_CACHE_H_
#define THREAD_CACHE_H_

class ThreadCache {
 private:
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

  };  // class FreeList for ThreadCache
};  // class ThreadCache



#endif  // THREAD_CACHE_H_
