/*

  ! Baseline:
  ! 1. STL 的设计是尽可能追求“大一统”的。
  ! 2. 为了实现“大一统”，这个终极目标，
  !    STL 引入了“迭代器”这个概念。

*/

#include <iostream>
#include <list>
#include <vector>

int main() {
  //? 《迭代器 STL的准则》

  std::vector<int> arr0{0, 1, 2, 3, 4};
  std::list<int> arr1{0, 1, 2, 3, 4};

  // 我们来显式地看一下 begin 和 end 的返回值类型。
  // 它们的类型名字有点长，但都是以“iterator”作为结尾的。

  std::vector<int>::iterator begin0 = arr0.begin();
  std::vector<int>::iterator end0 = arr0.end();

  std::list<int>::iterator begin1 = arr1.begin();
  std::list<int>::iterator end1 = arr1.end();

  // “iterator”的中文是“迭代器”，
  //! 我们总是使用迭代器来遍历“容器” (数组、链表)。
  for (auto it = begin0; it != end0; ++it)
    std::cout << *it << std::endl;

  for (auto it = begin1; it != end1; ++it)
    std::cout << *it << std::endl;

  // 那你会问，不也可以用传统方法遍历数组嘛：
  for (size_t i = 0; i < arr0.size(); ++i)
    std::cout << arr0[i] << std::endl;

  //! 但是对于 std::list，传统方法就不行了。
  // 这是因为链表只能“按照顺序一个一个访问”，不能“跳着访问”：
  for (size_t i = 0; i < arr1.size(); ++i)
    std::cout << arr1[i] << std::endl;

  //! 感受一下：
  //! 1. STL 的设计是尽可能追求“大一统”的。
  //! 2. 为了实现“大一统”，这个终极目标，
  //!    STL 引入了“迭代器”这个概念。

  return 0;
}
