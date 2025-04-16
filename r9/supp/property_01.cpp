#include <iostream>

//? 《Re：从零开始的大一生活》

// 假设你校开设了一门名叫“C++ 设计模式”的专业必修课，
// 它布置了一道这样的题目：
//   请实现一个 class Student，使得以下代码能够运行。

void PrintStudent(const Student &student) {
  std::cout << "name: " << student.name() << std::endl //
            << "id  : " << student.id() << std::endl   //
            << "year: " << student.year() << std::endl //
            << std::endl;
}

int main() {
  Student student;

  // 丁臻是一位研一老登，他很后悔自己 4 年前没有好好学习 CS100，
  // 导致自己科研道路非常艰辛。
  student.name() = "Zhen Ding";
  student.id() = 2024'533'999;
  PrintStudent(student);

  // 丁臻穿越回了 4 年前，这一次，他要学好 C/C++！
  student.year() = 2020;
  PrintStudent(student);

  return 0;
}
