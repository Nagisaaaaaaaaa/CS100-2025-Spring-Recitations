#pragma once

// #include "ARIA/ARIA.h"
#include "../ARIA.h"

#include <concepts>
#include <type_traits>

namespace ARIA {

namespace type_array::detail {

/// \brief The base class of any type array.
///
/// \note The base class is introduced in order to support two concepts `ArrayType` and `NonArrayType`.
/// Users should not directly inherit from this class, or, there will be undefined behaviors.
struct TypeArrayBase {};

/// \brief Whether the type `T` is an `TypeArray`.
template <typename T>
concept ArrayType = std::derived_from<T, TypeArrayBase>;

/// \brief Whether the type `T` is not an `TypeArray`.
template <typename T>
concept NonArrayType = !ArrayType<T>;

/// \brief Type array support Python-like negative indices.
///
/// \see Get
/// \see Slice
/// \see Erase
/// \see Insert
using Idx = std::make_signed_t<size_t>;

}; // namespace type_array::detail

//
//
//
//
//
//
//
//
//
// fwd
template <type_array::detail::NonArrayType... Ts>
struct TypeArray;

//
//
//
//
//
//
//
//
//
namespace type_array::detail {

template <typename... Types>
struct MakeTypeArray;

// \brief Build empty type array.
// MakeTypeArray<> is the same as TypeArray<>.
template <>
struct MakeTypeArray<> {
  using type = TypeArray<>;
};

// \brief Build type array with 1 type.
// MakeTypeArray<int> is the same as TypeArray<int>.
template <NonArrayType T>
struct MakeTypeArray<T> {
  using type = TypeArray<T>;
};

// \brief Build type array with 1 type array.
// MakeTypeArray<TypeArray<int>> is the same as TypeArray<int>.
template <template <typename...> typename T, NonArrayType... Ts>
  requires(ArrayType<T<Ts...>>)
struct MakeTypeArray<T<Ts...>> {
  using type = TypeArray<Ts...>;
};

// \brief Build type array with 2 types.
// MakeTypeArray<int, float&> is the same as TypeArray<int, float&>.
template <NonArrayType T, NonArrayType U>
struct MakeTypeArray<T, U> {
  using type = TypeArray<T, U>;
};

// \brief Build type array with 1 type and 1 type array.
// MakeTypeArray<int, TypeArray<float&>> is the same as TypeArray<int, float&>.
template <NonArrayType T, template <typename...> typename U, NonArrayType... Us>
  requires(ArrayType<U<Us...>>)
struct MakeTypeArray<T, U<Us...>> {
  using type = TypeArray<T, Us...>;
};

// \brief Build type array with 1 type array and 1 type.
// MakeTypeArray<TypeArray<int>, float&> is the same as TypeArray<int, float&>.
template <template <typename...> typename T, NonArrayType... Ts, NonArrayType U>
  requires(ArrayType<T<Ts...>>)
struct MakeTypeArray<T<Ts...>, U> {
  using type = TypeArray<Ts..., U>;
};

// \brief Build type array with 1 type array and 1 empty type array.
// MakeTypeArray<TypeArray<int, float&>, TypeArray<>> is the same as TypeArray<int, float&>.
template <template <typename...> typename T, NonArrayType... Ts, template <typename...> typename U>
  requires(ArrayType<T<Ts...>> && ArrayType<U<>>)
struct MakeTypeArray<T<Ts...>, U<>> {
  using type = TypeArray<Ts...>;
};

// \brief Build type array with 2 type arrays.
// MakeTypeArray<TypeArray<int, float&>, TypeArray<double&&>> is the same as TypeArray<int, float&, double&&>.
template <ArrayType TArray, template <typename...> typename U, NonArrayType U0, NonArrayType... Us>
  requires(ArrayType<U<U0, Us...>>)
struct MakeTypeArray<TArray, U<U0, Us...>> {
  // The left type array recursively grab types from the begin of
  // the right type array, until the right one is empty.
  using type = MakeTypeArray<typename MakeTypeArray<TArray, U0>::type, TypeArray<Us...>>::type;
};

// \brief Build type array with any combinations of types and type arrays.
template <typename Type0, typename Type1, typename... Types>
struct MakeTypeArray<Type0, Type1, Types...> {
  // (1, 2, 3) is made with (1, 2) and 3.
  using type = MakeTypeArray<typename MakeTypeArray<Type0, Type1>::type, Types...>::type;
};

//
//
//
//
//
//
//
//
//
template <Idx i, ArrayType TArray>
struct Get;

// \brief If `i` < 0, convert negative `i` to non-negative ones like Python.
template <Idx i, NonArrayType... Ts>
  requires(i < 0)
struct Get<i, TypeArray<Ts...>> {
  using type = Get<i + TypeArray<Ts...>::size, TypeArray<Ts...>>::type;
};

// \brief If `i` == 0, return the first type of the type array.
template <Idx i, NonArrayType T, NonArrayType... Ts>
  requires(i == 0)
struct Get<i, TypeArray<T, Ts...>> {
  using type = T;
};

// \brief If `i` > 0, recursively, minus 1, and go to the next element of the type array.
template <Idx i, NonArrayType T, NonArrayType... Ts>
  requires(i > 0)
struct Get<i, TypeArray<T, Ts...>> {
  using type = Get<i - 1, TypeArray<Ts...>>::type;
};

//
//
//
//
//
//
//
//
//
template <Idx begin, Idx end, Idx step, ArrayType TArray>
struct Slice;

// \brief Step should not be 0 to prevent infinite loops, which is the minimum requirement.
template <Idx step>
concept SliceValidStep = step != 0;

// \brief The given `begin` and `end` are refined to support Python-like negative indices.
// The procedure always performed exactly once at the very beginning of `Slice`.
//
// \details This "function" will consecutively calls
// `SliceBoundBeginEnd`, `SliceShiftBeginEnd`, and `SliceClampBegin`.
//
// \warning At the very beginning, require that `step` is valid.
template <Idx begin, Idx end, Idx step, ArrayType TArray>
  requires SliceValidStep<step>
struct SliceRefineBeginEnd;

// \brief Whether the slice loop should continue.
//
// \note The following `begin` can be imagined as `i` of the `for` loops.
// We directly iterate with `begin` instead of introducing another variable `i`,
// which is the common practice in template-related programmings.
//
// \warning Care should be taken for `step` < 0.
// Consider `for (int i = 4; i > -1; --i) { ... }`.
// This case, `i` in [0, 4].
//
// \todo: Compiler bug: use `constexpr bool` instead of `concept` to make it compilable with MSVC + CUDA 12.1.
template <Idx begin, Idx end, Idx step>
constexpr bool slice_continue = (step > 0 ? begin < end : begin > end);

// \brief Whether the slice loop should stop (return) or not.
template <Idx begin, Idx end, Idx step>
constexpr bool slice_return = !slice_continue<begin, end, step>;

// \brief Bound the arbitrary given `begin` and `end` to a smaller range, both compiler and human friendly.
//
// \example Given a Python example:
// ```cpp
// a = [0, 1, 2, 3, 4]
// a[ 0:5:1] == a[ 0:6:1] == [0, 1, 2, 3, 4]
// a[-6:5:1] == a[-5:5:1] == [0, 1, 2, 3, 4]
// a[-6:5:2] == a[-5:5:2] == [0, 2, 4]
// a[ 5:5:1] == a[ 5:10000:1] = []
// ```
// We don't want the compiler to perform a 10000-depth recursion, right?
// In order to handle this, both `begin` and `end` are clamped to
// [-6, 5] to make the life easier.
template <Idx begin, Idx end, ArrayType TArray>
struct SliceBoundBeginEnd {
private:
  // -6 = -5 - 1 in the above example
  static constexpr Idx i_min = -static_cast<Idx>(TArray::size) - 1;
  // 5 in the above example
  static constexpr Idx i_max = static_cast<Idx>(TArray::size);

public:
  static constexpr Idx begin_bounded = begin > i_max ? i_max : begin < i_min ? i_min : begin;
  static constexpr Idx end_bounded = end > i_max ? i_max : end < i_min ? i_min : end;
};

// \brief For now, both `begin` and `end` have been in [-6, 5] in the above example.
// During this step, both `begin` and `end` are added by `TArray::size` if they are < 0,
// in order to move them to an "almost" positive range.
//
// \example ```cpp
// a[-5: 5: 1] -> a[ 0: 5: 1]
// a[-6: 5: 1] -> a[-1: 5: 1]
// a[ 4:-6:-1] -> a[ 4:-1:-1]
// a[ 5:-6:-1] -> a[ 5:-1:-1]
// ```
// Note that a[-1: 5: 1] should be equal to a[ 0: 5: 1], and
//           a[ 5:-1:-1] should be equal to a[ 4:-1:-1], so,
// `begin` will be "clamped" to the first valid index (if possible) towards step
// during the following pipelines.
template <Idx begin, Idx end, ArrayType TArray>
struct SliceShiftBeginEnd {
  static constexpr Idx begin_shifted = begin >= 0 ? begin : begin + TArray::size;
  static constexpr Idx end_shifted = end >= 0 ? end : end + TArray::size;
};

// \brief For now, the only remaining problem is to handle a[-1: 5: 1] and a[ 5:-1:-1],
// by clamping `begin` to the first valid index (if possible) towards step.
//
// \example ```cpp
// a[-1: 5: 1] -> a[ 0: 5: 1]
// a[ 5:-1:-1] -> a[ 4:-1:-1]
// ```
template <Idx begin, Idx step, ArrayType TArray>
struct SliceClampBegin {
private:
  static constexpr Idx i_min = 0;
  static constexpr Idx i_max = static_cast<Idx>(TArray::size) - 1;

public:
  static constexpr Idx begin_clamped = step > 0 ? begin >= i_min ? begin : i_min : begin <= i_max ? begin : i_max;
};

// \brief For now, we are ready to consecutively call the above pipelines.
//
// \warning At the very beginning, require that `step` is valid.
template <Idx begin, Idx end, Idx step, ArrayType TArray>
  requires SliceValidStep<step>
struct SliceRefineBeginEnd {
private:
  static constexpr Idx begin_bounded = SliceBoundBeginEnd<begin, end, TArray>::begin_bounded;
  static constexpr Idx end_bounded = SliceBoundBeginEnd<begin, end, TArray>::end_bounded;
  static constexpr Idx begin_shifted = SliceShiftBeginEnd<begin_bounded, end_bounded, TArray>::begin_shifted;
  static constexpr Idx end_shifted = SliceShiftBeginEnd<begin_bounded, end_bounded, TArray>::end_shifted;
  static constexpr Idx begin_clamped = SliceClampBegin<begin_shifted, step, TArray>::begin_clamped;

public:
  static constexpr Idx begin_refined = begin_clamped;
  static constexpr Idx end_refined = end_shifted;
};

//
//
//
//
//
// \brief `SliceRefineBeginEnd` should be called exactly once, why?
// After the first call, a[ 5:-6:-1] -> a[ 5:-1:-1] -> a[ 4:-1:-1] in the above example.
// Note that `end` is converted to `-1`, but,
// `-1` will be converted to `4` after the second call, which is not allowed.
// So, `SliceRefineBeginEnd` is called exactly once at the very beginning of `Slice`, and
// we need `SliceAssumeRefined` to handle all the recursions.
template <Idx begin, Idx end, Idx step, ArrayType TArray>
struct SliceAssumeRefined;

// \brief If the slice loop stops (returns), return an empty type array.
template <Idx begin, Idx end, Idx step, ArrayType TArray>
  requires slice_return<begin, end, step>
struct SliceAssumeRefined<begin, end, step, TArray> {
  using type = TypeArray<>;
};

// \brief If the slice loop continues, get the type at [begin] of the original type array,
// merge it to the returned type array with `MakeTypeArray`, and continue the loop with "begin += step".
template <Idx begin, Idx end, Idx step, ArrayType TArray>
  requires slice_continue<begin, end, step>
struct SliceAssumeRefined<begin, end, step, TArray> {
  using type = MakeTypeArray<
      // get the type at [begin] of the original type array
      typename Get<begin, TArray>::type,
      // begin += step
      typename SliceAssumeRefined<begin + step, end, step, TArray>::type>::type;
};

//
//
//
//
//
// \brief This "function" consecutively calls `SliceRefineBeginEnd` and `SliceAssumeRefined` in namespace detail.
//
// \details Implementations of `SliceRefineBeginEnd` and `SliceAssumeRefined` tells you why this design in detail.
template <Idx begin, Idx end, Idx step, ArrayType TArray>
struct Slice {
private:
  static constexpr Idx begin_refined = SliceRefineBeginEnd<begin, end, step, TArray>::begin_refined;
  static constexpr Idx end_refined = SliceRefineBeginEnd<begin, end, step, TArray>::end_refined;

public:
  using type = SliceAssumeRefined<begin_refined, end_refined, step, TArray>::type;
};

//
//
//
//
//
//
//
//
//
// \brief Reverse is implemented by creating a slice from end to start with step = -1.
template <ArrayType TArray, typename Void = void>
  requires std::is_void_v<Void>
struct Reverse {
  using type = Slice<-1, -static_cast<Idx>(TArray::size) - 1, -1, TArray>::type;
};

//
//
//
//
//
//
//
//
//
// \brief Erase is implemented by merging the left slice [0, i) with the right slice [i + 1, size).
//
// \note Care should be taken when `i` < 0.
// `i` should be first shifted to [0, size) at the very beginning.
template <Idx i, ArrayType TArray>
struct Erase {
private:
  static_assert(i >= -static_cast<Idx>(TArray::size) && i < static_cast<Idx>(TArray::size),
                "Index should not be out of range.");
  static constexpr Idx i_shifted = i >= 0 ? i : i + TArray::size;

public:
  using type = MakeTypeArray<typename Slice<0, i_shifted, 1, TArray>::type,
                             typename Slice<i_shifted + 1, TArray::size, 1, TArray>::type>::type;
};

//
//
//
//
//
//
//
//
//
// \brief Insert is implemented by merging the left slice [0, i), `T`, and the right slice [i, size).
// `T` can be a `NonArrayType` or a type array.
//
// \note Care should be taken when `i` < 0.
// `i` should be first shifted to [0, size) at the very beginning.
template <Idx i, typename T, ArrayType TArray>
struct Insert {
private:
  static_assert(i >= -static_cast<Idx>(TArray::size) && i < static_cast<Idx>(TArray::size),
                "Index should not be out of range.");
  static constexpr Idx i_shifted = i >= 0 ? i : i + TArray::size;

public:
  using type = MakeTypeArray<typename Slice<0, i_shifted, 1, TArray>::type,
                             T,
                             typename Slice<i_shifted, TArray::size, 1, TArray>::type>::type;
};

//
//
//
//
//
//
//
//
//
// \brief Pop is implemented by simpling calling `Erase`.
template <ArrayType TArray, typename Void = void>
  requires std::is_void_v<Void>
struct PopFront {
  using type = Erase<0, TArray>::type;
};

// \brief Pop is implemented by simpling calling `Erase`.
template <ArrayType TArray, typename Void = void>
  requires std::is_void_v<Void>
struct PopBack {
  using type = Erase<-1, TArray>::type;
};

//
//
//
//
//
//
//
//
//
// \brief Both `NonArrayType` and `ArrayType` T can be pushed with `MakeTypeArray`.
template <typename T, ArrayType TArray>
struct PushFront {
  using type = MakeTypeArray<T, TArray>::type;
};

// \brief Both `NonArrayType` and `ArrayType` T can be pushed with `MakeTypeArray`.
template <typename T, ArrayType TArray>
struct PushBack {
  using type = MakeTypeArray<TArray, T>::type;
};

//
//
//
//
//
//
//
//
//
template <NonArrayType T, ArrayType TArray>
struct NOf;

// \brief Recursion stops when all the types in the type array have been reached.
// Number is 0.
template <NonArrayType T>
struct NOf<T, TypeArray<>> {
  static constexpr size_t value = 0;
};

// \brief If the currently checked type `T1` is the same as the given type `T`, value += 1.
// Recursively "call" this function.
template <NonArrayType T, NonArrayType T1, NonArrayType... Ts>
struct NOf<T, TypeArray<T1, Ts...>> {
  static constexpr size_t value = (std::is_same_v<T, T1> ? 1 : 0) + NOf<T, TypeArray<Ts...>>::value;
};

// \brief `NOf` > 0 means the given type `T` exists.
template <NonArrayType T, ArrayType TArray>
struct Has {
  static constexpr bool value = NOf<T, TArray>::value > 0;
};

//
//
//
//
//
//
//
//
//
template <NonArrayType T, ArrayType TArray>
struct FirstIdx;

// \brief Recursion stops when all the types in the type array have been reached.
// No type match.
template <NonArrayType T>
struct FirstIdx<T, TypeArray<>> {
  static_assert(!std::is_same_v<T, T>, "Type not present in the type array.");
};

// \brief Recursion stops when find a matching type.
// Return 0 means returning the current index.
template <NonArrayType T, NonArrayType... Ts>
struct FirstIdx<T, TypeArray<T, Ts...>> {
  static constexpr size_t value = 0;
};

// \brief Recursively calls `FirstIdx` and add `value` by 1.
template <NonArrayType T, NonArrayType T1, NonArrayType... Ts>
struct FirstIdx<T, TypeArray<T1, Ts...>> {
  static constexpr size_t value = 1 + FirstIdx<T, TypeArray<Ts...>>::value;
};

// \brief Find last is implemented by reversing the type array and calling `FirstIdx`.
template <NonArrayType T, ArrayType TArray>
struct LastIdx {
  static constexpr size_t value = TArray::size - 1 - FirstIdx<T, typename Reverse<TArray>::type>::value;
};

//
//
//
//
//
//
//
//
//
template <NonArrayType T, ArrayType TArray>
struct Remove;

// \brief If the current type array does not has `T`, stop removal.
template <NonArrayType T, ArrayType TArray>
  requires(!Has<T, TArray>::value)
struct Remove<T, TArray> {
  using type = TArray;
};

// \brief If the current type array still has `T`, recursively call `Erase` at that index.
template <NonArrayType T, ArrayType TArray>
  requires(Has<T, TArray>::value)
struct Remove<T, TArray> {
  using type = Remove<T, typename Erase<FirstIdx<T, TArray>::value, TArray>::type>::type;
};

//
//
//
//
//
//
//
//
//
template <NonArrayType TFrom, typename TTo, ArrayType TArray>
struct Replace;

// \brief For empty type array, nothing to replace.
template <NonArrayType TFrom, typename TTo>
struct Replace<TFrom, TTo, TypeArray<>> {
  using type = TypeArray<>;
};

// \brief Check the current type of the type array `T1`.
// If `T1` is not the same as `TFrom`, push `T1` to the new type array, and go to the next type.
template <NonArrayType TFrom, typename TTo, NonArrayType T1, NonArrayType... Ts>
  requires(!std::is_same_v<TFrom, T1>)
struct Replace<TFrom, TTo, TypeArray<T1, Ts...>> {
  using type = MakeTypeArray<T1, typename Replace<TFrom, TTo, TypeArray<Ts...>>::type>::type;
};

// \brief Check the current type of the type array `T1`.
// If `T1` is the same as `TFrom`, push `TTo` to the new type array, and go to the next type.
//
// \note Both `NonArrayType` and `ArrayType` `TTo` can be pushed with `MakeTypeArray`.
template <NonArrayType TFrom, typename TTo, NonArrayType T1, NonArrayType... Ts>
  requires std::is_same_v<TFrom, T1>
struct Replace<TFrom, TTo, TypeArray<T1, Ts...>> {
  using type = MakeTypeArray<TTo, typename Replace<TFrom, TTo, TypeArray<Ts...>>::type>::type;
};

//
//
//
//
//
//
//
//
//
template <template <typename> typename F, ArrayType TArray>
struct ForEach;

// \brief Recursion stops when all the types in the type array have been reached.
template <template <typename> typename F>
struct ForEach<F, TypeArray<>> {
  using type = TypeArray<>;
};

// \brief Recursively "calls" `F<T>` and insert the resulting type into the new type array.
template <template <typename> typename F, NonArrayType T, NonArrayType... Ts>
  requires NonArrayType<F<T>>
struct ForEach<F, TypeArray<T, Ts...>> {
  //! Actually, even if F<T> returns a type array,
  //! `MakeTypeArray` will be able to flatten it. But this is weird.
  using type = MakeTypeArray<F<T>, typename ForEach<F, TypeArray<Ts...>>::type>::type;
};

//
//
//
//
//
//
//
//
//
template <template <typename> typename F, ArrayType TArray>
struct Filter;

// \brief Recursion stops when all the types in the type array have been reached.
template <template <typename> typename F>
struct Filter<F, TypeArray<>> {
  using type = TypeArray<>;
};

// \brief Recursively "calls" `F<T>`.
// If the result is false, discard `T`.
template <template <typename> typename F, NonArrayType T, NonArrayType... Ts>
  requires(!static_cast<bool>(F<T>::value))
struct Filter<F, TypeArray<T, Ts...>> {
  using type = Filter<F, TypeArray<Ts...>>::type;
};

// \brief Recursively "calls" `F<T>`.
// If the result is true, push `T` into the new type array.
template <template <typename> typename F, NonArrayType T, NonArrayType... Ts>
  requires(static_cast<bool>(F<T>::value))
struct Filter<F, TypeArray<T, Ts...>> {
  using type = MakeTypeArray<T, typename Filter<F, TypeArray<Ts...>>::type>::type;
};

} // namespace type_array::detail

} // namespace ARIA
