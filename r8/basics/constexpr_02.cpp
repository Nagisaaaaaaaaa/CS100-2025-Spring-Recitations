#include <cassert>

int main() {
  //? 《我们仍未知道那天所看见的常量的名字。》

  {
    // 这是一个“运行时”的数组，活在“运行时”。
    // 它有实体，当程序运行到这儿时，会真实地出现在栈上。
    int v[3] = {0, -1, -2};

    // 因为是“运行时”的，所以只支持 assert。
    assert(v[0] == 0);
    assert(v[1] == -1);
    assert(v[2] == -2);
    assert(*v == 0);
    assert(sizeof(v) == sizeof(int) * 3);
  }

  {
    // 这是一个“用宏来表示”的数组，活在“预编译时”。
    // 它没有实体，仿佛幽灵一般。
#define v0 0
#define v1 -1
#define v2 -2

    // 因为是“预编译时”的，所以支持 static_assert。
    static_assert(v0 == 0);
    static_assert(v1 == -1);
    static_assert(v2 == -2);
  }

  {
    // 这是一个“编译时”的数组，活在“编译时”。
    // 它没有实体，但没有任何人知道这件事情。
    constexpr int v[3] = {0, -1, -2};

    static_assert(v[0] == 0);
    static_assert(v[1] == -1);
    static_assert(v[2] == -2);
    static_assert(*v == 0);
    static_assert(sizeof(v) == sizeof(int) * 3);
  }

  return 0;
}
