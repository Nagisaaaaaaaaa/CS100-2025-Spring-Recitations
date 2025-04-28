/*

  ! Baseline:
  ! 孩子们，答应我别这么写好吗？

*/

// C++ 是一门允许函数重载的语言。
//! 我们上节课介绍了，函数重载是引入 rvalue-reference 的罪魁祸首。
//! 没想到竟然还有高手。

// 摘录自官方习题课 PPT。
int fun(float a) { /*...*/ }

int fun(float a, float b) { /*...*/ }

int fun(float x, int y = 5) { /*...*/ }

int main() {
  float p = 4.5, t = 10.5;
  int s = 30;
  fun(p, s);
  fun(t);
  return 0;
}

//* 任何事物都是具有两面性的：
//* 1. 一方面，我们享受着函数重载带来的便利。
//* 2. 另一方面，我们不得不承受代价。
//*
//* 但很不幸的是，代价远比我们想象中的大。
