//? 《右值终末旅行》

#include <string>

class Student {
public:
  //! 神奇的是，最优解竟然是这么实现的：
  //!   1. 接收 std::string。
  //!   2. 调用 std::move。
  //!
  //! name_(std::move(name)) 的意思是：
  //!   让 name_ 直接“夺舍”掉 name，从此，name 名存实亡！
  //!   所以，std::move 这个函数的意思是“夺舍”，跟“移动”没有任何关系。
  explicit Student(std::string name) : name_(std::move(name)) {}

private:
  std::string name_;
};

int main() {
  // 那我问你，调用构造函数会拷贝几次 std::string？
  std::string name("Zhen Ding");
  Student student0(name);

  // 答案：
  //   1. 参数是 std::string，传入左值，一次拷贝。
  //!  2. name_(std::move(name))，直接“夺舍”，没有拷贝。

  // 那我问你，调用构造函数会拷贝几次 std::string？
  Student student1(std::string("Zhen Ding"));

  // 答案：
  //!  1. 参数是 std::string，“孤魂野鬼找地方住”，没有拷贝。
  //!  2. name_(std::move(name))，直接“夺舍”，没有拷贝。

  return 0;
}
