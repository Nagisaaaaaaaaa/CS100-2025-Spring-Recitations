/*

  ! Baseline:
  ! 1. Use `template <typename T>` to define a template.
  ! 2. Now, `Vector` is no longer a class, it is a template.
  ! 3. But, `Vector<int>` is a class.

*/

#include <iostream>

// 《Template/stay night》

// 什么是模板 (template)？
//   在任何一个 struct/class 前面加上 template <typename T>，
//   就能把这个 struct/class 变成一个 template。
// 这里的 T 被称为模板参数 (template parameter)：
//   当我们写 Vector<int>    时，T 就是 int   ，得到 int    *data。
//   当我们写 Vector<double> 时，T 就是 double，得到 double *data。
template <typename T>
struct Vector {
  T *data;

  ~Vector() { delete[] data; }
};

// 你可以想象，编译器或许是这么干的：
//
// 当我们写下 Vector<int> 时，编译器把所有的 T 都替换成了 int，生成了一个类型：
//   struct VectorInt {
//     int *data;
//     ~Vector() { delete[] data; }
//   };
//
// 当我们又写下 Vector<double> 时，编译器把所有的 T 都替换成了 double，又生成了一个类型：
//   struct VectorDouble {
//     double *data;
//     ~Vector() { delete[] data; }
//   };
//
// 当我们双写下……
// 当我们叒写下……
// 当我们叕写下……

//! 那我问你：
//!   1. Vector      是一个“类型”吗？
//!   2. Vector<int> 是一个“类型”吗？

//! 答案是：
//!   1. Vector      不是一个“类型”，它是一个“模板”。
//!   2. Vector<int> 是一个“类型”没错。

int main() {
  Vector<int> vecI{new int[5]};
  Vector<double> vecD{new double[5]};

  return 0;
}
