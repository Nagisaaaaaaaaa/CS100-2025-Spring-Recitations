/*

  ! Baseline:
  ! 1. 构造函数的设计原则：
  !   (1). 99% 的情况下，不要让构造函数的参数超过 2 个。
  !   (2). 95% 的情况下，不要让构造函数的参数超过 1 个。
  !   (3). 尽可能支持默认构造 (0 个参数)。
  !   (4). 如果真的希望超过 2 个，使用“builder pattern” (见下一集)。

*/

#include <iostream>

class Student {
public:
  //! 这个构造函数，设计得足够好吗？
  //! 为什么参数顺序要设计成：名字、学号、邮箱 呢？
  //! 难道名字一定比学号重要吗？不一定吧？我还觉得邮箱最重要呢！
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
  //! 请找到这行代码中的 bug。
  Student student{"Dingzh6@shanghaitech.edu.cn", 2024533999, "Zhen Ding"};

  //! 构造函数的设计原则：
  //! 1. 99% 的情况下，不要让构造函数的参数超过 2 个。
  //! 2. 95% 的情况下，不要让构造函数的参数超过 1 个。
  //! 3. 尽可能支持默认构造 (0 个参数)。
  //! 4. 如果真的希望超过 2 个，使用“builder pattern” (见下一集)。

  return 0;
}
