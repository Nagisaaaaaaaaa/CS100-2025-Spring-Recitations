#include <iostream>

//? 《Re：从零开始的大一生活》

class Student {
public:
  const std::string &name() const { return name_; }

  std::string &name() { return name_; }

  const int &id() const { return id_; }

  int &id() { return id_; }

  //! 既然 year() 必须得返回一个 reference，
  //! 那我们干脆把 id 和 year 都设为成员变量吧。
  const int &year() const { return year_; }

  int &year() { return year_; }

private:
  std::string name_;
  int id_ = 0;
  int year_ = 0;
};

void Print(const Student &student) {
  std::cout << "name: " << student.name() << std::endl //
            << "id  : " << student.id() << std::endl   //
            << "year: " << student.year() << std::endl //
            << std::endl;
}

int main() {
  Student student;

  //! 这下连前三行都搞不定了，因为
  //! 当我们修改 id 的时候，year 并没有被修改！
  student.name() = "Zhen Ding";
  student.id() = 2028533999;
  Print(student);

  student.year() -= 4;
  Print(student);

  return 0;
}
