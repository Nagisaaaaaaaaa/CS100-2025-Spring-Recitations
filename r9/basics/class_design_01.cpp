/*

  ! Baseline:
  ! 1. 设计一个 class 需要考虑哪些问题？

*/

#include <iostream>

class Student {
public:
  //! 用 std::move 来最大程度地减少拷贝次数。
  //! 成员的构造永远写在冒号后面，不要写在花括号里面。
  //* 我们上周介绍过 pass-by-view 的设计思想，但请让我们暂时忘记它。
  Student(std::string name, int id, std::string email) //
      : name_(std::move(name)), id_(id), email_(std::move(email)) {}

  //! 为什么这里还要写一次 public？
  //! 仅仅是为了让 class 的结构更清晰。
public:
  //! 对于成员变量的访问，一定要
  //! 同时提供 const 和 non-const 两个版本。
  //! 请总是把 const 那版放在上面，这样我们就永远不会忘记写它。
  const std::string &name() const { return name_; }

  std::string &name() { return name_; }

  const int &id() const { return id_; }

  int &id() { return id_; }

  const std::string &email() const { return email_; }

  std::string &email() { return email_; }

  //! 为什么这里还要写一次 public？
public:
  // TODO: 在这里实现一些 public 成员函数。

  //! private 的成员变量和函数通常放在最下面，
  //! 因为使用这个 class 的人没有义务了解任何实现细节。
private:
  //! 成员变量推荐使用这几种命名方式：
  //! 2. someName_  / some_name_
  //! 4. _someName  / _some_name
  //! 6. m_someName / m_some_name
  std::string name_;
  int id_;
  std::string email_;

  //! 为什么这里还要写一次 private？
private:
  // TODO: 在这里实现一些 private 成员函数。
};

int main() {
  //! 构造函数能用花括号调用就不要用圆括号。
  Student student{"Zhen Ding", 2024533999, "Dingzh6@shanghaitech.edu.cn"};

  //! 我们上节课讲过，拷贝/移动 构造/赋值 析构 那 5 个函数，
  //! 只要一个都不写，编译器就会自动使用默认的版本。
  Student student1 = student;
  Student student2 = std::move(student);

  return 0;
}
