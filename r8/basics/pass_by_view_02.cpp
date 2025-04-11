#include <iostream>
#include <vector>

void Print(const std::vector<int> &vec) {
  for (const auto &v : vec)
    std::cout << v << " ";
  std::cout << std::endl;
}

void Print(const int *vec, size_t n) {
  for (size_t i = 0; i < n; ++i)
    std::cout << vec[i] << " ";
  std::cout << std::endl;
}

int main() {
  std::vector<int> vec0 = {0, 1, 2, 3, 4};
  int vec1[5] = {0, 1, 2, 3, 4};

  Print(vec0);
  Print(vec1, 5);

  return 0;
}
