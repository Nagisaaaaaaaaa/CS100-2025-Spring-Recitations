#include <string>
#include <vector>

//? 《Ban Dream! It's My构!!!!!》

// 还记得我们之前提到：
// 1. C++ 的默认拷贝行为，会一一对应地拷贝所有成员。
// 2. C++ 的默认“掠夺”行为，会一一对应地“掠夺”所有成员。
//
// 如果将它换个说法：
//! 1. 只要所有的成员都“正确地”实现了拷贝行为，我们就能放心地使用默认拷贝。
//! 2. 只要所有的成员都“正确地”实现了“掠夺”行为，我们就能放心地使用默认“掠夺”。
//!
//! 甚至：
//! 3. 只要所有的成员都“正确地”实现了 RAII (析构函数)，我们就能放心地使用默认析构！

class Student {
public:
  Student() = default;

  //! 默认拷贝构造，这行代码甚至可以省略不写。
  Student(const Student &) = default;
  //! 默认拷贝赋值，这行代码甚至可以省略不写。
  Student &operator=(const Student &) = default;

  //! 默认“掠夺”构造，这行代码甚至可以省略不写。
  Student(Student &&) = default;
  //! 默认“掠夺”赋值，这行代码甚至可以省略不写。
  Student &operator=(Student &&) = default;

  //! 默认析构，这行代码甚至可以省略不写。
  ~Student() = default;

private:
  std::string name_;        // 名字。
  std::vector<int> grades_; // 成绩。
};

//! 没错，我们未来有生之年写的 99% 的 C++ class，都只需要：
//! 1. 写下这 5 个 = default！
//! 2. 或者甚至可以全省略，一个都不写！

int main() {
  Student stu0;
  Student stu1 = stu0;
  Student stu2 = std::move(stu0);

  return 0;
}
