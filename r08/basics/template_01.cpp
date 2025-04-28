/*

  ! Baseline:
  ! 1. Always use `new` and `delete` instead of `malloc` and `free`.

*/

struct Vector {
  int *data;

  ~Vector() { delete[] data; } //! 从今天开始，我们不再用 free，而是用 delete 和 delete[]。
};

int main() {
  Vector vec{new int[5]}; //! 从今天开始，我们不再用 malloc，而是用 new 和 new[]。

  return 0;
}
