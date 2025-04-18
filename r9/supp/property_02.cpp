#include <iostream>

//? 《Re：从零开始的大一生活》

class Student {
  // TODO: Your code here.
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
