//? 《右值终末旅行》

#include <string>

class Student {
public:
  //! 我们只需要调用一次 std::move 就能够得到最优解！
  explicit Student(std::string name) : name_(std::move(name)) {}

private:
  std::string name_;
};

int main() {
  // 问：这行代码拷贝了几次 std::string？
  std::string name = "Zhen Ding";
  Student student0(name);

  // 答：
  //   1. 参数是 std::string name，传入左值，做了一次拷贝。
  //!  2. name_(std::move(name))，直接“掠夺”，没发生拷贝。

  // 问：这行代码拷贝了几次 std::string？
  Student student1(std::string("Zhen Ding"));

  // 答：
  //!  1. 参数是 std::string name，传入“纯净”右值，没发生拷贝。
  //!  2. name_(std::move(name))，直接“掠夺”，没发生拷贝。

  return 0;
}
