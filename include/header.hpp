// Copyright 2021 siruser agamesok@gmail.com

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
#include <stdexcept>
#include <atomic>
#include <vector>
#include <iostream>
#include <utility>

auto example() -> void;

template <typename T>
class SharedPtr {
 public:
  SharedPtr(){
    this->ptr = nullptr;
    this->counter = new std::atomic_uint;
    *this->counter = 0;
  }

  explicit SharedPtr(T* pointer){
    this->counter = new std::atomic_uint;
    this->ptr = pointer;
    *this->counter = 1;
  }

  SharedPtr(const SharedPtr& r){
    this->ptr = r.ptr;
    this->counter = r.counter;
    (*this->counter)++;
  }

  SharedPtr(SharedPtr&& r){
    this->ptr = std::move(r.ptr);
    this->counter = std::move(r.counter);
  }

  ~SharedPtr(){
    if ((*this->counter) < 2)
    {
      delete this->counter;
    } else {
      this->ptr = nullptr;
      (*this->counter)--;
    }
  }

  auto operator=(const SharedPtr& r) -> SharedPtr&{
    if ((*this->counter) > 1)
    {
      (*this->counter)--;
    }
    this->ptr = r.ptr;
    this->counter = r.counter;
    (*this->counter)++;
    return *this;
  }

  auto operator=(SharedPtr&& r) -> SharedPtr&{
    if ((*this->counter) > 1)
    {
      (*this->counter)--;
    }
    this->ptr = std::move(r.ptr);
    this->counter = std::move(r.counter);
    return *this;
  }

  operator bool() const{
    return (this->ptr != nullptr);
  }

  auto operator*() const -> T&{
    return (*this->ptr);
  }

  auto operator->() const -> T*{
    return this->ptr;
  }

  auto get() -> T*{
    return this->ptr;
  }

  void reset(){
    if (*this->counter > 1)
    {
      (*this->counter)--;
    } else {
      delete this->counter;
    }
    this->ptr = nullptr;
    this->counter = new std::atomic_uint;
    *this->counter = 0;
  }

  void reset(T* pointer){
    if (*this->counter > 1)
    {
      (*this->counter)--;
    } else {
      delete this->counter;
    }
    this->ptr = pointer;
    this->counter = new std::atomic_uint;
    *this->counter = 1;
  }

  void swapPtr(SharedPtr& r){
    T* temp1 = this->ptr;
    std::atomic_uint* temp2 = this->counter;
    this->ptr = r.ptr;
    this->counter = r.counter;
    r.ptr = temp1;
    r.counter = temp2;
  }

  auto use_count() const -> size_t{
    if (this->counter == nullptr)
    {
      return 0;
    } else {
      return *this->counter;
    }
  }

 private:
  T* ptr;
  std::atomic_uint* counter;
};

#endif  // INCLUDE_HEADER_HPP_
