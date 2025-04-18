#include <iostream>

//? 《Re：从零开始的大一生活》

class Student {
public:
  const std::string &name() const { return name_; }

  std::string &name() { return name_; }

  const int &id() const { return id_; }

  int &id() { return id_; }

  int year() const { return id_ / 1000000; } // 取学号的前 4 位。

  //! 一切的困难都来源于我们需要支持 year() -= 4，
  //! 如果只需要支持 SetYear(year - 4) 的话，这题就没那么难了。
  void SetYear(int value) { id_ = id_ % 1000000 + value * 1000000; } // 修改学号的前 4 位。

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

  //! 如果只需要支持 SetYear(year - 4) 的话，这题就没那么难了。
  // student.year() -= 4;
  student.SetYear(student.year() - 4);
  Print(student);

  //* 总结一下这题难在哪里：
  //* 1. 我们需要同时支持 id() = ... 和 year() -= ...，
  //*    说明 id() 和 year() 这两个成员函数都得返回 reference。
  //* 2. 当我们修改 id   的时候，year 需要被自动修改，
  //*    当我们修改 year 的时候，id   也需要被自动修改。

  //* 每次用 SetId, SetYear, Set... 来修改东西，不也挺好的嘛。
  //*   试想一下你在做游戏开发 (Set 的重灾区)，
  //*   用 多 了 你 一 定 会 觉 得 烦 的......

  return 0;
}
