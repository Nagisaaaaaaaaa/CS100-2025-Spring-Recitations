#include <string>

//? 《右值终末旅行》

void Func0(std::string) {}

void Func1(const std::string &) {}

int main() {
  // 我们先构造了一个 std::string，然后将它作为参数传给函数。
  //! 那我问你，传参的时候，有没有拷贝？调用了什么函数？
  Func0(std::string("QAQ"));

  // 那如果用 const & 延长右值生命周期呢？
  //! 那我问你，传参的时候，有没有拷贝？调用了什么函数？
  Func1(std::string("QAQ"));

  //! 答案：
  //!   和前面 Square0 和 Square1 的例子没有任何区别。
  //!   1. Func0 是“孤魂野鬼找地方住”。
  //!   2. Func1 是用 const & 延长右值生命周期。
  //!   所以：
  //!
  //!   传 参 的 时 候 没 有 调 用 任 何 函 数！
  //!   也 没 有 任 何 拷 贝！

  return 0;
}
