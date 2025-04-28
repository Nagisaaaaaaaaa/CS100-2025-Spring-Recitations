#pragma once

/// \file
/// \brief This file introduces `class C`, a wrapper class for compile-time constants,
/// similar to `std::integral_constants` but support floating point types.
///
/// This file also defines concepts about compile-time constants, including
/// `ConstantArithmetic`, compile-time constant arithmetic type,
/// `ConstantIntegral`, compile-time constant integral type, etc.
///
/// These concepts are helpful because they can correctly handle
/// `std::integral_constant`, `C`, `cute::C`, and any other user-defined constant types.

//
//
//
//
//
// #include "ARIA/ARIA.h"
#include "./ARIA.h"

#include "../cute/numeric/integral_constant.hpp"

namespace ARIA {

/// \brief A wrapper class for compile-time constants,
/// similar to `std::integral_constants` but support floating point types.
///
/// \example ```cpp
/// C<1> a{};
/// C<3> b = a + C<2>{};
/// C<2> c = b - 1_I;
/// ```
template <auto T>
using C = cute::C<T>;

//
//
//
/// \brief A wrapper class for compile-time signed `int`.
///
/// \example ```cpp
/// Int<1> a{};
/// Int<3> b = a + Int<2>{};
/// Int<2> c = b - 1_I;
/// ```
template <int v>
using Int = C<v>;

//
//
//
/// \brief A wrapper class for compile-time `unsigned int`.
///
/// \example ```cpp
/// UInt<1> a{};
/// UInt<3> b = a + UInt<2>{};
/// UInt<2> c = b - 1_U;
/// ```
template <uint v>
using UInt = C<v>;

//
//
//
//
//
namespace constant::detail {

template <typename T, char... cs>
consteval auto make_integral_udl() {
  T result = 0;
  ((result = result * 10 + (cs - '0')), ...);
  return result;
}

} // namespace constant::detail

//
//
//
//
//
/// \brief UDL for constant signed integers.
///
/// \example ```cpp
/// auto one = 1_I;
/// static_assert(std::is_same_v<decltype(one), C<1>>);
/// static_assert(std::is_same_v<decltype(one), Int<1>>);
/// static_assert(one == 1_I);
/// static_assert(one == 1_U);
/// ```
template <char... cs>
consteval auto operator""_I() {
  constexpr auto value = constant::detail::make_integral_udl<int, cs...>();
  return Int<value>{};
}

/// \brief UDL for constant unsigned integers.
///
/// \example ```cpp
/// auto one = 1_U;
/// static_assert(std::is_same_v<decltype(one), C<1U>>);
/// static_assert(std::is_same_v<decltype(one), UInt<1>>);
/// static_assert(one == 1_I);
/// static_assert(one == 1_U);
/// ```
template <char... cs>
consteval auto operator""_U() {
  constexpr auto value = constant::detail::make_integral_udl<uint, cs...>();
  return UInt<value>{};
}

//
//
//
//
//
//
//
//
//
template <typename T>
struct is_constant_arithmetic : std::false_type {};

template <typename T>
  requires(std::is_arithmetic_v<decltype(decltype(T{})::value)> && std::is_const_v<decltype(decltype(T{})::value)>)
struct is_constant_arithmetic<T> : std::true_type {};

template <typename T>
constexpr bool is_constant_arithmetic_v = is_constant_arithmetic<T>::value;

/// \brief Whether type `T` is a compile-time constant arithmetic type,
/// where "arithmetic" follows the rule of `std::is_arithmetic`.
///
/// \details A "compile-time constant arithmetic type" is defined as
/// types having `static` and `constexpr` or `const` arithmetic members named `value`.
/// This definition is safe enough, see the below examples.
///
/// \example ```cpp
/// struct MyIntegralConstant0 {
///   static constexpr int value = 0;
/// };
///
/// // Note, `static_assert(MyIntegralConstant1::value == 0)` may not work, but
/// // `value` is still regarded as a compile-time constant arithmetic.
/// struct MyIntegralConstant1 {
///   static const inline int value = 0;
/// };
///
/// // Non-const static variable.
/// struct MyFakeIntegralConstant {
///   static inline int value = 0;
/// };
///
/// struct MyFloatingPointConstant0 {
///   static constexpr float value = 0;
/// };
///
/// // Note, `static_assert(MyFloatingPointConstant1::value == 0.0F)` may not work, but
/// // `value` is still regarded as a compile-time constant arithmetic.
/// struct MyFloatingPointConstant1 {
///   static const inline float value = 0;
/// };
///
/// // Non-const static variable.
/// struct MyFakeFloatingPointConstant {
///   static inline float value = 0;
/// };
///
/// static_assert(ConstantArithmetic<std::true_type>);
/// static_assert(ConstantArithmetic<const std::false_type>);
/// static_assert(ConstantArithmetic<std::integral_constant<int, 0>>);
/// static_assert(ConstantArithmetic<C<2>>);
/// static_assert(ConstantArithmetic<cute::C<2>>);
/// static_assert(!ConstantArithmetic<cute::Int<2>&>);
/// static_assert(!ConstantArithmetic<cute::_3&&>);
///
/// static_assert(ConstantArithmetic<MyIntegralConstant0>);
/// static_assert(ConstantArithmetic<MyIntegralConstant1>);
/// static_assert(!ConstantArithmetic<MyFakeIntegralConstant>);
///
/// static_assert(ConstantArithmetic<MyFloatingPointConstant0>);
/// static_assert(ConstantArithmetic<MyFloatingPointConstant1>);
/// static_assert(!ConstantArithmetic<MyFakeFloatingPointConstant>);
/// ```
template <typename T>
concept ConstantArithmetic = is_constant_arithmetic_v<T>;

//
//
//
//
//
template <typename T>
struct is_constant_integral : std::false_type {};

template <typename T>
  requires(ConstantArithmetic<T> && std::is_integral_v<decltype(decltype(T{})::value)>)
struct is_constant_integral<T> : std::true_type {};

template <typename T>
constexpr bool is_constant_integral_v = is_constant_integral<T>::value;

/// \brief Whether type `T` is a compile-time constant integral type,
/// where "integral" follows the rule of `std::is_integral`.
///
/// \details A "compile-time constant integral type" is defined as
/// types having `static` and `constexpr` or `const` integral members named `value`.
/// This definition is safe enough, see the below examples.
///
/// \example ```cpp
/// struct MyIntegralConstant0 {
///   static constexpr int value = 0;
/// };
///
/// // Note, `static_assert(MyIntegralConstant1::value == 0)` may not work, but
/// // `value` is still regarded as a compile-time constant integral.
/// struct MyIntegralConstant1 {
///   static const inline int value = 0;
/// };
///
/// // Non-const static variable.
/// struct MyFakeIntegralConstant {
///   static inline int value = 0;
/// };
///
/// struct MyFloatingPointConstant0 {
///   static constexpr float value = 0;
/// };
///
/// // Note, `static_assert(MyFloatingPointConstant1::value == 0.0F)` may not work, but
/// // `value` is still regarded as a compile-time constant arithmetic.
/// struct MyFloatingPointConstant1 {
///   static const inline float value = 0;
/// };
///
/// // Non-const static variable.
/// struct MyFakeFloatingPointConstant {
///   static inline float value = 0;
/// };
///
/// static_assert(ConstantIntegral<std::true_type>);
/// static_assert(ConstantIntegral<const std::false_type>);
/// static_assert(ConstantIntegral<std::integral_constant<int, 0>>);
/// static_assert(ConstantIntegral<C<2>>);
/// static_assert(ConstantIntegral<cute::C<2>>);
/// static_assert(!ConstantIntegral<cute::Int<2>&>);
/// static_assert(!ConstantIntegral<cute::_3&&>);
///
/// static_assert(ConstantIntegral<MyIntegralConstant0>);
/// static_assert(ConstantIntegral<MyIntegralConstant1>);
/// static_assert(!ConstantIntegral<MyFakeIntegralConstant>);
///
/// static_assert(!ConstantIntegral<MyFloatingPointConstant0>);
/// static_assert(!ConstantIntegral<MyFloatingPointConstant1>);
/// static_assert(!ConstantIntegral<MyFakeFloatingPointConstant>);
/// ```
template <typename T>
concept ConstantIntegral = is_constant_integral_v<T>;

} // namespace ARIA
