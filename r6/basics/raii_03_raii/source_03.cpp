/*

  ! Baseline:
  ! 1. 既然 析 构 函 数 一 定 会 被 执 行，
  !    那么我们就可以 永 远 让 析 构 函 数 来 负 责 释 放 资 源，
  !    这样就 永 远 都 不 会 出 现 资 源 泄 漏！
  ! 2. 久而久之，大家逐渐形成了这样的编程习惯：
  !    永 远 在 _构 造_ 的 时 候 _获 取_ 资 源，
  !    永 远 在 _析 构_ 的 时 候 _释 放_ 资 源。
  !    并且将这一习惯命名为 RAII (Resource Acquisition Is Initialization)！
  ! 3. C++ 标准库中的很多东西，例如 `std::vector`、`std::string`，都是遵循 RAII 的。

*/

#include <cstdlib>
#include <iostream>
#include <vector>

struct MemoryGuard {
  int *const ptr;

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
