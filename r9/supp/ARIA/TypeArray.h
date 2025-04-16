#pragma once

/// \file
/// \brief Type array is a compile-time 1D array containing any combinations of types
/// which themselves are not type arrays (we call them `NonArrayType`s).
///
/// That is, a type array can contain int, float&, void, etc.
/// But it cannot recursively contain another type array.
///
/// Type array may be helpful if you want to perform complex manipulations on many types,
/// for example, erase, remove, foreach, filter, etc.

//
//
//
//
//
// #include "ARIA/ForEach.h"
#include "./ForEach.h"
#include "detail/TypeArrayImpl.h"

namespace ARIA {

/// \brief A compile-time 1D type array containing any combinations of types
/// which themselves are not type arrays (we call them `NonArrayType`s).
///
/// That is, a type array can contain int, float&, void, etc.
/// But it cannot recursively contain another type array.
///
/// Type array may be helpful if you want to perform complex manipulations on many types,
/// for example, erase, remove, foreach, filter, etc.
///
/// \tparam Ts Combination of `NonArrayType`s.
///
/// \example ```cpp
/// using ts = MakeTypeArray<int, float&>; // TypeArray<int, float&>
/// using t0 = ts::Get<0>;                 // int
/// using t1 = ts::Get<1>;                 // float&
/// ```
///
/// \note `MakeTypeArray<int, float&>` is used instead of directly writing `TypeArray<int, float&>`,
/// because `MakeTypeArray` provides many stronger ways to construct a type array,
/// including merging many type arrays.
///
/// \see MakeTypeArray
template <type_array::detail::NonArrayType... Ts>
struct TypeArray final : type_array::detail::TypeArrayBase {
private:
  /// \brief Type array support Python-like negative indices.
  ///
  /// \see Get
  /// \see Slice
  /// \see Erase
  /// \see Insert
  using Idx = type_array::detail::Idx;

public:
  /// \brief Number of types contained in the type array.
  ///
  /// \example ```cpp
  /// using ts = MakeTypeArray<int, float&>; // TypeArray<int, float&>
  /// constexpr size_t size = ts::size;      // 2
  /// ```
  static constexpr size_t size = sizeof...(Ts);

  /// \brief Number of the given type `T` contained in the type array.
  ///
  /// \tparam T The given type `T` to be searched,
  /// required not to be a type array.
  ///
  /// \example ```cpp
  /// using ts = MakeTypeArray<int, int, float&>; // TypeArray<int, int, float&>
  /// constexpr size_t v0 = ts::nOf<int>;         // 2
  /// constexpr size_t v1 = ts::nOf<float&>;      // 1
  /// ```
  ///
  /// \see has
  template <type_array::detail::NonArrayType T>
  static constexpr size_t nOf = type_array::detail::NOf<T, TypeArray>::value;

  /// \brief Whether the given type `T` exists in the type array.
  ///
  /// \tparam T The given type `T` to be searched,
  /// required not to be a type array.
  ///
  /// \example ```cpp
  /// using ts = MakeTypeArray<int, float&>;  // TypeArray<int, float&>
  /// constexpr bool v0 = ts::has<int>;       // true
  /// constexpr bool v1 = ts::has<float&>;    // true
  /// constexpr bool v2 = ts::has<const int>; // false
  /// constexpr bool v3 = ts::has<int&>;      // false
  /// ```
  ///
  /// \see nOf
  template <type_array::detail::NonArrayType T>
  static constexpr bool has = type_array::detail::Has<T, TypeArray>::value;

  /// \brief Find index of the first time the given type `T` appears in the type array.
  ///
  /// \tparam T The given type `T` to be searched, required not to be a type array.
  ///
  /// \example ```cpp
  /// using ts = MakeTypeArray<int, int, float&>; // TypeArray<int, int, float&>
  /// constexpr size_t v0 = ts::firstIdx<int>;    // 0
  /// constexpr size_t v1 = ts::firstIdx<float&>; // 2
  /// ```
  ///
  /// \note Compile error if `T` is not exist in the type array.
  ///
  /// \see lastIdx
  template <type_array::detail::NonArrayType T>
  static constexpr size_t firstIdx = type_array::detail::FirstIdx<T, TypeArray>::value;

