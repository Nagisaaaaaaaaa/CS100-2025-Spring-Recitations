/*

  ! Baseline:
  ! 1. Why we need template.

*/

// 我们目前为止看到的 Vector，都是 int 的数组。
// 如果想让 Vector 支持各种类型，那岂不是得这么写……

// 给 int 写一份。
struct VectorInt {
  int *data;

  ~VectorInt() { delete[] data; }
};

// 给 double 写一份。
struct VectorDouble {
  double *data;

  ~VectorDouble() { delete[] data; }
};

// 这也太累了吧……
//! 这就是为什么 C++ 引入了模板。

int main() {
  VectorInt vecI{new int[5]};
  VectorDouble vecD{new double[5]};

  return 0;
}
