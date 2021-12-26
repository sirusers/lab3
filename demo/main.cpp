// Copyright 2021 siruser agamesok@gmail.com

#include <iostream>
#include "header.hpp"
int main() {
  struct shared {
    int a;
    int b;
  };
  shared one = { 1, 2 };
  shared two = { 2, 1 };
  SharedPtr<shared> a(&one);
  SharedPtr<shared> b(&two);
  b.swapPtr(a);
  std::cout << a.use_count() << std::endl;
}
