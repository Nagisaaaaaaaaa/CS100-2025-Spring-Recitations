#pragma once

/// \file
/// \brief You may have known that `std::vector<bool>` is a special case in C++ STL.
/// See https://en.cppreference.com/w/cpp/container/vector_bool.
/// This special cases make code based on `std::vector` much more error prone,
/// one of the most tricky bugs is about `auto`, see the following examples.
///
/// We refer to these `std::vector<bool>`-like designs as "proxy systems".
/// In ARIA, there are a lot of proxy systems working together, including:
///   1. std::vector<bool>,
///   2. thrust::device_vector,
///   3. Eigen,
///   ...,
/// and the most intensively used one: the ARIA builtin property system, see Property.h.
///
/// To help `auto` work better with proxy systems,
/// this file introduces the `auto + Auto` type deduction.

//
//
//
//
//
#include "ARIA/detail/PropertyType.h"

namespace ARIA {

/// \brief A function return type wrapper to help `auto` better deduce return types from proxy systems.
///
/// \warning Using `auto` for type deduction is unsafe when there exists proxies, for example:
/// ```cpp
/// std::vector<bool> v(1);
/// auto x = v[0];
/// std::cout << x << std::endl; // 0
///
/// v[0] = true;
/// std::cout << x << std::endl; // ?
/// ```
/// It will print `0` at the first time, easy.
/// But, how about the second time?
/// It will be `1`, not `0`!
/// That is because `auto` was not deduced to `bool`, instead,
/// it was deduced to a magic reference to `bool`, the same case for the ARIA property system.
/// To make life easier, ALWAYS use `auto + Auto()` type deduction.
///
/// You may have imagined that function overloading with C++20 concepts are able to correctly implement `Auto`,
/// but the truth is that it is error prone,
/// because we must provide the "most generic" `Auto`, which accepts any types:
/// ```cpp
/// template <typename T>
/// ARIA_HOST_DEVICE auto Auto(const T& v) {
///   return v;
/// }
/// ```
/// This "most generic" `Auto` makes template type deduction weird, especially when C++20 concepts exist.
/// That is why `Auto` is implemented with `if constexpr` instead.
/// And that is why there's EXACTLY ONE `Auto` in namespace ARIA.
///
/// So, if you want to implement another `Auto` for your own system which depends on ARIA,
/// for example if you want to add another proxy system, follow the rules below:
/// 1. Implement the new `Auto` in your namespace, never in namespace ARIA.
/// 2. From then on, always use `YourNamespace::Auto` instead of `ARIA::Auto`,
///    never write something like `use namespace ARIA;`.
/// 3. Make sure that the proxy system you want to add is not in namespace ARIA,
///    or ADL will make things much more weird.
///
/// If you are also using the ARIA property system, see `Property.h`,
/// it is recommended to implement your own property system in order to
/// properly handle the newly added proxy system.
/// See `Property.h` for how to implement it.
///
/// \example ```cpp
/// std::vector<bool> v(1);
/// auto x = Auto(v[0]); // `x` is `bool`.
///
/// Vec3f v;
/// auto x = Auto(v.x()); // `x` is `float`.
/// ```
///
/// \see std::vector<bool>
/// \see thrust::device_vector
/// \see Eigen
/// \see Property.h
/// \see PropertyImpl.h
template <property::detail::ProxyType T>
ARIA_HOST_DEVICE constexpr auto Auto(T &&v) {
  if constexpr //! For ARIA property, note that this should be checked before any other proxy systems.
      (property::detail::PropertyType<std::decay_t<T>>)
    return std::forward<T>(v).value();
  else if constexpr (std::is_same_v<std::decay_t<T>,
                                    std::decay_t<decltype(std::vector<bool>()[0])>>) //! For `std::vector<bool>`.
    return static_cast<bool>(std::forward<T>(v));
  else if constexpr (!std::is_same_v<std::decay_t<T>,
                                     std::decay_t<decltype(thrust::raw_reference_cast(v))>>) //! For `thrust`.
    return static_cast<typename std::decay_t<T>::value_type>(std::forward<T>(v));
  else if constexpr //! For `Eigen`.
      (requires {
         { std::forward<T>(v).eval() };
       })
    return std::forward<T>(v).eval();
  else //! Non-proxy types.
    ARIA_STATIC_ASSERT_FALSE("Bugs detected in the ARIA property system, please contact the developers to fix them");
}

template <property::detail::NonProxyType T>
ARIA_HOST_DEVICE constexpr decltype(auto) Auto(T &&v) {
  if constexpr (std::is_lvalue_reference_v<decltype(v)>) //! For l-value, simply return the reference.
    return std::forward<T>(v);
  else {                            //! For r-value and others, never return a reference.
    auto temp = std::forward<T>(v); // Deduced by `auto` instead of `decltype(auto)` to remove the reference.
    return temp;
  }
}

} // namespace ARIA
