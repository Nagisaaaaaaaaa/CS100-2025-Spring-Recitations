/*

  ! Baseline:
  ! 1. 聪明的 C++ 语言设计师当然知道选择 exception 会带来的问题，
  !    所以他们提出了这样的设计：C++ 有一种函数一定会被执行，那就是“析构函数”。
  ! 2. 析 构 函 数 一 定 会 被 执 行！

*/

#include <cstdlib>
#include <iostream>
#include <vector>

struct QAQ {
  //! 和 C 语言不同的是，C++ 的 `struct` 里面可以定义函数。
  //! 其中有一种特殊的函数叫做“析构函数”，也就是这里的 `~QAQ` 函数。
  //! 正如它的名字，“析构函数”会在变量的“生命结束时”被自动调用，并且，
  //! 它 一 定 会 被 执 行！
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
