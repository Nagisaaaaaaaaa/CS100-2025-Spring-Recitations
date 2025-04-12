/*

  ! Baseline:
  ! 1. Use `std::move` to “把拷贝换成掠夺”。

*/

#include <iostream>
#include <vector>

int main() {
  {
    // 默认情况下，v1 = v0 会做个拷贝，并且是个深拷贝。
    std::vector<int> v0(10);
    std::vector<int> v1 = v0;

    std::cout << v0.size() << std::endl;
    std::cout << v1.size() << std::endl;
  }

  {
    //! 但是，使用 std::move，我们就能“把拷贝换成掠夺”。
    std::vector<int> v0(10);
    std::vector<int> v1 = std::move(v0);

    //! 这里 v0 已经被“掠夺”了，一无所有，所以 size 是 0。
    std::cout << v0.size() << std::endl;
    std::cout << v1.size() << std::endl;
  }

  return 0;
}
