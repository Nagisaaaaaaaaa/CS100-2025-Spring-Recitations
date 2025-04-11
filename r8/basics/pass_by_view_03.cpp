#include <iostream>
#include <span>
#include <vector>

//? 《我的函数传参方式果然有问题》

//! view: 大哥们躺着别动就行，让我来当函数参数吧。
void Print(std::span<int> view) {
  for (const auto &v : view)
    std::cout << v << " ";
  std::cout << std::endl;
}

int main() {
  std::vector<int> vec0 = {0, 1, 2, 3, 4};
  int vec1[5] = {0, 1, 2, 3, 4};

  //! 两个大哥都能够被隐式转化成 non-owning 的 std::span<int> view。
  //! 最终，view 抗下了所有，打印出来了两个大哥的数组。
  Print(vec0);
  Print(vec1);

  //? (哎呀，我 view 得了 MVP！一看两个大哥什么事都不用干，躺赢狗！)

  return 0;
}
