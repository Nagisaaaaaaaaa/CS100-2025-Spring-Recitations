//? 《右值终末旅行》

#include <string>

class Student {
public:
  //! 如果改为 const std::string & 呢？
  explicit Student(const std::string &name) : name_(name) {}

private:
  std::string name_;
};

int main() {
  // 问：这行代码拷贝了几次 std::string？
  std::string name = "Zhen Ding";
  Student student0(name);

  // 答：
  //!  1. 参数是 const std::string &，传入左值，没发生拷贝。
  //   2. name_(name) 做了一次拷贝。

  // 问：这行代码拷贝了几次 std::string？
  Student student1(std::string("Zhen Ding"));

  // 答：
  //!  1. 参数是 const std::string &，传入“纯净”右值，延长生命周期，没发生拷贝。
  //   2. name_(name) 做了一次拷贝。

  return 0;
}
