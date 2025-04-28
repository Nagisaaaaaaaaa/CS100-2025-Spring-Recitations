#include <iostream>

//? 《Re：从零开始的大一生活》

// 又幻想了，幻想你校开设了一门名叫“高级 C++ 编程”的专业必修课，CS1000，
// 我成功当上了这门课的助教，并且出了一道这样的 HW5：
//   请实现 class Student，使得以下代码能够正确执行。

class Student {
  // TODO: Your code here.
};

void Print(const Student &student) {
  std::cout << "name: " << student.name() << std::endl //
            << "id  : " << student.id() << std::endl   //
            << "year: " << student.year() << std::endl //
            << std::endl;
}

int main() {
  Student student;

  // 丁臻是一位研一老登，他很后悔自己 4 年前没有好好学习 CS100，
  // 导致自己的科研道路非常艰辛。
  student.name() = "Zhen Ding";
  student.id() = 2028533999; //! 注：丁臻是 2028 级研究生，所以学号是 2028 开头的。
  Print(student);
  // 会打印出：
  //   name: Zhen Ding
  //   id  : 2028533999
  //   year: 2028

  // 有一天，一觉醒来，丁臻发现自己竟然穿越回了 4 年前！
  // 这一次，他要学好 CS100！
  student.year() -= 4;
  Print(student);
  // 会打印出：
  //   name: Zhen Ding
  //!  id  : 2024533999 // 注：在 4 年前，丁臻是 2024 级本科生，所以学号是 2024 开头的。
  //!  year: 2024

  return 0;
}
