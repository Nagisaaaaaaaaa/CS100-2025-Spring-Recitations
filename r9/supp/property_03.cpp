#include "ARIA/Property.h"

using namespace ARIA;

class Student {
public:
  const std::string &name() const { return name_; }

  std::string &name() { return name_; }

  const int &id() const { return id_; }

  int &id() { return id_; }

  ARIA_PROP(public, public, ARIA_HOST, int, year);

private:
  std::string name_;
  int id_ = 0;

  int ARIA_PROP_GETTER(year)() const {
    // 取学号的前 4 位。
    return id_ / 1'000'000;
  }

  void ARIA_PROP_SETTER(year)(const int &value) {
    // 修改学号的前 4 位。
    id_ = id_ % 1'000'000 + value * 1'000'000;
  }
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
  // 导致自己科研道路非常艰辛。
  student.name() = "Zhen Ding";
  student.id() = 2028'533'999;
  Print(student);

  // 丁臻穿越回了 4 年前，这一次，他要学好 C/C++！
  student.year() -= 4;
  Print(student);

  return 0;
}