  /// \brief Find index of the last time the given type `T` appears in the type array.
  ///
  /// \tparam T The given type `T` to be searched, required not to be a type array.
  ///
  /// \example ```cpp
  /// using ts = MakeTypeArray<int, int, float&>; // TypeArray<int, int, float&>
  /// constexpr size_t v0 = ts::lastIdx<int>;     // 1
  /// constexpr size_t v1 = ts::lastIdx<float&>;  // 2
  /// ```
  ///
  /// \note Compile error if `T` is not exist in the type array.
  ///
  /// \see firstIdx
  template <type_array::detail::NonArrayType T>
  static constexpr size_t lastIdx = type_array::detail::LastIdx<T, TypeArray>::value;

  //
  //
  //
  /// \brief Get the type at the given Python-like index `i`.
  ///
  /// \tparam i Python-like signed index, can be 0, 1, 2, ... or -1, -2, ...
  ///
  /// \example ```cpp
  /// using ts = MakeTypeArray<int, float&>; // TypeArray<int, float&>
  /// using t0 = ts::Get<0>;                 // int
  /// using t1 = ts::Get<1>;                 // float&
  /// using t2 = ts::Get<-1>;                // float&
  /// using t3 = ts::Get<-2>;                // int
  /// ```
  ///
  /// \note Compile error if `i` not in range [-size, size - 1].
  ///
  /// \see Slice
  template <Idx i>
  using Get = typename type_array::detail::Get<i, TypeArray>::type;

  /// \brief Get the slice (sub array) given the slice parameters, `begin`, `end`, and `step`.
  ///
  /// \tparam begin Python-like signed index, can be 0, 1, 2, ... or -1, -2, ...
  /// \tparam end Python-like signed index, can be 0, 1, 2, ... or -1, -2, ...
  /// \tparam step Python-like signed index, can be 0, 1, 2, ... or -1, -2, ...
  ///
  /// \example ```cpp
  /// // TypeArray<int, float&, double&&>
  /// using ts = MakeTypeArray<int, float&, double&&>;
  /// using ts0 = ts::Slice<1, ts::size, 1>;      // TypeArray<float&, double&&>
  /// using ts1 = ts::Slice<ts::size - 1, 0, -1>; // TypeArray<double&&, float&>
  /// ```
  ///
  /// \note Compile error if `step == 0`.
  /// If `begin` and `end` are not in range [-size, size - 1], it is still able to compile,
  /// and exactly follows the Python slice rules.
  ///
  /// \see Get
  template <Idx begin, Idx end, Idx step>
  using Slice = typename type_array::detail::Slice<begin, end, step, TypeArray>::type;

  /// \brief Reverse the type array.
  ///
  /// \tparam Void A dummy parameter introduced to bypass the compiler feature (bug).
  ///
  /// \example ```cpp
  /// using ts = MakeTypeArray<int, float&>; // TypeArray<int, float&>
  /// using ts0 = ts::Reverse<>;             // TypeArray<float&, int>
  /// ```
  ///
  /// \note The dummy parameter `void` is introduced to bypass the compiler feature (bug),
  /// because `Reverse` has to be compiled after `TypeArray` to wait until the C++ type system ready.
  /// Otherwise, even `std::derived_from` and `std::is_same_v` will fail.
  template <typename Void = void>
  using Reverse = typename type_array::detail::Reverse<TypeArray, Void>::type;

  /// \brief Erase the type at the given Python-like index `i`.
  ///
  /// \tparam i Python-like signed index, can be 0, 1, 2, ... or -1, -2, ...
  ///
  /// \example ```cpp
  /// using ts = MakeTypeArray<int, float&>; // TypeArray<int, float&>
  /// using ts0 = ts::Erase<0>;              // TypeArray<float&>
  /// using ts1 = ts::Erase<-1>;             // TypeArray<int>
  /// using ts2 = ts::Erase<0>::Erase<0>;    // TypeArray<>
  /// ```
  ///
  /// \note Compile error if `i` not in range [-size, size - 1].
  ///
  /// \see Remove
  /// \see Replace
  template <Idx i>
  using Erase = typename type_array::detail::Erase<i, TypeArray>::type;

