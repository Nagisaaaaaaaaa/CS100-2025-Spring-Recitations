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

  // 那我问你，这里会调用哪个重载？
  Print(str);
}

int main() {
  // 那我问你，这里会调用哪个重载？
  std::string str("QAQ");
  Go(str);

  // 那我问你，这里会调用哪个重载？
  Go(std::string("QAQ"));

  return 0;
}
