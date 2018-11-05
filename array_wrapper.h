#ifndef ARRAY_WRAPPER_H
#define ARRAY_WRAPPER_H
#include <iostream>

template <typename T>
struct array_wrapper
{
  typedef T* iterator;
  typedef const T* const_iterator;
  array_wrapper(T* begin, T* end) : data_(begin), size_(end-begin) {}
  array_wrapper(T* begin, size_t size) : data_(begin), size_(size) {}
  iterator begin() { return data_; }
  iterator end() { return data_ + size_; }
  const_iterator begin() const { return data_; }
  const_iterator end() const { return data_ + size_; }
  size_t size() const { return size_; }
  T& operator[](size_t i) { return data_[i]; }
  const T& operator[](size_t i) const { return data_[i]; }
  void swap(array_wrapper& other) { 
    std::swap(size_, other.size_);
    std::swap(data_, other.data_);
  }
 private:
  T* data_;
  size_t size_;
};

typedef unsigned char BYTE;
typedef array_wrapper<BYTE> ByteArray;

template <typename T>
void printwrapper(const array_wrapper<T> &aw) {
  for (int i = 0; i < aw.size(); ++i)
      std::cout << i << ": " << (signed int)aw[i] << std::endl;
}

#endif /* ARRAY_WRAPPER_H */

