#include <iostream>

//? 《右值终末旅行》第二季

//! 为了让参数的“江湖地位”不再相同，
//! 我们把 const std::string & 改成 std::string &，
void Print(std::string &str) {
  std::cout << str + "!" << std::endl;
}

void Print(std::string str) {
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
  //! 这下，传右值行了，但传左值还是不行。
  //! error: call of overloaded function is ambiguous.

  // 为什么会这样？
  //! 所谓的“江湖地位”，是“见仁见智”的。
  //! 对于右值，只能选择第二个重载。
  //! 对于左值，仍然是两者都行。

  return 0;
}