  /// \brief Insert the given `NonArrayType` or even type array `T` before the type at the given Python-like index `i`.
  ///
  /// \tparam i Python-like signed index, can be 0, 1, 2, ... or -1, -2, ...
  /// \tparam T The given type `T` to be inserted,
  /// can be a `NonArrayType` or a type array.
  ///
  /// \example ```cpp
  /// using ts = MakeTypeArray<float&>; // TypeArray<float&>
  /// using ts0 = ts::Insert<0, int>;   // TypeArray<int, float&>
  /// using ts1 = ts0::Insert<1, ts0>;  // TypeArray<int, int, float&, float&>
  /// ```
  ///
  /// \note Compile error if `i` not in range [-size, size - 1].
  ///
  /// \see PushFront
  /// \see PushBack
  template <Idx i, typename T>
  using Insert = typename type_array::detail::Insert<i, T, TypeArray>::type;

  /// \brief Pop the first type of the type array.
  ///
  /// \tparam Void A dummy parameter introduced to bypass the compiler feature (bug).
  ///
  /// \example ```cpp
  /// using ts = MakeTypeArray<int, float&>; // TypeArray<int, float&>
  /// using ts0 = ts::PopFront<>;            // TypeArray<float&>
  /// ```
  ///
  /// \note The dummy parameter `void` is introduced to bypass the compiler feature (bug),
  /// because `Reverse` has to be compiled after `TypeArray` to wait until the C++ type system ready.
  /// Otherwise, even `std::derived_from` and `std::is_same_v` will fail.
  ///
  /// \see PopBack
  template <typename Void = void>
  using PopFront = typename type_array::detail::PopFront<TypeArray, Void>::type;

  /// \brief Pop the last type of the type array.
  ///
  /// \tparam Void A dummy parameter introduced to bypass the compiler feature (bug).
  ///
  /// \example ```cpp
  /// using ts = MakeTypeArray<int, float&>; // TypeArray<int, float&>
  /// using ts0 = ts::PopBack<>;             // TypeArray<int>
  /// ```
  ///
  /// \note The dummy parameter `void` is introduced to bypass the compiler feature (bug),
  /// because `Reverse` has to be compiled after `TypeArray` to wait until the C++ type system ready.
  /// Otherwise, even `std::derived_from` and `std::is_same_v` will fail.
  ///
  /// \see PopFront
  template <typename Void = void>
  using PopBack = typename type_array::detail::PopBack<TypeArray, Void>::type;

  /// \brief Push the given `NonArrayType` or type array `T` to the front of the type array.
  ///
  /// \tparam T The given type `T` to be pushed, can be a `NonArrayType` or a type array.
  ///
  /// \example ```cpp
  /// using ts = MakeTypeArray<float&>; // TypeArray<float&>
  /// using ts0 = ts::PushFront<int>;   // TypeArray<int, float&>
  /// using ts1 = ts::PushFront<ts0>;   // TypeArray<int, float&, float&>
  /// ```
  ///
  /// \see PushBack
  /// \see Insert
  template <typename T>
  using PushFront = typename type_array::detail::PushFront<T, TypeArray>::type;

  /// \brief Push the given `NonArrayType` or type array `T` to the back of the type array.
  ///
  /// \tparam T The given type `T` to be pushed, can be a `NonArrayType` or a type array.
  ///
  /// \example ```cpp
  /// using ts = MakeTypeArray<int>;    // TypeArray<int>
  /// using ts0 = ts::PushBack<float&>; // TypeArray<int, float&>
  /// using ts1 = ts::PushBack<ts0>;    // TypeArray<int, int, float&>
  /// ```
  ///
  /// \see PushFront
  /// \see Insert
  template <typename T>
  using PushBack = typename type_array::detail::PushBack<T, TypeArray>::type;

  /// \brief Remove all the types in the type array which are the same as `T`.
  ///
  /// \tparam T The given type `T` to be removed, required not to be a type array.
  ///
  /// \example ```cpp
  /// using ts = MakeTypeArray<int, float&>; // TypeArray<int, float&>
  /// using ts0 = ts::Remove<int>;           // TypeArray<float&>
  /// using ts1 = ts::Remove<float&>;        // TypeArray<int>
  /// ```
  ///
  /// \see Replace
  /// \see Erase
  template <type_array::detail::NonArrayType T>
  using Remove = typename type_array::detail::Remove<T, TypeArray>::type;

