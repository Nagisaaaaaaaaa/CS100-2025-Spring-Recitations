#include <cassert>

int main() {
  {
    int v[3] = {0, -1, -2};

    assert(v[0] == 0);
    assert(v[1] == -1);
    assert(v[2] == -2);
    assert(sizeof(v) == sizeof(int) * 3);
  }

  {
    constexpr int v[3] = {0, -1, -2};

    static_assert(v[0] == 0);
    static_assert(v[1] == -1);
    static_assert(v[2] == -2);
    static_assert(sizeof(v) == sizeof(int) * 3);
  }

  return 0;
}
