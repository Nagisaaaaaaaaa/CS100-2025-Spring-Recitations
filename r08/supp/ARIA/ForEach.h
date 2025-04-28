#pragma once

/// \file
/// \brief `ForEach` can be used to loop through both runtime integrals and compile-time constant integrals.
///
/// For example:
/// ```cpp
/// int n = 3;
///
/// ForEach(n, ...);    // Runtime integral.
/// ForEach(3_I, ...);  // Compile-time constant integral.
/// ForEach<3>(...);    // Compile-time constant integral.
/// ForEach<C<3>>(...); // Compile-time constant integral.
/// ```
///
/// For compile-time constant integrals,
/// loops are unrolled at compile-time and parameters `i` are `constexpr`.
///
/// In ARIA, there are overloads of `ForEach` to loop through other items, see `TypeArray.h`.

//
//
//
//
//
// #include "ARIA/detail/ForEachImpl.h"
#include "./detail/ForEachImpl.h"

namespace ARIA {

/// \brief For each runtime integral `i` from 0 to `n`, calls `f(i)`.
///
/// \example ```cpp
/// int n = 3;
///
/// ForEach(n, [&](auto i) {
///   ForEach(n, [&](auto j) {
///     ForEach(n, [&](auto k) {
///       static_assert(std::is_same_v<decltype(i), int>);
///       static_assert(std::is_same_v<decltype(j), int>);
///       static_assert(std::is_same_v<decltype(k), int>);
///
///       const auto x = i;
///       const auto y = j;
///       const auto z = k;
///
///       ...
///     });
///   });
/// });
/// ```
template <typename T, typename F>
  requires(!ConstantIntegral<T> && std::integral<T>)
ARIA_HOST_DEVICE constexpr void ForEach(const T &n, F &&f) {
  for (T i = {}; i < n; ++i)
    f(i);
}

//
//
//
/// \brief For each compile-time constant integral `i` from 0 to `N`, calls `f(i)` or `f<i>()`.
///
/// \example ```cpp
/// ForEach(3_I, [&](auto i) {
///   static_assert(ConstantIntegral<decltype(i)>);
///
///   constexpr auto x = i;
///
///   ...
/// });
///
/// ForEach(3_I, [&]<auto i> {
///   ForEach(3_I, [&]<auto j> {
///     ForEach(3_I, [&]<auto k> {
///       static_assert(std::is_same_v<decltype(i), int>);
///       static_assert(std::is_same_v<decltype(j), int>);
///       static_assert(std::is_same_v<decltype(k), int>);
///
///       constexpr auto x = i;
///       constexpr auto y = j;
///       constexpr auto z = k;
///
///       ...
///     });
///   });
/// });
/// ```
template <ConstantIntegral N, typename F>
ARIA_HOST_DEVICE constexpr void ForEach(const N &, F &&f) {
  using TInt = decltype(N::value);
  for_each::detail::ForEachImpl<TInt{0}, N::value, TInt{1}>(std::forward<F>(f));
}

//
//
//
/// \brief For each compile-time constant integral `i` from 0 to `N`, calls `f(i)` or `f<i>()`.
///
/// \example ```cpp
/// ForEach<3>([&](auto i) {
///   static_assert(ConstantIntegral<decltype(i)>);
///
///   constexpr auto x = i;
///
///   ...
/// });
///
/// ForEach<3>([&]<auto i> {
///   ForEach<3>([&]<auto j> {
///     ForEach<3>([&]<auto k> {
///       static_assert(std::is_same_v<decltype(i), int>);
///       static_assert(std::is_same_v<decltype(j), int>);
///       static_assert(std::is_same_v<decltype(k), int>);
///
///       constexpr auto x = i;
///       constexpr auto y = j;
///       constexpr auto z = k;
///
///       ...
///     });
///   });
/// });
/// ```
template <auto n, typename F>
  requires(!ConstantIntegral<decltype(n)> && std::integral<decltype(n)>)
ARIA_HOST_DEVICE constexpr void ForEach(F &&f) {
  ForEach(C<n>{}, std::forward<F>(f));
}

//
//
//
/// \brief For each compile-time constant integral `i` from 0 to `N`, calls `f(i)` or `f<i>()`.
///
/// \example ```cpp
/// ForEach<C<3>>([&](auto i) {
///   static_assert(ConstantIntegral<decltype(i)>);
///
///   constexpr auto x = i;
///
///   ...
/// });
///
/// ForEach<C<3>>([&]<auto i> {
///   ForEach<C<3>>([&]<auto j> {
///     ForEach<C<3>>([&]<auto k> {
///       static_assert(std::is_same_v<decltype(i), int>);
///       static_assert(std::is_same_v<decltype(j), int>);
///       static_assert(std::is_same_v<decltype(k), int>);
///
///       constexpr auto x = i;
///       constexpr auto y = j;
///       constexpr auto z = k;
///
///       ...
///     });
///   });
/// });
/// ```
template <ConstantIntegral N, typename F>
ARIA_HOST_DEVICE constexpr void ForEach(F &&f) {
  ForEach(N{}, std::forward<F>(f));
}

} // namespace ARIA
