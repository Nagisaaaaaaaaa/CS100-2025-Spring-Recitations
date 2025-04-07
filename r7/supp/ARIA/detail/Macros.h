#pragma once

/// \file
/// \brief This file introduces a collection of commonly used macros.
//
//
//
//
//
#include <fmt/core.h>

// Compilers.

/// \brief Whether clang is compiling the code.
#ifdef __clang__
  #define ARIA_CLANG __clang_major__
#else
  #define ARIA_CLANG 0
#endif // __clang__

/// \brief Whether ICC (Intel C++ Compiler) is compiling the code.
#ifdef __INTEL_COMPILER
  #define ARIA_ICC __INTEL_COMPILER
#else
  #define ARIA_ICC 0
#endif // __INTEL_COMPILER

/// \brief Whether MSVC is compiling the code.
#if defined(_MSC_VER) && !ARIA_CLANG && !ARIA_ICC
  #define ARIA_MSVC _MSC_VER
#else
  #define ARIA_MSVC 0
#endif

/// \brief Whether gcc is compiling the code.
#if defined(__GNUC__) && !ARIA_CLANG && !ARIA_ICC
  #define ARIA_GCC __GNUC__
#else
  #define ARIA_GCC 0
#endif

//
//
//
// Compiler related macros.

// clang and gcc.
#if ARIA_CLANG || ARIA_GCC
  #define ARIA_EXPORT __attribute__((visibility("default")))
  #define ARIA_IMPORT

  #define ARIA_NO_INLINE    __attribute__((noinline))
  #define ARIA_FORCE_INLINE __attribute__((always_inline)) inline

  #define ARIA_UNREACHABLE __builtin_unreachable()
#endif

// ICC and MSVC.
#if ARIA_ICC || ARIA_MSVC
  #define ARIA_EXPORT __declspec(dllexport)
  #define ARIA_IMPORT __declspec(dllimport)

  #define ARIA_NO_INLINE    __declspec(noinline)
  #define ARIA_FORCE_INLINE __forceinline

  #define ARIA_UNREACHABLE __assume(0)
#endif

//
//
//
//
//
// CUDA.

#if defined(__CUDACC__)
  #define ARIA_KERNEL __global__
  #define ARIA_HOST   __host__
  #define ARIA_DEVICE __device__
#else
  #define ARIA_KERNEL
  #define ARIA_HOST
  #define ARIA_DEVICE
#endif
#define ARIA_HOST_DEVICE ARIA_HOST ARIA_DEVICE

#if defined(__CUDA_ARCH__)
  #define ARIA_IS_DEVICE_CODE 1
  #define ARIA_IS_HOST_CODE   0
  #define ARIA_CONST          __constant__
  #define ARIA_NOEXCEPT       noexcept(true)
#else
  #define ARIA_IS_DEVICE_CODE 0
  #define ARIA_IS_HOST_CODE   1
  #define ARIA_CONST
  #define ARIA_NOEXCEPT noexcept(false)
#endif

//
//
//
//
//
// Common.

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
//
//
// The copy and swap idiom.
// See https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom.

/// \brief Set copy ability of a class.
///
/// \example ```cpp
/// class A {
/// public:
///   ARIA_COPY_ABILITY(A, delete);
///   ARIA_MOVE_ABILITY(A, default);
/// };
/// ```
#define ARIA_COPY_ABILITY(cls, copyAbility)                                                                            \
  cls(cls const &) = copyAbility;                                                                                      \
  cls &operator=(cls const &) = copyAbility

/// \brief Set move ability of a class.
///
/// \example ```cpp
/// class A {
/// public:
///   ARIA_COPY_ABILITY(A, delete);
///   ARIA_MOVE_ABILITY(A, default);
/// };
/// ```
#define ARIA_MOVE_ABILITY(cls, moveAbility)                                                                            \
  cls(cls &&) ARIA_NOEXCEPT = moveAbility;                                                                             \
  cls &operator=(cls &&) ARIA_NOEXCEPT = moveAbility

/// \brief Set copy and move ability of a class.
///
/// \example ```cpp
/// class A {
/// public:
///   ARIA_COPY_MOVE_ABILITY(A, delete, default);
/// };
/// ```
#define ARIA_COPY_MOVE_ABILITY(cls, copyAbility, moveAbility)                                                          \
  ARIA_COPY_ABILITY(cls, copyAbility);                                                                                 \
  ARIA_MOVE_ABILITY(cls, moveAbility)

//
//
//
//
//
// Assertions and exceptions.

/// \brief A wrapper of `static_assert(false, message)`.
///
/// \example ```cpp
/// ARIA_STATIC_ASSERT_FALSE("Should not compile");
/// ```
///
/// \note This macro is helpful because `static_assert(false, ...)` will
/// always be evaluated even in a `if constexpr` branch.
/// Something like this: `void Func() { if constexpr (false) { static_assert(false, ...); } }`
/// will always get compile error, even if this branch is never reached.
/// So, template is used to postpone it to the instantiation time.
#define ARIA_STATIC_ASSERT_FALSE(message)                                                                              \
  []<bool assertion>() { static_assert(assertion, message); }.template operator()<false>()

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

/// \brief Throw an exception with automatically formatted file name and line number.
///
/// \example ```cpp
/// ARIA_THROW(std::runtime_error, "Runtime error");
/// ```
#define ARIA_THROW(err, ...)                                                                                           \
  throw __ARIA_EXPAND(err)(fmt::format("Exception at [{}:{}]: ", __FILE__, __LINE__) + fmt::format(__VA_ARGS__))

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
