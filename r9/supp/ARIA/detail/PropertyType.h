#pragma once

#include "ARIA/ARIA.h"

#include <thrust/detail/raw_reference_cast.h>

#include <concepts>
#include <vector>

namespace ARIA {

namespace property::detail {

/// \brief The base class of any property.
/// The base class is introduced in order to
/// automatically define operators for properties with CRTP and type checks.
///
/// See PropertyImpl.h for its implementation.
template <typename TProperty>
class PropertyBase;

/// \brief Whether the type `T` is a property.
template <typename T>
concept PropertyType = std::derived_from<T, property::detail::PropertyBase<T>>;

/// \brief Whether the type `T` is not a property.
template <typename T>
concept NonPropertyType = !PropertyType<T>;

//
//
//
/// \brief Whether the decayed given type `T` is a proxy type of any proxy system.
///
/// \warning EVERY settable proxy type of EVERY proxy system should be taken into account,
/// or it will be dangerous when multiple proxy systems are used together.
template <typename T>
static constexpr bool is_proxy_type_v =
    PropertyType<std::decay_t<T>>                                                                               ? true
    : (std::is_same_v<std::decay_t<T>, std::decay_t<decltype(std::vector<bool>()[0])>>)                         ? true
    : (!std::is_same_v<std::decay_t<T>, std::decay_t<decltype(thrust::raw_reference_cast(std::declval<T>()))>>) ? true
    : (requires(T &&v) {
        { v.eval() };
        requires !std::is_same_v<std::decay_t<T>, std::decay_t<decltype(v.eval())>>;
      })                                                                                                        ? true
                                                                                                                : false;

template <typename T>
concept ProxyType = is_proxy_type_v<T>;

template <typename T>
concept NonProxyType = !ProxyType<T>;

/// \brief Whether the decayed given type `T` is a settable proxy type of any proxy system.
/// For example, return type of `std::vector<bool>()[i]` is a settable proxy,
/// return type of `thrust::device_vector<...>()[i]` is a settable proxy,
/// all ARIA properties are settable proxies, but
/// all `Eigen` proxies are non-settable proxies.
///
/// We have to define this concept to classify settable proxies from others,
/// in order to forbid non-settable proxies in `ARIA_PROP_FUNC`.
/// For example, `Eigen` function return types.
///
/// \warning EVERY settable proxy type of EVERY proxy system should be taken into account,
/// or it will be dangerous when multiple proxy systems are used together.
template <typename T>
static constexpr bool is_settable_proxy_type_v =
    PropertyType<std::decay_t<T>>                                                                               ? true
    : (std::is_same_v<std::decay_t<T>, std::decay_t<decltype(std::vector<bool>()[0])>>)                         ? true
    : (!std::is_same_v<std::decay_t<T>, std::decay_t<decltype(thrust::raw_reference_cast(std::declval<T>()))>>) ? true
    : (requires(T &&v) {
        { v.eval() };
        requires !std::is_same_v<std::decay_t<T>, std::decay_t<decltype(v.eval())>>;
      })                                                                                                        ? false
                                                                                                                : false;

template <typename T>
concept SettableProxyType = is_settable_proxy_type_v<T>;

template <typename T>
concept NonSettableProxyType = !SettableProxyType<T>;

} // namespace property::detail

} // namespace ARIA
