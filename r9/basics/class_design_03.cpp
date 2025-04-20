/*

  ! Baseline:

*/

#include <iostream>

class Student {
public:
  Student() = default;

  Student &name(std::string value) {
    name() = std::move(value);
    return *this;
  }

  Student &id(int value) {
    id() = value;
    return *this;
  }

  Student &email(std::string value) {
    email() = std::move(value);
    return *this;
  }

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
  //! 我们希望支持默认构造，因此所有成员都需要指定默认值：
  std::string name_;  //! 默认值是空字符串。
  int id_ = 0;        //! 默认值是 0。
  std::string email_; //! 默认值是空字符串。

private:
  // TODO: 在这里实现一些 private 成员函数。
};

int main() {
  auto student = Student() //
                     .name("Zhen Ding")
                     .id(2024533999)
                     .email("Dingzh6@shanghaitech.edu.cn");

  std::cout << student.name() << std::endl;
  std::cout << student.id() << std::endl;
  std::cout << student.email() << std::endl;

  return 0;
}
