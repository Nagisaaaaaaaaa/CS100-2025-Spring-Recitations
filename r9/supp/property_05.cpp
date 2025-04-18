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
    return id_ / 1000000;
  }

  void ARIA_PROP_SETTER(year)(const int &value) {
    // 修改学号的前 4 位。
    id_ = id_ % 1000000 + value * 1000000;
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

  student.name() = "Zhen Ding";
  student.id() = 2028533999;
  Print(student);

  student.year() -= 4;
  Print(student);

  return 0;
}
