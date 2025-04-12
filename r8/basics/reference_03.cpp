#include <string>

//? 《右值终末旅行》

int main() {
  // 等号的右手边，构造了一个 std::string。
  //! 那我问你，这里的等号，有没有拷贝？调用了什么函数？
  std::string str = std::string("QAQ");

  //! 答案：
  //!   这个例子和 int x = 5 没有任何区别，
  //!   它们本质上都是“孤魂野鬼找地方住”，所以：
  //!
  //!   这 个 等 号 没 有 调 用 任 何 函 数！
  //!   也 没 有 任 何 拷 贝！

  //! 所以我们也可以用 const & 来延长孤魂野鬼的生命周期。
  const std::string &str = std::string("QAQ");

  return 0;
}
