#include <iostream>

//? 《Re：从零开始的大一生活》

class Student {
public:
  const std::string &name() const { return name_; }

  std::string &name() { return name_; }

  const int &id() const { return id_; }

  int &id() { return id_; }

  int year() const { return id_ / 1000000; } // 取学号的前 4 位。

  void setYear(int value) { id_ = id_ % 1000000 + value * 1000000; } // 修改学号的前 4 位。

private:
  std::string name_;
  int id_ = 0;
};

void Print(const Student &student) {
  std::cout << "name: " << student.name() << std::endl //
            << "id  : " << student.id() << std::endl   //
            << "year: " << student.year() << std::endl //
            << std::endl;
}

int main() {
  Student student;

  student.name() = "Zhen Ding";
  student.id() = 2028533999;
  Print(student);

  // student.year() -= 4;
  student.setYear(student.year() - 4);
  Print(student);

  return 0;
}
