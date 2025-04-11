/*

  ! Baseline:
  ! 1. Use `template <typename T>` to define a template.

*/

#include <iostream>

// 《Template/stay night》

// 什么是 template？
// 加上这一行，我们就把一个 struct 变成了一个 template。
// 这里的 T 被称为模板参数 (template parameter)。
//   当我们写 Vector<int>    时，T 就是 int，
//   当我们写 Vector<double> 时，T 就是 double。
template <typename T>
struct Vector {
  T *data;

  ~Vector() { delete[] data; }
};

int main() {
  Vector<int> vecI{new int[5]};
  Vector<double> vecD{new double[5]};

  return 0;
}
