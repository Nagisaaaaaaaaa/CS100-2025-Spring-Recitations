#include "ARIA/Registry.h"

#include <vector>

struct Vec {
  int x, y;
};

struct Tank : public ARIA::Registry<Tank> {
  using Base = ARIA::Registry<Tank>;
  using Base::range;
  using Base::size;

  Vec pos;
};

int main() {
  // 0.
  std::cout << Tank::size() << std::endl;

  {
    // 0 + 2 = 2.
    Tank tank0;
    Tank tank1;
    std::cout << Tank::size() << std::endl;

    {
      // 2 + 5 = 7.
      std::vector<Tank> tanks(5);
      std::cout << Tank::size() << std::endl;

      // Iterate through all the tanks.
      for (const auto &tank : Tank::range()) {
        // ...
      }
    }

    // 7 - 5 = 2.
    std::cout << Tank::size() << std::endl;
  }

  // 2 - 2 = 0.
  std::cout << Tank::size() << std::endl;

  return 0;
}
