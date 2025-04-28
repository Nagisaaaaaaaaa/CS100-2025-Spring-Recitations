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

void foo(const int &&x) {
  std::cout << "const int &&\n";
}

int main() {
  int a = 73;
  int &b = a;
  const int &c = a;
  const int &&d = 42; // 仔细思考，这个类型到底有什么意义？

  //! &&暗示着d是一个右值引用：它延长了一个孤魂野鬼的生命周期
  //! 但无论如何延长，这种写法的 `本愿` 都有且仅能有一个：
  //! 告诉别人：来利用我！来掠夺我（所绑定对象的资源）！
  //! 但是 `const` 的修饰，又使得真正的掠夺成为不可能
  //! 这种本质性的自相矛盾，使得const &&成为了一种边缘化的类型

  foo(std::move(b)); // int &&
  foo(std::move(c)); // const int &&
  foo(std::move(d)); // const int &&
}
