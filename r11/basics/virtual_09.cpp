#include <memory>
#include <vector>

//* 但是，将万能公式换句话说：
//*   如果最远古的父类析构函数没有写 virtual，
//*   那么我们是不是永远都不应该继承于它呢？

//* 答案：
//*   也可以随意继承，只是不能用父类的指针析构。

// 假设你是一位普信程序员，打算继承 std::vector，
// 并为它拓展功能。
class MyVector : public std::vector<int> {
  // ...
};

int main() {
  //! 这么写安全吗？
  MyVector v0;

  //! 答案：
  //!   安全，反正总是会调用 ~MyVector 的析构函数。

  //! 这么写安全吗？
  std::unique_ptr<std::vector<int>> v1 = std::make_unique<MyVector>();

  //! 答案：
  //!   危险，因为父类 std::vector 的析构函数不是 virtual 的，
  //!   会调用父类的析构函数，不会调用子类的析构函数。

  //* 虽然它存在危险，但是真有人类会写出这种代码吗？
  //* std::unique_ptr<std::vector<int>>
  //* 会这么写的都是神人了，所以没关系的，放心用。
}
