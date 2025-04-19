/*

  ! Baseline:
  ! 1. const & 能够延长纯右值的生命周期：
  !   (1). const int &         能延长 5                  这个纯右值的生命周期。
  !   (2). const std::string & 能延长 std::string("QAQ") 这个纯右值的生命周期。
  !
  ! 2. 函数参数写 (int x)           和写 (const int &x)           有什么区别？
  !    函数参数写 (std::string str) 和写 (const std::string &str) 有什么区别？
  !   (1). int        : 孤魂野鬼找地方住。
  !   (2). const int &: 延长纯右值的生命周期。
  !
  ! 3. 调用 Student 的构造函数会拷贝几次 std::string？
  !   (1). 有多少种排列组合？它们的区别是什么？
  !   (2). std::move 这个函数的意思是“把拷贝换成掠夺”。
  !
  ! 4. 这三个等于号的含义分别是什么？
  !   (1). std::string str = std::string("QAQ"); // 孤魂野鬼找地方住。
  !   (2). std::string str = str0;               // 拷贝。
  !   (3). std::string str = std::move(str0);    // “掠夺”。

  * Bonus:
  * 5. C++ 的表达式可以分为 lvalue，prvalue，xvalue 三种“类别”。
  * 6. 其中 prvalue 和 xvalue 这两种“类别”统称为 rvalue。

*/

#include <string>

//? 《右值终末旅行》

class Student {
public:
  //! 这里的 ??? 有多少种排列组合？它们的区别是什么？
  explicit Student(??? name) : name_(???) {}

private:
  std::string name_;
};

int main() {
  // 调用构造函数会拷贝几次 std::string？
  std::string name("Zhen Ding");
  Student student0(name);

  // 调用构造函数会拷贝几次 std::string？
  Student student1(std::string("Zhen Ding"));

  return 0;
}
