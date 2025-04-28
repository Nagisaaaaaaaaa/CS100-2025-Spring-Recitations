#include <iostream>
#include <list>
#include <vector>

int main() {
  //? 《迭代器 STL的准则》

  // STL 中，除了数组 (vector) 之外，还有链表 (list) 这样的“容器”。
  std::vector<int> arr0{0, 1, 2, 3, 4};
  std::list<int> arr1{0, 1, 2, 3, 4};

  // 只看下面几行代码，你能猜到 arr0 和 arr1 分别是数组和链表吗？

  for (auto it = arr0.begin(); it != arr0.end(); ++it)
    std::cout << *it << std::endl;

  for (auto it = arr1.begin(); it != arr1.end(); ++it)
    std::cout << *it << std::endl;

  for (const auto &v : arr0)
    std::cout << v << std::endl;

  for (const auto &v : arr1)
    std::cout << v << std::endl;

  //! 所以，STL 的设计是尽可能追求“大一统”的。
  //   “大一统”的本质是，我们可以随意地修改 arr0 和 arr1 的类型，
  //   而完全不会影响对它们的使用。

  //! 为了实现“大一统”，这个终极目标，
  //! STL 引入了“迭代器”这个概念。

  return 0;
}
