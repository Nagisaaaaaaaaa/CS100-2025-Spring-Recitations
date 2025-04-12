//? 《右值终末旅行》

#include <string>

class Student {
public:
  explicit Student(std::string name) : name_(name) {}

private:
  std::string name_;
};

int main() {
  // 那我问你，调用构造函数会拷贝几次 std::string？
  std::string name("Zhen Ding");
  Student student0(name);

  // 答案：
  //   1. 参数是 std::string，传入左值，一次拷贝。
  //   2. name_(name)，一次拷贝。

  // 那我问你，调用构造函数会拷贝几次 std::string？
  Student student1(std::string("Zhen Ding"));

  // 答案：
  //!  1. 参数是 std::string，“孤魂野鬼找地方住”，没有拷贝。
  //   2. name_(name)，一次拷贝。

  return 0;
}
