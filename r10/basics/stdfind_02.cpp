/*

  ! Baseline:
  ! 1. Learn how to work with std::find, std::find_if， std::find_if_not

*/

#include "vec.h"
#include <algorithm>
#include <array>
#include <iostream>

//! 和sort中的 `<` 类似，我们重载 `==` 时也要思考：
//! 我们所定义的相等是否符合逻辑
//! 好在这次在两个向量相等这个判断上，似乎确实是make sense的

bool operator==(const vec2f &alice, const vec2f &bob) {
  return (abs(alice.x() - bob.x()) < 1e-6F) && (abs(alice.y() - bob.y()) < 1e-6F);
}

void example_contains() {

  vec2f A{1, 3};
  vec2f B{-1, 8};
  vec2f C{0.2, 0.5};
  vec2f D{10, -7};
  vec2f E{99, -1231};

  vec2f MATCH1{50, 60};
  vec2f MATCH2{0.1999999, 0.500000001};

  std::array vecs{A, B, C, D, E};
  std::array matches{MATCH1, MATCH2};

  for (const auto MATCH : matches) {
    if (std::find(vecs.begin(), vecs.end(), MATCH) == vecs.end())
      std::cout << "vecs does not contain " << MATCH << '\n';
    else
      std::cout << "vecs contains " << MATCH << '\n';
  }

  //! 仔细阅读Lecture20的PPT第22页（关于配合find使用的各种规范写法）
}

int main() {
  example_contains();
}
