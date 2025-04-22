#include "dynarray_02.hpp"
#include <exception>
#include <iostream>

int main() {
  // 我们拥有一只娇小的数组arr
  Dynarray arr(10, 5);
  try {
    // 我们在这里试图定义一只巨大的数组other
    Dynarray other(1e+10); // #1
    //! 之前的习题课我们说过，C++中我们采用异常处理机制来为程序 `兜底`
    //! 如果 #1 这里就寄了（std::bad_alloc），那么：
    //! 程序会在对应的构造函数内部停下，然后跳转到 catch
    //! 但至少，我们的 arr 完好无损

    arr = other; // #2
    //! 但如果程序在 #2 处抛出异常，那就会考验我们拷贝构造的写法！
    //! 如果处理不当，我们会发现 `arr` 中的数据被篡改或丢失。
    //! 这与我们 `try中如果失败，旧数据应该原封不动` 的期待相违背了。
  } catch (std::exception &e) { std::cout << e.what() << "\n"; }

  // 看一眼旧的数据还在不在？打印5说明正常。
  std::cout << arr.at(1) << "\n";
}
