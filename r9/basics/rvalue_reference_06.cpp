//? 《右值终末旅行》第二季

#include <iostream>

void Print(const std::string &str) {
  std::cout << str + "!" << std::endl;
}

void Print(std::string &&str) {
  str += "!";
  std::cout << str << std::endl;
}

void Go(const std::string &str) {
  // 那我问你，这里会调用哪个重载？
  Print(str);
}

void Go(std::string &&str) {
  //! C++ 选择重载，是基于“表达式”的“类别”来决定的！
  //! 所以如果我们希望它调用 && 的版本，
  //! 就得将“表达式”的“类别”变成 r-value！
  //!
  //! 还记得我们上节课介绍了 std::move，它能够“把拷贝换成掠夺”，
  //* 我们也提到过，std::move(str) 这个“表达式”的“类别”是
  //* 将亡值 (expiring value, xvalue)。
  //* 我们还提到过，纯右值 和 将亡值 这两种“类别”统称为 右值 (rvalue)。
  //!
  //! 所以，只要把 str 换成 std::move(str)，
  //! 我们就成功将这个“表达式”的“类别”变成了 r-value，
  //! 我们就会正确地调用 && 的那个版本！

  // 那我问你，这里会调用哪个重载？
  Print(std::move(str));
}

int main() {
  // 那我问你，这里会调用哪个重载？
  std::string str("QAQ");
  Go(str);

  // 那我问你，这里会调用哪个重载？
  Go(std::string("QAQ"));

  return 0;
}
