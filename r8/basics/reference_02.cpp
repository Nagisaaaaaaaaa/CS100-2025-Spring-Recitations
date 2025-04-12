/*

  ! Baseline:
  ! 1. Const reference can extend the lifetime of an r-value.

*/

//? 《右值终末旅行》

int Square0(int x) {
  return x * x;
}

int Square1(const int &x) {
  return x * x;
}

int main() {
  // 这个当然可以了。
  int v0 = Square0(5);

  // 但为什么这个也可以呢？
  //!  因为 const & 能够延长右值的生命周期！
  int v1 = Square1(5);

  // 分析一波 Square0：
  //   1. "5" 是一只孤魂野鬼，它作为参数传给 Square0。
  //   2. 由于 Square0 接收 int，所以会做一次拷贝。
  //!  3. 拷贝结束之后，孤魂野鬼便消散了。

  // 分析一波 Square1:
  //   1. "5" 是一只孤魂野鬼，它作为参数传给 Square1。
  //!  2. 由于 Square0 接收 const int &，所以延长了 "5" 的生命周期。
  //!  3. 直到函数运行完毕，孤魂野鬼才消散。

  return 0;
}
