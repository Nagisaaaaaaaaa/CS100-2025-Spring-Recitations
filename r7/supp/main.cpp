#include "ARIA/Registry.h"

#include <vector>

struct Vec {
  int x, y;
};

struct Tank : public ARIA::Registry<Tank> {
  using Base = Registry<Tank>;
  using Base::range;
  using Base::size;

  Vec pos;
};

int main() {
  // 0.
  std::cout << Tank::size() << std::endl;

  {
    // 0 + 1 = 1.
    Tank tank;
    std::cout << Tank::size() << std::endl;

    {
      // 1 + 5 = 6.
      std::vector<Tank> tanks(5);
      std::cout << Tank::size() << std::endl;

      for (const auto &tank : Tank::range()) {
        // ...
      }
    }

    // 6 - 5 = 1.
    std::cout << Tank::size() << std::endl;
  }

  // 1 - 1 = 0.
  std::cout << Tank::size() << std::endl;

  return 0;
}
