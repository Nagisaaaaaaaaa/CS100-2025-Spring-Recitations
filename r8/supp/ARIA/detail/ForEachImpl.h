#pragma once

// #include "ARIA/Constant.h"
#include "../Constant.h"

namespace ARIA {

namespace for_each::detail {

// Recursively unroll.
template <auto start, auto end, auto inc, typename F>
ARIA_HOST_DEVICE constexpr void ForEachImpl(F &&f) {
  if constexpr (start < end) {
    // Conditionally calls `f` with parameter or template parameter.
    if constexpr (std::is_invocable_v<F, C<start>>)
      f(C<start>());
    else
      f.template operator()<start>();

    // `++i;`.
    ForEachImpl<start + inc, end, inc>(std::forward<F>(f));
  }
}

} // namespace for_each::detail

} // namespace ARIA
