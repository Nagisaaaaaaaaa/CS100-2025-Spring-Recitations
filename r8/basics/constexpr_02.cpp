/*

  ! Baseline:
  ! 1. Always use `constexpr` to define constants instead of macros.
  ! 2. `constexpr` 的意思不是“编译时”，而是“在编译时求值”。

*/

#include <cassert>
#include <iostream>

int main() {
  //? 《我们仍未知道那天所看见的常量的名字。》

  {
    // 我是一个“运行时”的数组，只存活于“运行时”。
    // 我有实体，当程序运行到这儿时，会真实地出现在栈上。
    int v[3] = {0, -1, -2};

    // 因为是“运行时”的，所以只支持 assert，不支持 static_assert。
    assert(v[0] == 0);
    assert(v[1] == -1);
    assert(v[2] == -2);
    std::cout << v << std::endl; // 看看地址。
  }

  {
    // 我是一个“用宏来定义”的数组 (并非数组)，只存活于“预编译时”。
    // 我没有实体，一眼就看得出来嘛。
#define v0 0
#define v1 -1
#define v2 -2

    // 因为是“预编译时”的，所以支持 static_assert。
    static_assert(v0 == 0);
    static_assert(v1 == -1);
    static_assert(v2 == -2);
  }

  {
    //! 我是一个“在编译时求值”的数组，我在“编译时”就出生了，但我不知道自己能活多久。
    //! 我既可能没有实体，无法活到“运行时”；也可能有实体，能活到“运行时”。
    //!
    //! 都是编译器大人说了算的，我决定不了自己能活到什么时候。
    //! 但我尽可能地让大家不会察觉到这件事情，努力地装作自己也是一个“运行时”的数组。
    constexpr int v[3] = {0, -1, -2};

    static_assert(v[0] == 0);
    static_assert(v[1] == -1);
    static_assert(v[2] == -2);
    std::cout << v << std::endl; // 看看地址。
  }

  return 0;
}
