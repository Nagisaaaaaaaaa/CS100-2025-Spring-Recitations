#include "ARIA/Property.h"

using namespace ARIA;

//? 《Re：从零开始的大一生活》

//* 我们来直观地感受一下“代理” (proxy) 的强大之处。
class Student {
public:
  const std::string &name() const { return name_; }

  std::string &name() { return name_; }

  const int &id() const { return id_; }

  int &id() { return id_; }

  //* 不知名的野鸡开源库 ARIA 里面有 Property.h 这个头文件，
  //* 它提供了一个名叫 ARIA_PROP 的宏，
  //* 可以帮我们自动创建各种“代理” (这里 PROP 是 property 的缩写)。
  //*
  //* 比如这里我们定义了一个名叫 year，类型为 int 的代理。
  //* (别在意这里的前 3 个参数，这么写就对了)
  //*
  //! 当我们调用 student.year() 时，
  //! 将返回一个神秘的“变量”，它拥有一个神秘的“类型”。
  //! 这个神秘变量，就是我们所说的“代理”。
  ARIA_PROP(public, public, ARIA_HOST, int, year);

private:
  //* 注意，在这个例子中，我们只存储 id，不存储 year。
  std::string name_;
  int id_ = 0;

  //* 我们希望能这么写代码：
  //*   int y = student.year();
  //*
  //* 这意味着，每次都需要当场根据 id 计算 year。
  //* 只需要为 year 这个“代理”定义一个叫做“getter”的神秘函数，
  //* year 就能够自动支持这个功能了。
  int ARIA_PROP_GETTER(year)() const {
    // 取学号的前 4 位。
    return id_ / 1000000;
  }

  //* 我们还希望能这么写代码：
  //*   student.year() = y;
  //*   student.year() -= 4;
  //*
  //* 因为我们只存储了 id，所以需要根据给定的 year 修改 id。
  //* 只需要为 year 这个“代理”定义一个叫做“setter”的神秘函数，
  //* year 就能够自动支持所有相关功能，包括 += 和 -=。
  void ARIA_PROP_SETTER(year)(const int &value) {
    // 修改学号的前 4 位。
    id_ = id_ % 1000000 + value * 1000000;
  }
};

//! student.year() 会返回一个神秘的“变量”，这个变量就是我们所说的“代理”。
//* 当我们试图读取这个“代理”时，它会悄悄调用“getter”，
//* “getter”会根据 id 计算出 year。
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

  //! student.year() 会返回一个神秘的“变量”，这个变量就是我们所说的“代理”。
  //* 当我们试图修改这个“代理”时，它会悄悄调用“setter”，
  //* “setter”会根据给定的 year 修改 id。
  student.year() -= 4;
  Print(student);

  //* 总结：
  //! 1. “代理”是一个神秘的“变量”，拥有神秘的“类型”。
  //! 2. 可以把“代理”理解为一种“设计模式”。
  //* 3. 适当地使用“代理”可以让写代码更快乐。

  return 0;
}
