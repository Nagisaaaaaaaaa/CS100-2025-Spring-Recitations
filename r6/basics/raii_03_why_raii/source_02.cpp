/*

  ! Baseline:
  ! 1. 这所谓的“跑到一半不跑了”只有一个例外，那就是“析构函数”。
  ! 2. 析构函数永远都会被自动调用！

*/

#include <cstdlib>
#include <iostream>
#include <vector>

struct QAQ {
  //! 和 C 语言不同的是，C++ 的 `struct` 里面可以定义函数。
  //! 其中有一个特殊的函数叫做“析构函数”，也就是这里的 `~QAQ` 函数。
  //! 正如它的名字，“析构函数”会在变量的“生命结束时”被自动调用。
  ~QAQ() { std::cout << "QAQ" << std::endl; }
};

int main() {
  try {

    int *arr = (int *)malloc(sizeof(int) * 10);
    QAQ qaq;

    std::vector<int> v(0xFFFFFFFFFFFFFFFLLU);

    free(arr);

  } catch (std::exception &e) { //
    std::cout << "The exception message is: " << e.what() << std::endl;
  }

  return 0;
}
