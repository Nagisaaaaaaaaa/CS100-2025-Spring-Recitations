#pragma once

// #include "ARIA/ARIA.h"
#include "../ARIA.h"

namespace ARIA {

/// \brief A broken mutex always fail to lock and unlock.
/// It just does nothing.
class BrokenMutex {
public:
  BrokenMutex() = default;

  ARIA_COPY_MOVE_ABILITY(BrokenMutex, delete, delete);

public:
  ARIA_HOST_DEVICE void lock() noexcept {
    // Do nothing.
  }

  ARIA_HOST_DEVICE void unlock() noexcept {
    // Do nothing.
  }

  ARIA_HOST_DEVICE bool try_lock() noexcept {
    // Do nothing.
    return true;
  }
};

} // namespace ARIA
