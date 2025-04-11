/*

  ! Baseline:
  ! 1. `delete` copy constructor and copy assignment operator if
  !    you don't know how to implement them.

*/

#include <iostream>

//? 《因为太怕出错就全禁止了。》

struct Vector {
  int *data;

  //! 禁止拷贝构造：Vector vec1 = vec0。
  Vector(const Vector &) = delete;
  //! 禁止拷贝赋值：vec1 = vec0。
  Vector &operator=(const Vector &) = delete;

  ~Vector() { delete[] data; }
};

int main() {
  Vector vec0{new int[5]};

  // Vector vec1 = vec0;

  return 0;
}
