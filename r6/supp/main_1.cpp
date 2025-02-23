#include <exception>
#include <iostream>
#include <string>

void SomeBuggyFunction() {
  int num = std::stoi("杂鱼♥～杂鱼♥～，才不会给你一个数字呢♥");
  std::cout << num << std::endl;
}

//
//
//
int main() {
  try {
    SomeBuggyFunction();
  } catch (const std::exception &e) { std::cout << e.what() << std::endl; }

  return 0;
}
