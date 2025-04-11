/*

  ! 请使用 g++ -std=c++20 来编译。

  ! Baseline:
  ! 1. A "view" is a non-owning accessor of some owning resource.

*/

#include <iostream>
#include <span>
#include <vector>

int main() {
  // 我是一个拥有 5 个元素的数组。
  //! 我真正地拥有整个数组 (owning)。
  std::vector<int> vec(5);

  // 我叫 data，是一个指针，感谢 vec 大哥施舍，他愿意把数组借给我。
  //! 但我并不拥有这个数组 (non-owning)。
  int *data = vec.data();

  // 我叫 view (视图)，是一个“跨度” (span)，感谢 vec 大哥施舍，他愿意把数组借给我。
  //! 但我也不拥有这个数组 (non-owning)。
  std::span<int> view = vec;

  // vec : 你们随便用吧，除了别调用 free，其他什么都行。
  // data: 坏，我不知道大哥的数组里有多少元素啊？
  // view: 嘿嘿嘿，我知道元素的数量，这下我就能冒充大哥了呢。

  for (size_t i = 0; i < view.size(); ++i)
    view[i] = i;

  for (const auto &v : view)
    std::cout << v << std::endl;

  //! 感受一下上面那个小故事。
  //! 这就是为什么我们给它取名叫 view (视图)。

  return 0;
}
