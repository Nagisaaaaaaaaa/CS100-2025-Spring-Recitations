/*

  ! Baseline:
  ! 1. 既然析构函数总是会被自动调用，那么我们就永远通过析构函数来释放资源，
  !    这样就永远都不会出现资源泄漏！
  ! 2. 也正是因此，大家逐渐形成了这样的习惯：在“构造”的时候获取资源，在“析构”的时候释放资源。
  !    并且将它命名为 RAII (Resource Acquisition Is Initialization)！
  ! 3. C++ 标准库中的很多东西，例如 `std::vector`，都是遵循 RAII 实现的。

*/

#include <cstdlib>
#include <iostream>
#include <vector>

struct MemoryGuard {
  int *ptr;

  ~MemoryGuard() {
    free(ptr);
    std::cout << "Finished freeing" << std::endl;
  }
};

int main() {
  try {

    MemoryGuard arr{(int *)malloc(sizeof(int) * 10)};

    std::vector<int> v(0xFFFFFFFFFFFFFFFLLU);

  } catch (std::exception &e) { //
    std::cout << "The exception message is: " << e.what() << std::endl;
  }

  return 0;
}
