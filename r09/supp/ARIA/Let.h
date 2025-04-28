#pragma once

/// \file
/// \warning Make sure you are familiar with `Auto.h` before continue.
///
/// \brief Suppose you are writing a very small project based on ARIA,
/// it is very annoying to use `auto + Auto` type deduction everywhere.
/// Instead, we want to use `Auto` only when we have to, which
/// means that the compiler should be able to tell us:
///   1. Which `auto` is unsafe and refuse to compile them,
///   2. Which `Auto` is unnecessary and refuse to compile them.
///
/// It should be warned that such a design is bad for large projects, because
/// we usually need template functions which can
/// handle both proxy types and non-proxy types.
/// That is where `auto + Auto` type deduction is necessary.
///
/// So, if you are writing a very small project, feel free to
/// include this file and use `let + Let` instead of `auto + Auto`.

//
//
//
//
//
// #include "ARIA/Auto.h"
#include "./Auto.h"

namespace ARIA {

/// \brief A wrapped `auto`, refuse to compile when deducted to proxy types.
///
/// \example ```cpp
/// let x = 10;
/// let x = Let(10); // Compile error.
///
/// std::vector<bool> v(1);
/// let x = v[0]; // Compile error.
/// let x = Let(v[0]);
/// ```
///
/// \see Auto.h
#define let ::ARIA::property::detail::NonProxyType auto

//
//
//
/// \brief A wrapped `Auto`, refuse to compile when given non-proxy types.
///
/// \example ```cpp
/// let x = 10;
/// let x = Let(10); // Compile error.
///
/// std::vector<bool> v(1);
/// let x = v[0]; // Compile error.
/// let x = Let(v[0]);
/// ```
///
/// \see Auto.h
template <property::detail::ProxyType T>
ARIA_HOST_DEVICE constexpr decltype(auto) Let(T &&v) {
  return Auto(std::forward<T>(v)); // `decltype(auto)` is used to let `Auto` deduce the return type.
}

} // namespace ARIA
