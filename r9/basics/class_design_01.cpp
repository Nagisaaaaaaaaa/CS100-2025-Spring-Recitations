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

private:
  std::string name_;
  int id_;
  std::string email_;
};

int main() {
  Student student("Zhen Ding", 2028533999, "Dingzh6@shanghaitech.edu.cn");

  Student student1 = student;
  Student student2 = std::move(student);

  return 0;
}
