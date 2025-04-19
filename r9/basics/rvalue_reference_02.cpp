#include <iostream>

//? 《右值终末旅行》第二季

//! 有些时候，我们希望函数能根据接收左值还是右值，做不同的事情。
//! 比如接收右值的时候，做一点小优化。
//! 这当然得通过函数重载来实现。

// 假设我们希望实现一个 Print，
// 它会在打印字符串的时候添加一个感叹号。

// 首先实现一个最简单粗暴的版本。
void Print(const std::string &str) {
  std::cout << str + "!" << std::endl;
}

//! 重载：我们希望函数在接收右值的时候，做一点小优化。
void Print(std::string str) {
  //! 有时候用 += 会比 + 跑得更快。
  str += "!";
  std::cout << str << std::endl;
}

int main() {
  // 那我问你，这里会调用哪个重载？
  std::string str("QAQ");
  Print(str);

  // 那我问你，这里会调用哪个重载？
  Print(std::string("QAQ"));

  // 答案：
  //! 甚至无法通过编译。
  //! error: call of overloaded function is ambiguous.

  // 为什么会这样？
  //! C++ 的函数参数，std::string 和 const std::string & 这两种写法，
  //! 它们的“江湖地位”是相同的，因为它们都能接收左值和右值。

  return 0;
}
