/*

  ! Baseline:

*/

#include <iostream>

class Student {
public:
  //* 如何实现下面那种梦幻的构造方式？

  //* Step 1: 支持默认构造。
  Student() = default;

  //* Step 2: 为每个成员定义一个这样的函数：
  //* 1. 接收对应类型的 value。
  //* 2. 根据给定的 value 修改成员。
  //* 3. 返回值类型为 Student &，并且 return *this。
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
  //! 为了支持默认构造，所有成员都需要指定默认值：
  std::string name_;  //! 默认值是空字符串。
  int id_ = 0;        //! 默认值是 0。
  std::string email_; //! 默认值是空字符串。

private:
  // TODO: 在这里实现一些 private 成员函数。
};

int main() {
  //* 如果构造函数的参数超过 2 个，构造的时候带上它们的名字。
  //* 这么做的好处是，不再要求传参顺序，永远都不会出错！
  auto student = Student() //
                     .name("Zhen Ding")
                     .id(2024533999)
                     .email("Dingzh6@shanghaitech.edu.cn");

  std::cout << student.name() << std::endl;
  std::cout << student.id() << std::endl;
  std::cout << student.email() << std::endl;

  return 0;
}
