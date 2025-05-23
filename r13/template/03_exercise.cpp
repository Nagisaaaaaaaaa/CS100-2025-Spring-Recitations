#include <iostream>

//? 《Template/stay night》

// 请完整地实现：
//   template <typename T, size_t n>
//   class Vec;

//
//
//
//
//
// 答案：

template <typename T, size_t n>
class Vec {
public:
  Vec() = default;

  // ...

public:
  const T &operator[](size_t i) const { return data_[i]; }

  T &operator[](size_t i) { return data_[i]; }

  friend Vec operator+(const Vec &lhs, const Vec &rhs) {
    Vec res;
    for (size_t i = 0; i < n; ++i)
      res[i] = lhs[i] + rhs[i];
    return res;
  }

  // ...

private:
  T data_[n];
};

template <typename T>
using Vec3 = Vec<T, 3>;

using Vec3i = Vec3<int>;

int main() {
  Vec3i v0;
  v0[0] = 0, v0[1] = 1, v0[2] = 2;

  Vec3i v1;
  v1[0] = 1, v1[1] = 3, v1[2] = 5;

  Vec3i v2 = v0 + v1;
  printf("%d %d %d\n", v2[0], v2[1], v2[2]);
}
