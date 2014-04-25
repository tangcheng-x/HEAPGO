#ifndef AUTO_PTR_H_
#define AUTO_PTR_H_

template <typename T>
struct AutoPtrRef {
  T* m_ptr_;
  
  explicit AutoPtrRef(T* P)
    : m_ptr_(p) {}
};  // struct AutoPtrRef


template <typename T>
class AutoPtr {
 private:
  T* m_ptr_;

 public:
  typedef T element_type;

  explicit AutoPtr(element_type* p = NULL) throw()
    : m_ptr_(p) {}

  AutoPtr(AutoPtr& a) throw()
    : m_ptr_(a.release()) {
  }

  template <typename T1>
  AutoPtr(AutoPtr<T1>& a) throw()
    : m_ptr_(a.release()) {
  }

  AutoPtr& operator=(AutoPtr& a) throw() {
    reset(a.release());
    return *this;
  }

  template <class T1>
  AutoPtr& operato=(AutoPtr<T1>& a) throw() {
    reset(a.release());
    return *this;
  }

  ~AutoPtr() { delete m_ptr_; }

  element_type& operator*() const throw() {
    CHECK(m_ptr_ != NULL);
    return *m_ptr_;
  }

  element_type* operator->() const throw() {
    CHECK(m_ptr_ != NULL);
    return m_ptr_;
  }

  element_type* get() const throw() {
    return m_ptr_;
  }

  element_type* release() throw() {
    element_type* temp = m_ptr_;
    m_ptr_ = NULL;
    return temp;
  }

  void reset(element_type* p = NULL) throw() {
    if (p != m_ptr_) {
      delete m_ptr_;
      m_ptr_ = p;
    }
  }

  AutoPtr(AutoPtrRef<element_type> ref) throw()
    : m_ptr_(ref.m_ptr_) { }

  AutoPtr& operator= (AutoPtrRef<element_type> ref) throw() {
    if (ref.m_ptr_ != this->get()) {
      delete m_ptr_;
      m_ptr_ = ref.m_ptr_;
    }
    return *this;
  }

  template <typename T1>
  operator AutoPtrRef<T1>() throw() {
    return AutoPtrRef<T1>(this->release());
  }

  template <typename T1>
  operator AutoPtr<T1>() throw() {
    return AutoPtr<T1>(this->release());
  }

};  // class AutoPtr

#endif  // AUTO_PTR_H_