  /// \brief Replace all the types in the type array which are the same as `TFrom`
  /// with the given `NonArrayType` or type array `TTo`.
  ///
  /// \tparam TFrom The given type `T` to be replaced, required not to be a type array.
  /// \tparam TTo The given type `T` to be filled, can be a `NonArrayType` or a type array.
  ///
  /// \example ```cpp
  /// using ts = MakeTypeArray<int, float&>;   // TypeArray<int, float&>
  /// using ts0 = ts::Replace<int, const int>; // TypeArray<const int, float&>
  /// using ts1 = ts::Replace<int, ts0>; // TypeArray<const int, float&, float&>
  /// ```
  ///
  /// \see Remove
  /// \see Erase
  template <type_array::detail::NonArrayType TFrom, typename TTo>
  using Replace = typename type_array::detail::Replace<TFrom, TTo, TypeArray>::type;

  //
  //
  //
  /// \brief Replace each type `T` in the type array with `F<T>`.
  ///
  /// \tparam F A template, where `F<T>` is a `NonArrayType`.
  ///
  /// \example ```cpp
  /// using ts = MakeTypeArray<int, float&>; // TypeArray<int, float&>
  /// using ts0 = ts::ForEach<std::remove_reference_t>; // TypeArray<int, float>
  /// ```
  ///
  /// \note Compile error if `F<T>` is an `ArrayType`.
  ///
  /// \see Filter
  template <template <type_array::detail::NonArrayType> typename F>
  using ForEach = typename type_array::detail::ForEach<F, TypeArray>::type;

  /// \brief Filter each type `T` in the type array with `F<T>::value` equals to false.
  ///
  /// \tparam F A template, whose `F<T>::value` can be statically casted to `bool`.
  ///
  /// \example ```cpp
  /// using ts = MakeTypeArray<int, float&>;     // TypeArray<int, float&>
  /// using ts0 = ts::Filter<std::is_reference>; // TypeArray<float&>
  /// ```
  ///
  /// \note Compile error if `F<T>::value` can not be statically casted to `bool`.
  ///
  /// \see ForEach
  ///
  /// \todo Failed to directly use something like std::is_reference_v because
  /// `F<T>` will be a value, not a type.
  template <template <type_array::detail::NonArrayType> typename F>
  using Filter = typename type_array::detail::Filter<F, TypeArray>::type;
};

//
//
//
//
//
/// \brief Build type array with any combinations of `NonArrayType`s and type arrays.
///
/// \tparam Types Combination of `NonArrayType`s and type arrays.
///
/// \example ```cpp
/// using ts0 = MakeTypeArray<int, float&>;   // TypeArray<int, float&>
/// using ts1 = MakeTypeArray<ts0, int&&>; // TypeArray<int, float&, int&&>
/// ```
///
/// \see TypeArray
template <typename... Types>
using MakeTypeArray = typename type_array::detail::MakeTypeArray<Types...>::type;

//
//
//
//
//
/// \brief For each type `T` in the type array, calls `f<T>()`.
///
/// \tparam TArray A type array.
/// \tparam F A callable type.
///
/// \param f A callable parameter.
///
/// \example ```cpp
/// using ts = MakeTypeArray<const int, volatile float&, void>;
/// ForEach<ts>([] <typename T> {
///   if constexpr (std::is_same_v<T, const int>)
///     std::cout << "const int" << std::endl;
///   else if constexpr (std::is_same_v<T, volatile float&>)
///     std::cout << "volatile float&" << std::endl;
///   else if constexpr (std::is_same_v<T, void>)
///     std::cout << "void" << std::endl;
///   else
///     std::cout << "unknown" << std::endl;
/// });
/// ```
///
/// \see Loop.h
template <type_array::detail::ArrayType TArray, typename F>
ARIA_HOST_DEVICE constexpr void ForEach(F &&f) {
  ForEach<TArray::size>([&]<auto i>() {
    using T = TArray::template Get<i>;
    f.template operator()<T>();
  });
}

} // namespace ARIA
