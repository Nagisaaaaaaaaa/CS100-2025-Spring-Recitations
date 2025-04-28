#pragma once

/// \file
/// \warning "Higher beings, these words are for you alone.
/// Beyond this point you enter the land of ARIA.
/// Step across this threshold and obey our laws."

//
//
//
//
//
// #include "ARIA/detail/Macros.h"
#include "./detail/Macros.h"

#include <cstddef>
#include <cstdint>
#include <utility>

namespace ARIA {

/// \brief Always use `int8` instead of `char`.
using int8 = int8_t;

/// \brief Always use `uint8` instead of `unsigned char`.
using uint8 = uint8_t;

/// \brief Always use `int16` instead of `short`.
using int16 = int16_t;

/// \brief Always use `uint16` instead of `unsigned short`.
using uint16 = uint16_t;

/// \brief Always use `uint` instead of `unsigned`.
using uint = uint32_t;

/// \brief Always use `int64` instead of `int64_t`.
using int64 = int64_t;

/// \brief Always use `uint64` instead of `uint64_t`.
using uint64 = uint64_t;

static_assert(sizeof(int8) == sizeof(uint8), "Size of `int8` and `uint8` should be the same");
static_assert(sizeof(int16) == sizeof(uint16), "Size of `int16` and `uint16` should be the same");
static_assert(sizeof(int) == sizeof(uint), "Size of `int` and `uint` should be the same");
static_assert(sizeof(int64) == sizeof(uint64), "Size of `int64` and `uint64` should be the same");

//
//
//
/// \brief `Real` is a universal number type defined by cmake options.
using Real = float; // ${aria_real_type};

/// \brief Use `100.0_R` to define a `Real` equals to one hundred.
ARIA_HOST_DEVICE constexpr Real operator"" _R(long double value) {
  return static_cast<Real>(value);
}

/// \brief Use `100_R` to define a `Real` equals to one hundred.
ARIA_HOST_DEVICE constexpr Real operator"" _R(unsigned long long value) {
  return static_cast<Real>(value);
}

//
//
//
/// \brief Overload the lambda functions.
///
/// \example ```cpp
/// std::visit(
///   Overload{[](auto arg) { std::cout << arg << std::endl; },
///            [](double arg) { std::cout << std::fixed << arg << std::endl; },
///            [](const std::string &arg) { std::cout << std::quoted(arg) << std::endl; }},
///   v);
/// ```
///
/// \details This implementation is based on https://en.cppreference.com/w/cpp/utility/variant/visit.
template <class... Ts>
struct Overload : Ts... {
  using Ts::operator()...;
};

template <class... Ts>
Overload(Ts...) -> Overload<Ts...>;

//
//
//
/// \brief A type wrapper which converts all "dot" calls to "arrow" calls.
///
/// \example ```
/// ArrowProxy v{std::vector<int>{1, 2, 3}};
/// std::cout << v->size() << std::endl;
/// ```
template <typename T>
class ArrowProxy {
public:
  ARIA_HOST_DEVICE ArrowProxy(T &&t) noexcept : t(std::move(t)) {}

public:
  ARIA_HOST_DEVICE const T *operator->() const noexcept { return &t; }

  ARIA_HOST_DEVICE T *operator->() noexcept { return &t; }

private:
  T t;
};

//
//
//
/// \brief A commonly-used policy, means whether the class is for host use.
struct SpaceHost {};

/// \brief A commonly-used policy, means whether the class is for device use.
struct SpaceDevice {};

/// \brief A commonly-used policy, means whether the class is thread-unsafe.
struct ThreadUnsafe {};

/// \brief A commonly-used policy, means whether the class is thread-safe.
struct ThreadSafe {};

//
//
//
/// \brief A commonly-used parameter type, means whether something should be set to "on".
struct On {};

/// \brief A commonly-used parameter type, means whether something should be set to "off".
struct Off {};

//
//
//
/// \brief Compute `abs(v)`, where `v` is determined at compile-time.
template <auto v>
ARIA_HOST_DEVICE static consteval auto Abs() {
  return v < decltype(v){} ? -v : v;
}

/// \brief Compute `a^n`, where `n` is determined at compile-time.
template <uint n, typename T>
ARIA_HOST_DEVICE static constexpr T Pow(const T &a) {
  if constexpr (n == 0)
    return static_cast<T>(1);

  T half = Pow<n / 2>(a);
  if constexpr (n % 2)
    return half * half * a;
  else
    return half * half;
}

} // namespace ARIA
