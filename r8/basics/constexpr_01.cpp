#include <cassert>
#include <vector>

int main() {
  assert(0 != 1);

  try {
    std::vector<int>(999999999999999999LLU);
  } catch (const std::exception &e) {}

  static_assert(sizeof(int) == sizeof(unsigned int));

  return 0;
}
