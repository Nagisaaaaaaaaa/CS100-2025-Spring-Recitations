/*

  ! Baseline:
  ! 1. Why we need template.

*/

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

int main() {
  VectorInt vecI{new int[5]};
  VectorDouble vecD{new double[5]};

  return 0;
}
