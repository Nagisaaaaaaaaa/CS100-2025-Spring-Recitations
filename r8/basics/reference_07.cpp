//? 《右值终末旅行》

#include <string>

class Student {
public:
  //! 我们只需要调用一次 std::move 就能够得到最优解！
  //! name_(std::move(name)) 这段代码的意思是：
  //! 让 name_ 直接“夺舍”掉 name，从此，name 名存实亡！
  //! 所以，std::move 这个函数的意思是“夺舍”，跟“移动”没有任何关系。
  explicit Student(std::string name) : name_(std::move(name)) {}

private:
  std::string name_;
};

int main() {
  // 那我问你，调用构造函数会拷贝几次 std::string？
  std::string name("Zhen Ding");
  Student student0(name);

  // 答案：
  //   1. 参数是 std::string name，传入左值，做了一次拷贝。
  //!  2. name_(std::move(name))，直接“掠夺”，没发生拷贝。

  // 那我问你，调用构造函数会拷贝几次 std::string？
  Student student1(std::string("Zhen Ding"));

  // 答案：
  //!  1. 参数是 std::string name，传入“纯净”右值，没发生拷贝。
  //!  2. name_(std::move(name))，直接“掠夺”，没发生拷贝。

  return 0;
}
