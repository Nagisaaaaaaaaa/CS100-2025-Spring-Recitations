/*

  ! Baseline:
  ! 1. Use `std::move` to “把拷贝换成掠夺”。

*/

#include <iostream>

int main() {
  {
    // 默认情况下，str1 = str0 会做个拷贝，并且是个深拷贝。
    std::string str0("QAQ");
    std::string str1 = str0;

    std::cout << str0.length() << std::endl;
    std::cout << str1.length() << std::endl;
  }

  {
    //! 但是，使用 std::move，我们就能“把拷贝换成掠夺”。
    std::string str0("QAQ");
    std::string str1 = std::move(str0);

    //! 这里 str0 已经被“掠夺”了，一无所有，所以 length 是 0。
    std::cout << str0.length() << std::endl;
    std::cout << str1.length() << std::endl;
  }

  return 0;
}
