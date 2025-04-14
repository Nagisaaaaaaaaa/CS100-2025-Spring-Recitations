/*

  ! Baseline:
  ! 1. Why moving "RAII owner" is dangerous.

*/

#include <iostream>

//? 《Ban Dream! It's My构!!!!!》

// 请找到这几行代码中的 bug。

struct Vector {
  int *data;

  ~Vector() { delete[] data; }
};

int main() {
  Vector vec0{new int[5]};

  // C++ 的默认“掠夺”行为，会一一对应地“掠夺”所有成员。
  // 所以，下面这行代码等价于 vec1.data = std::move(vec0.data)。
  Vector vec1 = std::move(vec0);

  //! 很不幸的是，对指针这类 C 语言基础类型做“拷贝”和“掠夺”是等价的。
  std::cout << vec0.data << std::endl;
  std::cout << vec1.data << std::endl;

  return 0;
}
