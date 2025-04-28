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
