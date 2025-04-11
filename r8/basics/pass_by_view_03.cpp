#include <iostream>
#include <span>
#include <vector>

void Print(const std::span<int> &vec) {
  for (const auto &v : vec)
    std::cout << v << " ";
  std::cout << std::endl;
}

int main() {
  std::vector<int> vec0 = {0, 1, 2, 3, 4};
  int vec1[5] = {0, 1, 2, 3, 4};

  Print(vec0);
  Print(vec1);

  return 0;
}
