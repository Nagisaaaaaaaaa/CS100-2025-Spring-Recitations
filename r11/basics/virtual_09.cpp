#include <memory>
#include <vector>

//? 《OLD GAME!》

// 现在，我们来回答这些问题：
//! 当涉及到继承的时候，析构函数必须是虚函数吗？
//! 如果不是虚函数，岂不是很危险吗？

// 我们来看这样的一个例子：
// 假设你是一位普信程序员，打算继承 std::vector，
// 并为它拓展功能。
class MyVector : public std::vector<int> {
  // ...
};

int main() {
  //! 那我问你，这么写安全吗？
  MyVector v0;

  //! 答案：
  //!   安全，反正总是会调用 ~MyVector 的析构函数。

  //! 那我问你，这么写安全吗？
  std::unique_ptr<std::vector<int>> v1 = std::make_unique<MyVector>();

  //! 答案：
  //!   危险，因为父类 std::vector 的析构函数不是 virtual 的，
  //!   会调用父类的析构函数，不会调用子类的析构函数。

  //* 虽然它存在危险，但是真有人类会写出这种代码吗？
  //* std::unique_ptr<std::vector<int>>
  //* 会这么写的都是神人了，所以没关系的，放心用。

  //* 所以，我们实际上有这样的设计原则：
  //* 1. 如果一个 class 存在非析构函数的虚函数，
  //*    那么这个 class 的析构函数也应当是虚函数。
  //* 2. 如果一个 class 不存在非析构函数的虚函数，
  //*    那么这个 class 的析构函数也应当不是虚函数。
}
