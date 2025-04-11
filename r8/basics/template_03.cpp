/*

  ! Baseline:
  ! 1. Use `template <typename T>` to define a template.
  ! 2. `Vector`      is a template, not a class.
  !    `Vector<int>` is a class.
  ! 3. Understand template instantiation.
  ! 4. `std::vector` is a template.

*/

#include <iostream>

// 《Template/stay night》

// 什么是模板 (template)？
//   在任何一个 struct/class 前面加上 template <typename T>，
//   就能把这个 struct/class 变成一个 template。
// 这里的 T 被称为模板参数 (template parameter)：
//   当我们写 Vector<int>    时，T 就是 int   ，得到 int    *data。
//   当我们写 Vector<double> 时，T 就是 double，得到 double *data。
//! 有没有发现，它越来越像 std::vector 了呢？
template <typename T>
struct Vector {
  T *data;

  ~Vector() { delete[] data; }
};

int main() {
  Vector<int> vecI{new int[5]};
  Vector<double> vecD{new double[5]};

  // 可以想象，编译器或许做了这样的事情：
  //
  // 当我们写下 Vector<int> 时，
  // 编译器把 Vector 中所有的 T 都替换成了 int，
  //! 生成了一个新的类型：
  //     struct Vector {
  //       int *data;
  //       ~Vector() { delete[] data; }
  //     };
  //
  // 当我们又写下 Vector<double> 时，
  // 编译器又把 Vector 中所有的 T 都替换成了 double，
  //! 又生成了一个新的类型：
  //     struct Vector {
  //       double *data;
  //       ~Vector() { delete[] data; }
  //     };
  //
  // 当我们双写下……
  //! 双生成了一个新的类型……
  //
  // 当我们叒写下……
  //! 叒生成了一个新的类型……
  //
  // 当我们叕写下……
  //! 叕生成了一个新的类型……

  //! 那我问你：
  //!   1. Vector      是一个“类型”吗？
  //!   2. Vector<int> 是一个“类型”吗？

  //! 答案是：
  //!   1. Vector      不是一个“类型”，它是一个“模板”。
  //!   2. Vector<int> 是一个“类型”没错。
  //!
  //! 我们称，从“模板”生成“类型”的过程，叫做：
  //!   模板实例化 (template instantiation)。

  return 0;
}
