#include <iostream>

//? 《Re：从零开始的大一生活》

class Student {
public:
  const std::string &name() const { return name_; }

  std::string &name() { return name_; }

  const int &id() const { return id_; }

  int &id() { return id_; }

  //! 我们知道，id 的前 4 位就是 year。
  //! 所以我们理所当然地，只存储 id，每次需要用到 year 的时候，
  //! 当场把它计算出来就完事了，反正只需要一次除法嘛。
  int year() const { return id_ / 1000000; } // 取学号的前 4 位。

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

  student.year() -= 4;
  Print(student);

  return 0;
}
