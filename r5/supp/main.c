#include <assert.h>
#include <stdbool.h>

// Helper macros.
#define __MY_EXPAND(x) x

#define __MY_NUM_OF_HELPER(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _, ...) _
#define __MY_CONCAT_HELPER(x, y)                                                                          x##y

#define __MY_COND_0(x, y)     y
#define __MY_COND_1(x, y)     x
#define __MY_COND_false(x, y) y
#define __MY_COND_true(x, y)  x

//
//
//
/// \brief Get number of the given args.
///
/// \example ```c
/// static_assert(MY_NUM_OF(a, b) == 2);
/// static_assert(MY_NUM_OF(a, b, c) == 3);
/// ```
#define MY_NUM_OF(...)                                                                                                 \
  __MY_EXPAND(__MY_NUM_OF_HELPER(__VA_ARGS__, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1))

/// \brief Concatenate `x` and `y`.
///
/// \example ```c
/// static_assert(MY_CONCAT(114, 514) == 114514);
/// ```
#define MY_CONCAT(x, y) __MY_CONCAT_HELPER(x, y)

/// \brief Create an anonymous name based on x.
///
/// \example ```c
/// class MY_ANON(Name) {
/// ...
/// };
/// ```
///
/// \see Property.h
#define MY_ANON(x) MY_CONCAT(x, __LINE__)

/// \brief Create a precompile-time `cond ? x : y`.
///
/// \example ```c
/// int five = MY_COND(MY_IS_HOST_CODE, 5, 6); // Can be `0`, `1`, `false`, `true` here.
/// EXPECT_EQ(five, 5);
/// ```
#define MY_COND(cond, x, y) __MY_EXPAND(MY_CONCAT(__MY_COND_, cond))(x, y)

/// \brief Create a precompile-time `if (cond) x`.
///
/// \example ```c
/// MY_IF(MY_IS_HOST_CODE, printf("Is host code here\n")); // Can be `0`, `1`, `false`, `true` here.
/// ```
#define MY_IF(cond, x) MY_COND(cond, x, )

//
//
//
/// \brief Mark unimplemented code.
///
/// \example ```c
/// MY_UNIMPLEMENTED;
/// ```
#define MY_UNIMPLEMENTED                                                                                               \
  do {                                                                                                                 \
    fmt::print(stderr, "Reached unimplemented code at [{}:{}]\n", __FILE__, __LINE__);                                 \
    std::abort();                                                                                                      \
  } while (0)

#if !defined(NDEBUG)
  #if MY_IS_DEVICE_CODE
    #define __MY_ASSERT1(cond)                                                                                         \
      do {                                                                                                             \
        if (!(cond)) {                                                                                                 \
          printf("Assertion (%s) failed at [%s:%d]\n", #cond, __FILE__, __LINE__);                                     \
          assert(false);                                                                                               \
        }                                                                                                              \
      } while (0)

    #define __MY_ASSERT2(cond, explanation)                                                                            \
      do {                                                                                                             \
        if (!(cond)) {                                                                                                 \
          printf("Assertion (%s) failed at [%s:%d] (" explanation ")\n", #cond, __FILE__, __LINE__);                   \
          assert(false);                                                                                               \
        }                                                                                                              \
      } while (0)
  #else
    #define __MY_ASSERT1(cond)                                                                                         \
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

    #define __MY_ASSERT2(cond, explanation)                                                                            \
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
  /// \example ```c
  /// MY_ASSERT(a == 1);
  /// MY_ASSERT(a == 1, "`a` does not equals to 1");
  /// ```
  #define MY_ASSERT(...) __MY_EXPAND(__MY_EXPAND(MY_CONCAT(__MY_ASSERT, MY_NUM_OF(__VA_ARGS__)))(__VA_ARGS__))
#else
  #define MY_ASSERT(...) ((void)0)
#endif // !defined(NDEBUG)

//
//
//
//
//
int main() {
  static_assert(MY_NUM_OF(a) == 1);
  static_assert(MY_NUM_OF(a, b) == 2);
  static_assert(MY_NUM_OF(a, b, c) == 3);

  static_assert(MY_CONCAT(114, 514) == 114514);

  return 0;
}
