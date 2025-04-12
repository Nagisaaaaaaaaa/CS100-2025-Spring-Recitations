/*

  ! Baseline:
  ! 1. How many copies in this example?

*/

#include <string>

//? 《右值终末旅行》

class Student {
public:
  //! 如果改为 const std::string & 呢？
  explicit Student(const std::string &name) : name_(name) {}

private:
  std::string name_;
};

int main() {
  // 那我问你，调用构造函数会拷贝几次 std::string？
  std::string name("Zhen Ding");
  Student student0(name);

  // 答案：
  //!  1. 参数是 const std::string &，传入左值，没有拷贝。
  //   2. name_(name)，一次拷贝。

  // 那我问你，调用构造函数会拷贝几次 std::string？
  Student student1(std::string("Zhen Ding"));

  // 答案：
  //!  1. 参数是 const std::string &，延长右值生命周期，没有拷贝。
  //   2. name_(name)，一次拷贝。

  return 0;
}
