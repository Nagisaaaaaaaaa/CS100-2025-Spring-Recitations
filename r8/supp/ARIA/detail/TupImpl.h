#pragma once

// #include "ARIA/TypeArray.h"
#include "../TypeArray.h"

// #include <cute/int_tuple.hpp>
#include "../../cute/int_tuple.hpp"

#include <array>

// Define CTAD for CuTe types.
namespace cute {

template <typename... Ts>
tuple(Ts...) -> tuple<Ts...>;

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
namespace ARIA {

namespace tup::detail {

// Get the underlying arithmetic domain.
// Examples:
//   int         -> int
//   const int   -> int
//   const int&  -> int
//   C<1>        -> int
//   const C<1>  -> int
//   const C<1>& -> int
//   std::string -> void
template <typename T>
struct arithmetic_domain {
  using type = void;
};

template <typename T>
  requires(!ConstantArithmetic<std::decay_t<T>> && std::is_arithmetic_v<std::decay_t<T>>)
struct arithmetic_domain<T> {
  using type = std::decay_t<T>;
};

template <typename T>
  requires(ConstantArithmetic<std::decay_t<T>>)
struct arithmetic_domain<T> {
  using type = std::decay_t<decltype(std::decay_t<T>::value)>;
};

template <typename T>
using arithmetic_domain_t = typename arithmetic_domain<T>::type;

template <typename T>
constexpr bool has_arithmetic_domain_v = !std::is_void_v<arithmetic_domain_t<T>>;

//
//
//
template <typename... Ts>
using Tup = cute::tuple<Ts...>;

template <typename... Ts>
  requires(has_arithmetic_domain_v<Ts> && ...)
using Tec = cute::tuple<Ts...>;

//
//
//
template <auto n, typename F, typename... Ts>
[[nodiscard]] ARIA_HOST_DEVICE constexpr auto make_tec_impl(F &&f, Ts &&...ts) {
  using TIdx = decltype(n);
  constexpr TIdx i0(0);
  constexpr TIdx i1(1);

  if constexpr (n == i0) {
    return Tec{std::forward<Ts>(ts)...};
  } else {
    if constexpr (std::is_invocable_v<F, C<n - i1>>)
      return make_tec_impl<n - i1>(std::forward<F>(f), f(C<n - i1>{}), std::forward<Ts>(ts)...);
    else
      return make_tec_impl<n - i1>(std::forward<F>(f), f.template operator()<n - i1>(), std::forward<Ts>(ts)...);
  }
}

template <auto n, typename F>
[[nodiscard]] ARIA_HOST_DEVICE constexpr auto make_tec(F &&f) {
  return make_tec_impl<n>(std::forward<F>(f));
}

//
//
//
//
//
// TODO: Great efforts are made to bypass the MSVC bug.
template <typename... Ts>
  requires((sizeof...(Ts) == 1 && has_arithmetic_domain_v<Ts>) && ...)
using Tec1 = cute::tuple<Ts...>;

template <typename... Ts>
  requires((sizeof...(Ts) == 2 && has_arithmetic_domain_v<Ts>) && ...)
using Tec2 = cute::tuple<Ts...>;

template <typename... Ts>
  requires((sizeof...(Ts) == 3 && has_arithmetic_domain_v<Ts>) && ...)
using Tec3 = cute::tuple<Ts...>;

template <typename... Ts>
  requires((sizeof...(Ts) == 4 && has_arithmetic_domain_v<Ts>) && ...)
using Tec4 = cute::tuple<Ts...>;

//
//
//
template <typename... Ts>
  requires(std::is_same_v<arithmetic_domain_t<Ts>, int> && ...)
using Teci = cute::tuple<Ts...>;

template <typename... Ts>
  requires(std::is_same_v<arithmetic_domain_t<Ts>, uint> && ...)
using Tecu = cute::tuple<Ts...>;

template <typename... Ts>
  requires(std::is_same_v<arithmetic_domain_t<Ts>, float> && ...)
using Tecf = cute::tuple<Ts...>;

template <typename... Ts>
  requires(std::is_same_v<arithmetic_domain_t<Ts>, double> && ...)
using Tecd = cute::tuple<Ts...>;

template <typename... Ts>
  requires(std::is_same_v<arithmetic_domain_t<Ts>, Real> && ...)
using Tecr = cute::tuple<Ts...>;

//
//
//
template <typename... Ts>
  requires((sizeof...(Ts) == 1 && std::is_same_v<arithmetic_domain_t<Ts>, int>) && ...)
using Tec1i = cute::tuple<Ts...>;

template <typename... Ts>
  requires((sizeof...(Ts) == 1 && std::is_same_v<arithmetic_domain_t<Ts>, uint>) && ...)
using Tec1u = cute::tuple<Ts...>;

template <typename... Ts>
  requires((sizeof...(Ts) == 1 && std::is_same_v<arithmetic_domain_t<Ts>, float>) && ...)
using Tec1f = cute::tuple<Ts...>;

template <typename... Ts>
  requires((sizeof...(Ts) == 1 && std::is_same_v<arithmetic_domain_t<Ts>, double>) && ...)
using Tec1d = cute::tuple<Ts...>;

template <typename... Ts>
  requires((sizeof...(Ts) == 1 && std::is_same_v<arithmetic_domain_t<Ts>, Real>) && ...)
using Tec1r = cute::tuple<Ts...>;

//
//
//
template <typename... Ts>
  requires((sizeof...(Ts) == 2 && std::is_same_v<arithmetic_domain_t<Ts>, int>) && ...)
using Tec2i = cute::tuple<Ts...>;

template <typename... Ts>
  requires((sizeof...(Ts) == 2 && std::is_same_v<arithmetic_domain_t<Ts>, uint>) && ...)
using Tec2u = cute::tuple<Ts...>;

template <typename... Ts>
  requires((sizeof...(Ts) == 2 && std::is_same_v<arithmetic_domain_t<Ts>, float>) && ...)
using Tec2f = cute::tuple<Ts...>;

template <typename... Ts>
  requires((sizeof...(Ts) == 2 && std::is_same_v<arithmetic_domain_t<Ts>, double>) && ...)
using Tec2d = cute::tuple<Ts...>;

template <typename... Ts>
  requires((sizeof...(Ts) == 2 && std::is_same_v<arithmetic_domain_t<Ts>, Real>) && ...)
using Tec2r = cute::tuple<Ts...>;

//
//
//
template <typename... Ts>
  requires((sizeof...(Ts) == 3 && std::is_same_v<arithmetic_domain_t<Ts>, int>) && ...)
using Tec3i = cute::tuple<Ts...>;

template <typename... Ts>
  requires((sizeof...(Ts) == 3 && std::is_same_v<arithmetic_domain_t<Ts>, uint>) && ...)
using Tec3u = cute::tuple<Ts...>;

template <typename... Ts>
  requires((sizeof...(Ts) == 3 && std::is_same_v<arithmetic_domain_t<Ts>, float>) && ...)
using Tec3f = cute::tuple<Ts...>;

template <typename... Ts>
  requires((sizeof...(Ts) == 3 && std::is_same_v<arithmetic_domain_t<Ts>, double>) && ...)
using Tec3d = cute::tuple<Ts...>;

template <typename... Ts>
  requires((sizeof...(Ts) == 3 && std::is_same_v<arithmetic_domain_t<Ts>, Real>) && ...)
using Tec3r = cute::tuple<Ts...>;

//
//
//
template <typename... Ts>
  requires((sizeof...(Ts) == 4 && std::is_same_v<arithmetic_domain_t<Ts>, int>) && ...)
using Tec4i = cute::tuple<Ts...>;

template <typename... Ts>
  requires((sizeof...(Ts) == 4 && std::is_same_v<arithmetic_domain_t<Ts>, uint>) && ...)
using Tec4u = cute::tuple<Ts...>;

template <typename... Ts>
  requires((sizeof...(Ts) == 4 && std::is_same_v<arithmetic_domain_t<Ts>, float>) && ...)
using Tec4f = cute::tuple<Ts...>;

template <typename... Ts>
  requires((sizeof...(Ts) == 4 && std::is_same_v<arithmetic_domain_t<Ts>, double>) && ...)
using Tec4d = cute::tuple<Ts...>;

template <typename... Ts>
  requires((sizeof...(Ts) == 4 && std::is_same_v<arithmetic_domain_t<Ts>, Real>) && ...)
using Tec4r = cute::tuple<Ts...>;

//
//
//
// Whether the given type is `Tec<...>`.
template <typename T>
struct is_tec : std::false_type {};

template <typename... Ts>
struct is_tec<Tec<Ts...>> : std::true_type {};

template <typename T>
constexpr bool is_tec_v = is_tec<T>::value;

//
//
//
// Whether the given `Tec` has rank `r`.
template <typename TTec, auto r>
struct is_tec_r : std::false_type {};

template <typename... Ts, auto r>
  requires(sizeof...(Ts) == r)
struct is_tec_r<Tec<Ts...>, r> : std::true_type {};

template <typename TTec, auto r>
constexpr bool is_tec_r_v = is_tec_r<TTec, r>::value;

//
//
//
// Whether the given `Tec` has "arithmetic" type `T`.
template <typename TTec, typename T>
struct is_tec_t : std::false_type {};

template <typename... Ts, typename T>
  requires(std::is_same_v<arithmetic_domain_t<Ts>, T> && ...)
struct is_tec_t<Tec<Ts...>, T> : std::true_type {};

template <typename TTec, typename T>
constexpr bool is_tec_t_v = is_tec_t<TTec, T>::value;

//
//
//
// Whether the given `Tec` has "arithmetic" type `T` and rank `r`.
template <typename TTec, typename T, auto r>
struct is_tec_tr : std::false_type {};

template <typename... Ts, typename T, auto r>
  requires(sizeof...(Ts) == r && (std::is_same_v<arithmetic_domain_t<Ts>, T> && ...))
struct is_tec_tr<Tec<Ts...>, T, r> : std::true_type {};

template <typename TTec, typename T, auto r>
constexpr bool is_tec_tr_v = is_tec_tr<TTec, T, r>::value;

//
//
//
//
//
template <typename T>
constexpr auto tup_size_v = cute::tuple_size_v<T>;

template <auto I, typename T>
using tup_elem_t = cute::tuple_element_t<I, T>;

//
//
//
using cute::rank;
using cute::rank_t;
using cute::rank_v;

using cute::get;

//
//
//
using cute::is_static;
using cute::is_static_v;

//
//
//
//
//
// Cast `Tup` to `TypeArray`.
template <typename... Ts>
consteval auto ToTypeArray(const Tup<Ts...> &) {
  return MakeTypeArray<Ts...>{};
}

template <typename TTup>
using to_type_array_t = decltype(detail::ToTypeArray(std::declval<TTup>()));

// Cast `TypeArray` to `Tup`.
template <typename... Ts>
consteval auto ToTup(const TypeArray<Ts...> &) {
  return Tup<Ts...>{};
}

template <typename TArray>
using to_tup_t = decltype(detail::ToTup(std::declval<TArray>()));

//
//
//
// Cast `Tec` to `std::array`.
template <typename T, typename... Ts>
[[nodiscard]] ARIA_HOST_DEVICE static constexpr auto ToArray(const Tec<T, Ts...> &tec) {
  using value_type = arithmetic_domain_t<T>;
  static_assert(is_tec_t_v<Tec<T, Ts...>, value_type>, "Element types of `Tec` should be \"as similar as possible\"");

  constexpr uint rank = rank_v<Tec<T, Ts...>>;

  std::array<value_type, rank> res;
  ForEach<rank>([&]<auto i>() { res[i] = get<i>(tec); });
  return res;
}

//
//
//
//
//
// Commonly-used constants.
template <uint n, auto v, auto... vs>
consteval auto ConstantImpl() {
  if constexpr (n == 0)
    return Tec<C<vs>...>{};
  else
    return ConstantImpl<n - 1, v, v, vs...>();
}

template <typename T, uint n, auto... vs>
consteval auto IndexSequenceImpl() {
  if constexpr (n == 0)
    return Tec<C<T(vs)>...>{};
  else
    return IndexSequenceImpl<T, n - 1, n - 1, vs...>();
}

template <typename T, uint n, uint i, auto... vs>
consteval auto UnitImpl() {
  if constexpr (n == 0)
    return Tec<C<T(vs)>...>{};
  else
    return UnitImpl<T, n - 1, i, (n == i + 1 ? 1 : 0), vs...>();
}

template <uint n, auto v>
using TecConstant = decltype(ConstantImpl<n, v>());

template <typename T, uint n>
using TecZero = decltype(ConstantImpl<n, T(0)>());

template <typename T, uint n>
using TecOne = decltype(ConstantImpl<n, T(1)>());

template <typename T, uint n>
using TecIndexSequence = decltype(IndexSequenceImpl<T, n>());

template <typename T, uint n, uint i>
  requires(i < n)
using TecUnit = decltype(UnitImpl<T, n, i>());

//
//
//
//
//
// Math-related features.
template <typename... Ts0, typename... Ts1>
[[nodiscard]] ARIA_HOST_DEVICE constexpr auto Dot(const Tec<Ts0...> &a, const Tec<Ts1...> &b) {
  static_assert(sizeof...(Ts0) > 0, "Empty `Tec`s are not allowed");

  //! `Ts0` is automatically required to have the same number of elements as `Ts1` at next line.
  using TRes = decltype(((std::declval<Ts0>() * std::declval<Ts1>()) + ...));
  if constexpr (is_static_v<TRes>) {
    return TRes{};
  } else {
    TRes res{};
    ForEach<sizeof...(Ts0)>([&]<auto i>() { res += get<i>(a) * get<i>(b); });
    return res;
  }
}

template <typename... Ts>
[[nodiscard]] ARIA_HOST_DEVICE constexpr auto NormSquared(const Tec<Ts...> &a) {
  return Dot(a, a);
}

template <typename... Ts0, typename... Ts1>
[[nodiscard]] ARIA_HOST_DEVICE constexpr auto Cross(const Tec<Ts0...> &a, const Tec<Ts1...> &b) {
  static_assert(sizeof...(Ts0) == 3 && sizeof...(Ts1) == 3,
                "Cross product is only implemented for `Tec`s with ranks equal to 3");

  return Tec{get<1>(a) * get<2>(b) - get<2>(a) * get<1>(b), //
             get<2>(a) * get<0>(b) - get<0>(a) * get<2>(b), //
             get<0>(a) * get<1>(b) - get<1>(a) * get<0>(b)};
}

} // namespace tup::detail

} // namespace ARIA

//
//
//
//
//
//
//
//
//
// Arithmetic operators for coords.
//! WARNING: These operators should only be defined in `namespace cute` in order for
//! ADL to find the correct operators.

namespace cute {

namespace aria::tup::detail {

// Fill a `Tec` with a same value.
template <typename... Ts>
[[nodiscard]] ARIA_HOST_DEVICE constexpr ARIA::tup::detail::Tec<Ts...>
FillTec(const std::decay_t<decltype(get<0>(std::declval<ARIA::tup::detail::Tec<Ts...>>()))> &v) {
  ARIA::tup::detail::Tec<Ts...> c;
  ARIA::ForEach<sizeof...(Ts)>([&]<auto i>() {
    static_assert(std::is_same_v<std::decay_t<decltype(cute::get<i>(c))>, std::decay_t<decltype(v)>>,
                  "Element types of the `Tec` should be the same");
    cute::get<i>(c) = v;
  });

  return c;
}

} // namespace aria::tup::detail

//
//
//
//! CuTe's original implementation of operators for constant zeros (in `integral_constant.hpp`)
//! has limitations such as floating point compatibilities.
//! So, those operators are rewritten by ARIA.
template <auto t, typename U>
  requires(t == 0 && std::is_arithmetic_v<U>)
[[nodiscard]] ARIA_HOST_DEVICE constexpr auto operator*(C<t>, U) {
  static_assert(t * U(1) == 0, "Invalid types for arithmetic operators");
  return C<t * U(1)>{};
}

template <typename U, auto t>
  requires(t == 0 && std::is_arithmetic_v<U>)
[[nodiscard]] ARIA_HOST_DEVICE constexpr auto operator*(U, C<t>) {
  static_assert(U(1) * t == 0, "Invalid types for arithmetic operators");
  return C<U(1) * t>{};
}

template <auto t, typename U>
  requires(t == 0 && std::is_arithmetic_v<U>)
[[nodiscard]] ARIA_HOST_DEVICE constexpr auto operator/(C<t>, U) {
  static_assert(t / U(1) == 0, "Invalid types for arithmetic operators");
  return C<t / U(1)>{};
}

//
//
//
template <typename... Ts0, typename... Ts1>
[[nodiscard]] ARIA_HOST_DEVICE constexpr auto operator+(const ARIA::tup::detail::Tec<Ts0...> &lhs,
                                                        const ARIA::tup::detail::Tec<Ts1...> &rhs) {
  //! `Ts0` is automatically required to have the same number of elements as `Ts1` at next line.
  ARIA::tup::detail::Tec<decltype(std::declval<Ts0>() + std::declval<Ts1>())...> res;
  ARIA::ForEach<sizeof...(Ts0)>([&]<auto i>() { cute::get<i>(res) = cute::get<i>(lhs) + cute::get<i>(rhs); });
  return res;
}

template <typename... Ts0, typename... Ts1>
[[nodiscard]] ARIA_HOST_DEVICE constexpr auto operator-(const ARIA::tup::detail::Tec<Ts0...> &lhs,
                                                        const ARIA::tup::detail::Tec<Ts1...> &rhs) {
  ARIA::tup::detail::Tec<decltype(std::declval<Ts0>() - std::declval<Ts1>())...> res;
  ARIA::ForEach<sizeof...(Ts0)>([&]<auto i>() { cute::get<i>(res) = cute::get<i>(lhs) - cute::get<i>(rhs); });
  return res;
}

template <typename... Ts0, typename... Ts1>
[[nodiscard]] ARIA_HOST_DEVICE constexpr auto operator*(const ARIA::tup::detail::Tec<Ts0...> &lhs,
                                                        const ARIA::tup::detail::Tec<Ts1...> &rhs) {
  ARIA::tup::detail::Tec<decltype(std::declval<Ts0>() * std::declval<Ts1>())...> res;
  ARIA::ForEach<sizeof...(Ts0)>([&]<auto i>() { cute::get<i>(res) = cute::get<i>(lhs) * cute::get<i>(rhs); });
  return res;
}

template <typename... Ts0, typename... Ts1>
[[nodiscard]] ARIA_HOST_DEVICE constexpr auto operator/(const ARIA::tup::detail::Tec<Ts0...> &lhs,
                                                        const ARIA::tup::detail::Tec<Ts1...> &rhs) {
  ARIA::tup::detail::Tec<decltype(std::declval<Ts0>() / std::declval<Ts1>())...> res;
  ARIA::ForEach<sizeof...(Ts0)>([&]<auto i>() { cute::get<i>(res) = cute::get<i>(lhs) / cute::get<i>(rhs); });
  return res;
}

template <typename... Ts0, typename Ts1>
[[nodiscard]] ARIA_HOST_DEVICE constexpr auto operator+(const ARIA::tup::detail::Tec<Ts0...> &lhs, const Ts1 &rhs) {
  //! `std::conditional_t<...>` at the following line is used to generate such a pack `<Ts1, Ts1, ...>`.
  return lhs + aria::tup::detail::FillTec<std::conditional_t<true, Ts1, Ts0>...>(rhs);
}

template <typename... Ts0, typename Ts1>
[[nodiscard]] ARIA_HOST_DEVICE constexpr auto operator+(const Ts1 &lhs, const ARIA::tup::detail::Tec<Ts0...> &rhs) {
  return aria::tup::detail::FillTec<std::conditional_t<true, Ts1, Ts0>...>(lhs) + rhs;
}

template <typename... Ts0, typename Ts1>
[[nodiscard]] ARIA_HOST_DEVICE constexpr auto operator-(const ARIA::tup::detail::Tec<Ts0...> &lhs, const Ts1 &rhs) {
  return lhs - aria::tup::detail::FillTec<std::conditional_t<true, Ts1, Ts0>...>(rhs);
}

template <typename... Ts0, typename Ts1>
[[nodiscard]] ARIA_HOST_DEVICE constexpr auto operator-(const Ts1 &lhs, const ARIA::tup::detail::Tec<Ts0...> &rhs) {
  return aria::tup::detail::FillTec<std::conditional_t<true, Ts1, Ts0>...>(lhs) - rhs;
}

template <typename... Ts0, typename Ts1>
[[nodiscard]] ARIA_HOST_DEVICE constexpr auto operator*(const ARIA::tup::detail::Tec<Ts0...> &lhs, const Ts1 &rhs) {
  return lhs * aria::tup::detail::FillTec<std::conditional_t<true, Ts1, Ts0>...>(rhs);
}

template <typename... Ts0, typename Ts1>
[[nodiscard]] ARIA_HOST_DEVICE constexpr auto operator*(const Ts1 &lhs, const ARIA::tup::detail::Tec<Ts0...> &rhs) {
  return aria::tup::detail::FillTec<std::conditional_t<true, Ts1, Ts0>...>(lhs) * rhs;
}

template <typename... Ts0, typename Ts1>
[[nodiscard]] ARIA_HOST_DEVICE constexpr auto operator/(const ARIA::tup::detail::Tec<Ts0...> &lhs, const Ts1 &rhs) {
  return lhs / aria::tup::detail::FillTec<std::conditional_t<true, Ts1, Ts0>...>(rhs);
}

template <typename... Ts0, typename Ts1>
[[nodiscard]] ARIA_HOST_DEVICE constexpr auto operator/(const Ts1 &lhs, const ARIA::tup::detail::Tec<Ts0...> &rhs) {
  return aria::tup::detail::FillTec<std::conditional_t<true, Ts1, Ts0>...>(lhs) / rhs;
}

} // namespace cute
