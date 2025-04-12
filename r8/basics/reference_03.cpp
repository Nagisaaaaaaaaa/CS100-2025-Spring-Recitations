#include <string>

//? 《右值终末旅行》

int main() {
  // 等号的右手边，构造了一个 std::string。
  //! 那我问你，这里的等号，调用了什么函数？Copy？
  std::string str = std::string("QAQ");

  //! 原因很复杂，我们今天只说结论：
  //!   这 个 等 号 没 有 调 用 任 何 函 数！

  return 0;
}
