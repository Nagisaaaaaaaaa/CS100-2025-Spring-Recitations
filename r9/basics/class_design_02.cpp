/*

  ! Baseline:
  ! 1. 设计一个 class 需要考虑哪些问题？

*/

#include <iostream>

class Student {
public:
  Student(std::string name, int id, std::string email) //
      : name_(std::move(name)), id_(id), email_(std::move(email)) {}

public:
  const std::string &name() const { return name_; }

  std::string &name() { return name_; }

  const int &id() const { return id_; }

  int &id() { return id_; }

  const std::string &email() const { return email_; }

  std::string &email() { return email_; }

public:
  // TODO: 在这里实现一些 public 成员函数。

  //
  //
  //
private:
  std::string name_;
  int id_;
  std::string email_;

private:
  // TODO: 在这里实现一些 private 成员函数。
};

int main() {
  Student student{"Zhen Ding", 2024533999, "Dingzh6@shanghaitech.edu.cn"};

  Student student1 = student;
  Student student2 = std::move(student);

  return 0;
}
