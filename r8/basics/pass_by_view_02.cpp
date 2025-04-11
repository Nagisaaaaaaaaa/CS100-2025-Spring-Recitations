/*

  ! 请使用 g++ -std=c++20 来编译。

  ! Baseline:
  ! 1. Why pass by owner is bad?

*/

#include <iostream>
#include <vector>

//? 《我的函数传参方式果然有问题》

// 假设我们想打印出各种数组。

// 实现 std::vector<int> 版本。
void Print(const std::vector<int> &vec) {
  for (const auto &v : vec)
    std::cout << v << " ";
  std::cout << std::endl;
}

// 实现 int* 版本。
void Print(const int *vec, size_t n) {
  for (size_t i = 0; i < n; ++i)
    std::cout << vec[i] << " ";
  std::cout << std::endl;
}

int main() {
  std::vector<int> vec0 = {0, 1, 2, 3, 4};
  int vec1[5] = {0, 1, 2, 3, 4};

  Print(vec0);
  Print(vec1, 5);

  //! 好烦啊，明明代码大差不差，为什么还要再写一遍！

  return 0;
}
