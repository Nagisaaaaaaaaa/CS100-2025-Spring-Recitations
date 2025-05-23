/*

  ! Baseline:
  ! 1. 对于最简单的数组来说，裸指针本身就可以被作为一种“迭代器”。
  !    但对于其他更复杂的数据结构，裸指针就不够用了。
  ! 2. 任何 class，只要实现了 begin 和 end 这两个成员函数，
  !    就能够自动支持 range-based for 循环。

*/

#include <iostream>

//? 《迭代器 STL的准则》

// 为什么 std::vector 和 std::list
// 能够支持 range-based for 循环呢？
//! 有没有办法让我们自己的 class 支持它呢？

// 这是一个超级简陋的 Vector 实现。
struct Vector {
  int *data;
  size_t size;

  ~Vector() { delete[] data; }

  // 我们定义两个神秘函数 begin 和 end，
  // 它们仅仅返回头尾的指针。
  int *begin() { return data; }

  int *end() { return data + size; }
};

int main() {
  Vector vec{new int[5]{}, 5};

  for (size_t i = 0; i < vec.size; ++i)
    vec.data[i] = i;

  // 我们竟然就可以像 std::vector 和 std::list 一样使用它了！
  for (auto it = vec.begin(); it != vec.end(); ++it)
    std::cout << *it << std::endl;

  for (const auto &v : vec)
    std::cout << v << std::endl;

  //! 感受一下：
  //! 1. 对于最简单的数组来说，裸指针本身就可以被作为一种“迭代器”。
  //!    但对于其他更复杂的数据结构，裸指针就不够用了。
  //! 2. 任何 class，只要实现了 begin 和 end 这两个成员函数，
  //!    就能够自动支持 range-based for 循环。

  return 0;
}
