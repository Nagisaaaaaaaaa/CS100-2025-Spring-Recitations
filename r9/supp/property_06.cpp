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

  //! 猜猜分别会打印出什么？
  std::vector<int> vec0;
  std::cout << typeid(vec0[0]).name() << std::endl;

  std::vector<bool> vec1;
  std::cout << typeid(vec1[0]).name() << std::endl;

  //! std::vector<bool> 几乎是 STL 中最“诡异”的类型。
  //! 我们知道，C/C++ 中，bool 这个类型至少也得有 1 个 byte。
  //! 但 std::vector<bool> 实际上使用 1 个 bit 来存储 bool，
  //! 这么做是为了节省内存。
  //!
  //! 所以，std::vector<bool> 的中括号运算符，
  //! 返回的是那个 bool 的“代理”。
  //! 和 student.year() 非常类似。

  return 0;
}
