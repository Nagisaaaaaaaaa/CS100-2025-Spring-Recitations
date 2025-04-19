#include <iostream>

//? 《右值终末旅行》第二季

void Print(const std::string &str) {
  std::cout << str + "!" << std::endl;
}

void Print(std::string &&str) {
  str += "!";
  std::cout << str << std::endl;
}

// 假设我们还有一个叫 Go 的函数，它会调用 Print。
// 和 Print 一样，Go 也需要有两个版本。

void Go(const std::string &str) {
  //! 那我问你，这里会调用哪个重载？
  Print(str);
}

void Go(std::string &&str) {
  //! 那我问你，这里会调用哪个重载？
  Print(str);
}

int main() {
  // 那我问你，这里会调用哪个重载？
  std::string str("QAQ");
  Go(str);

  // 那我问你，这里会调用哪个重载？
  Go(std::string("QAQ"));

  // 为什么会这样？
  //! 因为 C++ 选择重载，是由“表达式”的“类别”来决定的！
  //!
  //! 对于那两个 Print(str)，
  //!   两个 str “变量”的“类型”分别是 const & 和 &&。
  //!   两个 str “表达式”的“类别”都是 lvalue (左值)，有名有姓，能取地址。
  //!
  //! 由于“表达式”的“类别”是 lvalue (左值)，
  //! 所以它们都会选择左值版本的 Print！

  //! 这时候，请再回过头看看那四句“那我问你，这里会调用哪个重载？”
  //! C++ 选择重载，是由“表达式”的“类别”来决定的！

  return 0;
}
