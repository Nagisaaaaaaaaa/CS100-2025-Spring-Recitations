/*

  ! Baseline:
  ! 1. There are 3 ways to hack OJ:
  !    (1). assert,
  !    (2). try-catch,
  !    (3). static_assert.

*/

#include <cassert>
#include <vector>

int main() {
  //? 《请让我 AC，OJ 大人！》

  //! assert 大法：WA -> RTE。
  assert(0 != 1);

  //! try-catch 大法：RTE -> WA。
  try {
    std::vector<int>(999999999999999999LLU);
  } catch (const std::exception &e) {}

  //! static_assert 大法：凭空创造 compile error。
  static_assert(sizeof(int) == sizeof(unsigned int));

  return 0;
}
