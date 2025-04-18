/*

  ! 请使用 g++ -std=c++20 来编译。
  ! 这份代码依赖于 cute 和 ARIA 这两个开源库，如果编译不过，随机都可以找助教帮忙啊。

  * Bonus:
  * 1. std::vector<bool> 是 STL 中使用“代理”的典型案例。
  * 2. 那么，代价是什么？

*/

#include "ARIA/Property.h"

//? 《Re：从零开始的大一生活》

class Student {
public:
  ARIA_PROP(public, public, ARIA_HOST, int, year);

private:
  int id_ = 0;

  int ARIA_PROP_GETTER(year)() const { return id_ / 1000000; }

  void ARIA_PROP_SETTER(year)(const int &value) { id_ = id_ % 1000000 + value * 1000000; }
};

int main() {
  // 我们可以通过 typeid 来打印出函数的返回值类型。
  // 这样就能知道返回值是否是“代理”了。
  Student student;
  std::cout << typeid(student.year()).name() << std::endl;

  // std::vector 的中括号本质上也是函数。
  // 猜猜分别会打印出什么？
  std::vector<int> vec0;
  std::cout << typeid(vec0[0]).name() << std::endl;

  std::vector<bool> vec1;
  std::cout << typeid(vec1[0]).name() << std::endl;

  //! std::vector<bool> 几乎是 STL 中最“诡异”的类型。
  //! 我们知道，C++ 中，bool 这个类型至少也得有 1 个 byte。
  //! 但 std::vector<bool> 实际上只使用 1 个 bit 来存储 bool，
  //! 这么设计是为了节省内存。
  //!
  //! 可以想象，std::vector<bool> 的中括号运算符，
  //! 返回的是某个 bool 的“代理”。
  //! 和 student.year() 非常类似。

  //! 那么，代价是什么？
  for (auto &v : vec0) {}

  for (auto &v : vec1) {}

  return 0;
}
