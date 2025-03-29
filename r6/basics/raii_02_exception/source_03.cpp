/*

  ! Baseline:
  ! 1. “exception”这种“错误处理方式”的优点：
  !   1.1. 只要程序没被一拳打个半死，我们就能断言，它一定在好好地运作。
  !   1.2. 允许程序员不处理任何错误，懒人的福音。
  ! 2. “exception”这种“错误处理方式”的缺点：
  !   2.1. 不严谨、不安全。
  !   2.2. 不显式，`e.what()` 没法让我们一下子定位到错误的源头。

*/

#include <iostream>
#include <vector>

void SomeComplexFileTask() {
  // ...
}

void SomeComplexTask() {
  SomeComplexFileTask();
  // ...
}

int main() {
  try {
    SomeComplexTask();
  } catch (std::exception &e) { std::cout << "The exception message is: " << e.what() << std::endl; }

  return 0;
}
