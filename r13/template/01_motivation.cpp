#include <cstddef>

//? 《Template/stay night》

//! 为什么 C++ 引入了模板？

// 1. 如何让 Dynarray 支持 int 以外的类型？
class Dynarray {
public:
  Dynarray() = default;

private:
  int *data_ = nullptr;
  size_t size_ = 0;
};

void Print(const Dynarray &v) {}

// 2. 如何把 Vec3i (3 个 int) 拓展到任意类型？任意数量？
class Vec3i {
public:
  Vec3i() = default;

private:
  int v_[3];
};

int main() {
  Dynarray arr;

  Print(arr);

  Vec3i v;

  return 0;
}
