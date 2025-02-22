#include <assert.h>
#include <stdbool.h>

#define __ARIA_EXPAND(x) x

// Helper macros.
#define __ARIA_NUM_OF_HELPER(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _, ...) _
#define __ARIA_CONCAT_HELPER(x, y)                                                                          x##y

#define __ARIA_COND_0(x, y)     y
#define __ARIA_COND_1(x, y)     x
#define __ARIA_COND_false(x, y) y
#define __ARIA_COND_true(x, y)  x

/// \brief Get number of the given args.
///
/// \example ```cpp
/// EXPECT_EQ(ARIA_NUM_OF(a, b), 2);
/// EXPECT_EQ(ARIA_NUM_OF(a, b, c), 3);
/// ```
#define ARIA_NUM_OF(...)                                                                                               \
  __ARIA_EXPAND(__ARIA_NUM_OF_HELPER(__VA_ARGS__, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1))

/// \brief Concatenate `x` and `y`.
///
/// \example ```cpp
/// #define SQUARE(x) ((x) * (x))
/// int number = ARIA_CONCAT(SQUARE, (2)); // Replacement: ((2) * (2))
/// ```
#define ARIA_CONCAT(x, y) __ARIA_CONCAT_HELPER(x, y)

/// \brief Create an anonymous name based on x.
///
/// \example ```cpp
/// class ARIA_ANON(Name) {
/// ...
/// };
/// ```
///
/// \see Property.h
#define ARIA_ANON(x) ARIA_CONCAT(x, __LINE__)

/// \brief Create a precompile-time `cond ? x : y`.
///
/// \example ```cpp
/// int five = ARIA_COND(ARIA_IS_HOST_CODE, 5, 6); // Can be `0`, `1`, `false`, `true` here.
/// EXPECT_EQ(five, 5);
/// ```
#define ARIA_COND(cond, x, y) __ARIA_EXPAND(ARIA_CONCAT(__ARIA_COND_, cond))(x, y)

/// \brief Create a precompile-time `if (cond) x`.
///
/// \example ```cpp
/// ARIA_IF(ARIA_IS_HOST_CODE, printf("Is host code here\n")); // Can be `0`, `1`, `false`, `true` here.
/// ```
#define ARIA_IF(cond, x) ARIA_COND(cond, x, )

//
//
//
/// \brief Mark unimplemented code.
///
/// \example ```cpp
/// ARIA_UNIMPLEMENTED;
/// ```
#define ARIA_UNIMPLEMENTED                                                                                             \
  do {                                                                                                                 \
    fmt::print(stderr, "Reached unimplemented code at [{}:{}]\n", __FILE__, __LINE__);                                 \
    std::abort();                                                                                                      \
  } while (0)

#if !defined(NDEBUG)
  #if ARIA_IS_DEVICE_CODE
    #define __ARIA_ASSERT1(cond)                                                                                       \
      do {                                                                                                             \
        if (!(cond)) {                                                                                                 \
          printf("Assertion (%s) failed at [%s:%d]\n", #cond, __FILE__, __LINE__);                                     \
          assert(false);                                                                                               \
        }                                                                                                              \
      } while (0)

    #define __ARIA_ASSERT2(cond, explanation)                                                                          \
      do {                                                                                                             \
        if (!(cond)) {                                                                                                 \
          printf("Assertion (%s) failed at [%s:%d] (" explanation ")\n", #cond, __FILE__, __LINE__);                   \
          assert(false);                                                                                               \
        }                                                                                                              \
      } while (0)
  #else
    #define __ARIA_ASSERT1(cond)                                                                                       \
      do {                                                                                                             \
        if (!(cond)) {                                                                                                 \
          fmt::print(stderr,                                                                                           \
                     "Assertion ({:s}) failed at "                                                                     \
                     "[{:s}:{:d}]\n",                                                                                  \
                     #cond, __FILE__, __LINE__);                                                                       \
          fflush(stderr);                                                                                              \
          std::abort();                                                                                                \
        }                                                                                                              \
      } while (0)

    #define __ARIA_ASSERT2(cond, explanation)                                                                          \
      do {                                                                                                             \
        if (!(cond)) {                                                                                                 \
          fmt::print(stderr,                                                                                           \
                     "Assertion ({:s}) failed at "                                                                     \
                     "[{:s}:{:d}] (" explanation ")\n",                                                                \
                     #cond, __FILE__, __LINE__);                                                                       \
          fflush(stderr);                                                                                              \
          std::abort();                                                                                                \
        }                                                                                                              \
      } while (0)
  #endif

  /// \brief Assert that the condition is true.
  ///
  /// \example ```cpp
  /// ARIA_ASSERT(a == 1);
  /// ARIA_ASSERT(a == 1, "`a` does not equals to 1");
  /// ```
  #define ARIA_ASSERT(...)                                                                                             \
    __ARIA_EXPAND(__ARIA_EXPAND(ARIA_CONCAT(__ARIA_ASSERT, ARIA_NUM_OF(__VA_ARGS__)))(__VA_ARGS__))
#else
  #define ARIA_ASSERT(...) ((void)0)
#endif // !defined(NDEBUG)

//
//
//
//
//
int main() {
  assert(false);
  return 0;
}
