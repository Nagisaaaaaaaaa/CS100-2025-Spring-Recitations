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
public:
  // 你觉得 std::copy 的设计就是一坨，于是
  // 为它实现了一个更香的 copy 函数。
  void copy(const MyVector &others) { /*...*/ }
};

int main() {
  //! 那我问你，这行代码安全吗？
  MyVector v0;

  //! 答案：
  //!   安全。
  //!   因为这里没有涉及到任何指针，只有 MyVector 类型的实例，
  //!   自然总是会调用 MyVector 的析构函数。

  //! 那我问你，这行代码安全吗？
  std::unique_ptr<std::vector<int>> v1 = std::make_unique<MyVector>();

  //! 答案：
  //!   危险。
  //!   因为这里涉及到了 std::vector<int> * 类型的指针。
  //!   由于父类 std::vector<int> 的析构函数不是 virtual 的，
  //!   所以只会调用父类的析构函数，不会调用子类的析构函数。

  //* 这个例子和我们 GameObject、Tank 的例子有什么本质区别？
  //*   没有任何需求会用到 std::vector<int> * 这样的指针，
  //*   为什么一定用不到指针？因为不存在任何虚函数！
  //*   所以，MyVector 这样的实现，是足够安全的！

  //* 我们实际上有这样的设计原则：
  //* 1. 如果一个 class 存在 非析构函数的 虚函数，
  //*    那么这个 class 的析构函数 必须是虚函数。
  //* 2. 如果一个 class 不存在 非析构函数的 虚函数，
  //*    那么这个 class 的析构函数 不必是虚函数。
}
