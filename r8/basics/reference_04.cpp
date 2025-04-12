#include <string>

//? 《右值终末旅行》

void Func(std::string) {}

int main() {
  // 我们先构造了一个 std::string，然后将它传给 Func。
  //! 那我问你，传参的时候，有没有拷贝？调用了什么函数？
  Func(std::string("QAQ"));

  //! 原因很复杂，我们今天只说结论：
  //!   传 参 的 时 候 没 有 调 用 任 何 函 数！
  //!   也 没 有 任 何 拷 贝！
  //!   (因为它是个很纯净的右值嘛)

  return 0;
}
