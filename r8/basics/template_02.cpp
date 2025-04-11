/*

  ! Baseline:
  ! 1. Use `template <typename T>` to define a template.

*/

#include <iostream>

// 《Template/stay night》

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
