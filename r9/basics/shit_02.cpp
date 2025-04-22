/*

  ! Baseline:
  ! 孩子们，答应我别这么写好吗？

*/

#include <iostream>

void foo(int &x) {
  std::cout << "int &\n";
}

void foo(const int &x) {
  std::cout << "const int &\n";
}

void foo(int &&x) {
  std::cout << "int &&\n";
}

int main() {
  int a = 73;
  int &b = a;
  const int &c = a;
  const int &&d = 42;

  //! 我们一起来品一下参数匹配的过程~
  foo(std::move(b)); // int &&
  foo(std::move(c)); // const int &
  foo(std::move(d)); // const int &
}
