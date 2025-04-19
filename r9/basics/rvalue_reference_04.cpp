//? 《右值终末旅行》第二季

#include <iostream>

void Print(const std::string &str) {
  std::cout << str + "!" << std::endl;
}

//! 一切的根源都是重载导致的 ambiguous。
//! 为了绕开这个问题，
//! C++ 设计师引入了 右值引用 (r-value reference) 这个东西。
//!
//! 我们把 std::string 改成 std::string &&，
//! 这里的 && 就表示它是一个 右值引用。
void Print(std::string &&str) {
  str += "!";
  std::cout << str << std::endl;
}

int main() {
  // 那我问你，这里会调用哪个重载？
  std::string str("QAQ");
  Print(str);

  // 答案：
  // 会调用第一个，因为
  //! std::string && 只能接收右值，不能接收左值。

  // 那我问你，这里会调用哪个重载？
  Print(std::string("QAQ"));

  // 答案：
  // 会调用第二个，因为
  //! C++ 设计师为 && 开了个后门，
  //! 即使 const & 也能接收右值，&& 仍然拥有更高的优先级。
  //!
  //! 那么当 std::string &&str 接收一个 std::string("QAQ") 时，到底发生了什么？
  //! 和 const & 一样，它延长了右值的生命周期，仅此而已！

  //! 右值引用不是什么神秘的东西，我们只需要记住这几条游戏规则：
  //! 1. 选择函数重载时，右值引用的优先级更高 (开后门)。
  //! 2. 右值引用能延长右值的生命周期。
  //! 3. 与 const & 的延长生命周期不同，&& 不要求 const。

  return 0;
}
