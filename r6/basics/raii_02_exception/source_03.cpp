/*

  ! Baseline:
  ! 1. 如何分别使用 error code 和 exception 实现 `SomeComplexTask` 这个例子？
  ! 2. Exception 这种“错误处理方式”的优点：
  !   2.1. 只要程序没被一拳打个半死，我们就能断言，它一定在好好地运作。
  !   2.2. 允许程序员不处理任何错误，懒人的福音。
  ! 3. Exception 这种“错误处理方式”的缺点：
  !   3.1. 不严谨、不安全。
  !   3.2. 不显式，`e.what()` 没法让我们一下子定位到错误的源头。

*/

#include <iostream>
#include <vector>

void SomeComplexFileTask() {
  // ...
}

void SomeComplexTask() {
  SomeComplexFileTask();

  std::vector<int> v(0xFFFFFFFFFFFFFFFLLU);
}

int main() {
  try {

    SomeComplexTask();

  } catch (std::exception &e) { //
    std::cout << "The exception message is: " << e.what() << std::endl;
  }

  return 0;
}
