#include <iostream>
#include <list>
#include <vector>

int main() {
  std::vector<int> arr0{0, 1, 2, 3, 4};
  std::list<int> arr1{0, 1, 2, 3, 4};

  // 我们来显式地看一下 begin 和 end 的返回值类型。

  std::vector<int>::iterator begin0 = arr0.begin();
  std::vector<int>::iterator end0 = arr0.end();

  std::list<int>::iterator begin1 = arr1.begin();
  std::list<int>::iterator end1 = arr1.end();

  // “iterator”的中文是“迭代器”，也就是说，
  //! STL 要求我们总是使用迭代器来遍历所有的“容器” (数组、链表)。

  // 那你会问，我不也可以用传统方法遍历数组嘛：
  for (size_t i = 0; i < arr0.size(); ++i)
    std::cout << arr0[i] << std::endl;

  //! 但是对于 std::list，传统方法就不行了：
  for (size_t i = 0; i < arr1.size(); ++i)
    std::cout << arr1[i] << std::endl;

  // 这是因为链表只能“按照顺序一个一个访问”，不能“跳着访问”。
  //! 这就是为什么，STL 要求我们总是使用迭代器来遍历所有的“容器” (数组、链表)。

  return 0;
}
