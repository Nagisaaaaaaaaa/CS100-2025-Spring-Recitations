/*

  ! Baseline:
  ! 1. Learn how to work with std::sort

*/

#include "vec.h"
#include <algorithm>
#include <array>
#include <iostream>
#include <string_view>

//! 假设我们拥有这样一个需求：
//! 将一系列向量，按照模长从小到大排序

//! 你觉得下列哪种方式配合std::sort使用最好：
//! 1. 为vec2f重载 `<` 运算符
//! 2. 为vec2f定制一个用于比较模长的functor
//! 3. 当场写一个匿名lambda传入
//! 4. 在外面写好一个lambda传入
//! 5. 使用函数指针

//

//! 我们当然可以像下面这样重载 `<` 但这样做合适吗？
bool operator<(const vec2f &alice, const vec2f &bob) {
  return dot(alice, alice) < dot(bob, bob);
}

int main() {
  vec2f A{1, 3};
  vec2f B{-1, 8};
  vec2f C{0.2, 0.5};
  vec2f D{10, -7};
  vec2f E{99, -1231};

  std::array<vec2f, 5> arr{C, E, A, B, D};

  auto print = [&arr](std::string_view const rem) {
    for (auto a : arr)
      std::cout << a << ' ';
    std::cout << ": " << rem << '\n';
  };

  // # 1
  std::sort(arr.begin(), arr.end());
  print("sorted with reloaded operator <");

  // # 2
  struct {
    bool operator()(const vec2f &alice, const vec2f &bob) { return dot(alice, alice) < dot(bob, bob); }
  } absSmaller;

  std::sort(arr.begin(), arr.end(), absSmaller);
  print("sorted with functor 'absSmaller'");

  // # 3
  std::sort(arr.begin(), arr.end(),
            [](const vec2f &alice, const vec2f &bob) { return dot(alice, alice) < dot(bob, bob); });
  print("sorted with anonymous lambda");

  // # 4
  auto absGreater = [](const vec2f &alice, const vec2f &bob) { return dot(alice, alice) > dot(bob, bob); };
  std::sort(arr.begin(), arr.end(), absGreater);
  print("sorted with non-anonymous lambda 'absGreater'");

  // # 5
  // C-style function pointers are extremely not recommended in C++ programming.
  // Just choose between lamdba and functors: they are always better.
}
