/*

  ! Baseline:
  ! 1. 如果将 error code 和 exception 混用，将会非常容易导致资源泄漏。
  !    例如在一对 `malloc` 和 `free` 的中间出现了异常 (下面的例子)，就一定会出现内存泄漏。
  ! 2. 造成这一切的根源是，C++ 选择了 exception 而不是 error code，
  !    这使得所有函数都有可能“跑到一半不跑了”。
  !    而 C 那些不存在异常的语言，就永远不会遇到这种麻烦。
  !    这 就 是 选 择 了 异 常 的 代 价。

*/

#include <cstdlib>
#include <iostream>
#include <vector>

int main() {
  try {

    int *arr = (int *)malloc(sizeof(int) * 10);

    std::vector<int> v(0xFFFFFFFFFFFFFFFLLU);

    std::cout << "Start freeing" << std::endl;
    free(arr);

  } catch (std::exception &e) { //
    std::cout << "The exception message is: " << e.what() << std::endl;
  }

  return 0;
}
