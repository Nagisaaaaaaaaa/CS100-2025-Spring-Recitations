#include <iostream>

// 为什么 std::vector 和 std::list
// 能够支持 range-based for 循环呢？
//! 有没有办法让我们自己的 class 支持它呢？

// 这是一个超级简陋的 Vector 实现。
struct Vector {
  int *data;
  size_t size;

  ~Vector() { delete[] data; }

  int *begin() { return data; }

  int *end() { return data + size; }
};

int main() {
  //? 《迭代器 STL的准则》

  Vector vec{new int[5]{}, 5};

  for (size_t i = 0; i < vec.size; ++i)
    vec.data[i] = i;

  for (const auto &v : vec)
    std::cout << v << std::endl;

  return 0;
}
