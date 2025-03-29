/*

  ! Baseline:
  ! 1. 我们知道，只要异常出现，后面的代码就一定不会被执行，
  !    也就是说，只要在 `malloc` 和 `free` 的中间出现了异常，就一定会内存泄漏！
  ! 2. 造成这一切的根源是，C++ 选择了异常，使得所有函数都有可能“跑到一半不跑了”！

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

  } catch (std::exception &e) { std::cout << "The exception message is: " << e.what() << std::endl; }

  return 0;
}
