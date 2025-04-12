/*

  ! Baseline:
  ! 1. Const reference can extend the lifetime of an r-value.

*/

//? 《右值终末旅行》

int main() {
  // 为什么一个右值能赋给一个左值呢？
  const int &v = 5;

  // 这里难道我们对右值 "5" 取地址了？
  const int *ptr = &v;

  //! 原因：
  //! 1. const & 可以“延长右值的生命周期”。
  //! 2. 什么叫“延长生命周期”呢？你可以想象发生了类似这样的事情：
  {
    // 为了“延长生命周期”，编译器可能偷偷给孤魂野鬼安排了个临时住处。
    int temp = 5;

    // 这里的 const & 则引用到了临时住处。
    const int &v = temp;

    // 临时住处自然也可以取地址。
    const int *ptr = &temp;
  }

  //! 只有 const reference 可以，non-const reference 可不行。
  //! 因为 C++ 设计师认为，non-const reference 就只能引用有名有姓的大人物，
  // int &v = 5;

  return 0;
}
