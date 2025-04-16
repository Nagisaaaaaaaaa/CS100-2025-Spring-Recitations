#pragma once

#include "ARIA/Auto.h"
#include "ARIA/TypeArray.h"

#include <cuda/std/tuple>

#include <ostream>

namespace ARIA {

namespace property::detail {

/// \brief The opposite of `std::same_as`.
template <typename T, typename U>
concept DiffFrom = !std::same_as<T, U>;

/// \brief Whether the given type `T` is reference or pointer.
template <typename T>
static constexpr bool isReferenceOrPointer = std::is_reference_v<T> || std::is_pointer_v<T>;

//
//
//
/// \brief A helper function to make property `operator=()` calls look like constructor calls.
/// For example, `transform.localRotation().eulerAngles() = {0.1, 0.2, 0.3};`.
///
/// \note `operator=()`s are weaker than constructors.
/// Constructors can accept something like {0, 1.0, "Hello"}, while
/// `operator=()`s can only accept arguments with same types, for example, {0.1, 0.2, 0.3}.
template <typename ValueType, typename T, size_t... is>
ARIA_HOST_DEVICE constexpr auto ConstructWithArray(const T *args, std::index_sequence<is...>) {
  return ValueType{args[is]...};
}

//
//
//
//
//
// Automatically generate implementations for the given prefix unary operator.
//! Warning, according to C++ standards, temporary variables die after the expression.
//! So, everything should be written in "one expression", for example, `return Auto(op x.value())`.
//! This is necessary to fetch the values before temporary variables die.
#define __ARIA_PROP_BASE_DEFINE_PREFIX_UNARY_OPERATOR(op)                                                              \
                                                                                                                       \
  ARIA_HOST_DEVICE friend decltype(auto) operator op(const TProperty &x) {                                             \
    return Auto(op x.value());                                                                                         \
  }

// Automatically generate implementations for the given suffix unary operator.
#define __ARIA_PROP_BASE_DEFINE_SUFFIX_UNARY_OPERATOR(op)                                                              \
                                                                                                                       \
  ARIA_HOST_DEVICE friend decltype(auto) operator op(const TProperty &x) {                                             \
    return Auto(x.value() op);                                                                                         \
  }

// Automatically generate implementations for the given binary operator.
// Without assignment means operators such as "+".
#define __ARIA_PROP_BASE_DEFINE_BINARY_OPERATOR_WITHOUT_ASSIGNMENT(op)                                                 \
                                                                                                                       \
  template <NonPropertyType TRhs>                                                                                      \
  ARIA_HOST_DEVICE friend decltype(auto) operator op(const TProperty &lhs, const TRhs &rhs) {                          \
    return Auto(lhs.value() op rhs);                                                                                   \
  }                                                                                                                    \
  template <NonPropertyType TLhs> /* This requirement is added to support sol2. */                                     \
    requires(!std::is_same_v<std::decay_t<TLhs>, std::ostringstream>)                                                  \
  ARIA_HOST_DEVICE friend decltype(auto) operator op(const TLhs &lhs, const TProperty &rhs) {                          \
    return Auto(lhs op rhs.value());                                                                                   \
  }                                                                                                                    \
  ARIA_HOST_DEVICE friend decltype(auto) operator op(const TProperty &lhs, const TProperty &rhs) {                     \
    return Auto(lhs.value() op rhs.value());                                                                           \
  }                                                                                                                    \
  template <PropertyType TPropertyThat>                                                                                \
  ARIA_HOST_DEVICE decltype(auto) operator op(const TPropertyThat &rhs) const {                                        \
    return Auto(derived().value() op rhs.value());                                                                     \
  }

// Automatically generate implementations for the given binary operator.
// With assignment means operators such as "+=".
#define __ARIA_PROP_BASE_DEFINE_BINARY_OPERATOR_WITH_ASSIGNMENT(op)                                                    \
                                                                                                                       \
  template <NonPropertyType TRhs>                                                                                      \
  ARIA_HOST_DEVICE friend decltype(auto) operator ARIA_CONCAT(op, =)(TProperty &lhs, const TRhs &rhs) {                \
    return lhs = (lhs.value() op rhs);                                                                                 \
  }                                                                                                                    \
  template <PropertyType TPropertyThat>                                                                                \
  ARIA_HOST_DEVICE friend decltype(auto) operator ARIA_CONCAT(op, =)(TProperty &lhs, const TPropertyThat &rhs) {       \
    return lhs = (lhs.value() op rhs.value());                                                                         \
  }                                                                                                                    \
  template <NonPropertyType TRhs>                                                                                      \
  ARIA_HOST_DEVICE friend decltype(auto) operator ARIA_CONCAT(op, =)(TProperty &&lhs, const TRhs &rhs) {               \
    return std::move(lhs = (lhs.value() op rhs));                                                                      \
  }                                                                                                                    \
  template <PropertyType TPropertyThat>                                                                                \
  ARIA_HOST_DEVICE friend decltype(auto) operator ARIA_CONCAT(op, =)(TProperty &&lhs, const TPropertyThat &rhs) {      \
    return std::move(lhs = (lhs.value() op rhs.value()));                                                              \
  }

//
//
//
// Implementation of the property base.
// Generate operators for `TProperty` with CRTP.
template <typename TProperty>
class PropertyBase {
public:
  // clang-format off
  // Prefix unary.
  __ARIA_PROP_BASE_DEFINE_PREFIX_UNARY_OPERATOR(+)
  __ARIA_PROP_BASE_DEFINE_PREFIX_UNARY_OPERATOR(-)
  // __ARIA_PROP_BASE_DEFINE_PREFIX_UNARY_OPERATOR(*)
  ARIA_HOST_DEVICE friend decltype(auto) operator *(const TProperty &x) {
    return *x.value();
  }
  // __ARIA_PROP_BASE_DEFINE_PREFIX_UNARY_OPERATOR(/)
  // __ARIA_PROP_BASE_DEFINE_PREFIX_UNARY_OPERATOR(%)
  // __ARIA_PROP_BASE_DEFINE_PREFIX_UNARY_OPERATOR(^)
  //! It is extremely dangerous to define a l-value reference operator.
  // __ARIA_PROP_BASE_DEFINE_PREFIX_UNARY_OPERATOR(&)
  // __ARIA_PROP_BASE_DEFINE_PREFIX_UNARY_OPERATOR(|)
  __ARIA_PROP_BASE_DEFINE_PREFIX_UNARY_OPERATOR(~)
  __ARIA_PROP_BASE_DEFINE_PREFIX_UNARY_OPERATOR(!)
  //! Handled by copy constructors and assignment operators.
  // __ARIA_PROP_BASE_DEFINE_PREFIX_UNARY_OPERATOR(=)
  // __ARIA_PROP_BASE_DEFINE_PREFIX_UNARY_OPERATOR(<)
  // __ARIA_PROP_BASE_DEFINE_PREFIX_UNARY_OPERATOR(>)
  // __ARIA_PROP_BASE_DEFINE_PREFIX_UNARY_OPERATOR(<<)
  // __ARIA_PROP_BASE_DEFINE_PREFIX_UNARY_OPERATOR(>>)
  // __ARIA_PROP_BASE_DEFINE_PREFIX_UNARY_OPERATOR(==)
  // __ARIA_PROP_BASE_DEFINE_PREFIX_UNARY_OPERATOR(!=)
  // __ARIA_PROP_BASE_DEFINE_PREFIX_UNARY_OPERATOR(<=)
  // __ARIA_PROP_BASE_DEFINE_PREFIX_UNARY_OPERATOR(>=)
  //! It is extremely dangerous to define a r-value reference operator.
  // __ARIA_PROP_BASE_DEFINE_PREFIX_UNARY_OPERATOR(&&)
  // __ARIA_PROP_BASE_DEFINE_PREFIX_UNARY_OPERATOR(||)
  //! The prefix `++` and `--` operators are special cases.
  // __ARIA_PROP_BASE_DEFINE_PREFIX_UNARY_OPERATOR(++)
  ARIA_HOST_DEVICE decltype(auto) operator++() { return derived() += 1; }
  // __ARIA_PROP_BASE_DEFINE_PREFIX_UNARY_OPERATOR(--)
  ARIA_HOST_DEVICE decltype(auto) operator--() { return derived() -= 1; }
  // __ARIA_PROP_BASE_DEFINE_PREFIX_UNARY_OPERATOR(->)

  // Suffix unary.
  //! Dangerous to define `i++` because it is not able to return a property
  //! having value `i`. It is only able to return a value instead of a property,
  //! but that will make the remaining code weird.
  // ARIA_HOST_DEVICE const auto operator++(int) {
  //   auto tmp = derived().value(); //! Should not use decltype(auto) here because a copy is required.
  //   derived() += 1;
  //   return tmp;
  // }
  // ARIA_HOST_DEVICE const auto operator--(int) {
  //   auto tmp = derived().value(); //! Should not use decltype(auto) here because a copy is required.
  //   derived() -= 1;
  //   return tmp;
  // }
  //! `->` operator should be defined in-class
  // __ARIA_PROP_BASE_DEFINE_SUFFIX_UNARY_OPERATOR(->) // TODO: Support C++23
  // operator ->*.

  // Binary without assignment.
  __ARIA_PROP_BASE_DEFINE_BINARY_OPERATOR_WITHOUT_ASSIGNMENT(+)
  __ARIA_PROP_BASE_DEFINE_BINARY_OPERATOR_WITHOUT_ASSIGNMENT(-)
  __ARIA_PROP_BASE_DEFINE_BINARY_OPERATOR_WITHOUT_ASSIGNMENT(*)
  __ARIA_PROP_BASE_DEFINE_BINARY_OPERATOR_WITHOUT_ASSIGNMENT(/)
  __ARIA_PROP_BASE_DEFINE_BINARY_OPERATOR_WITHOUT_ASSIGNMENT(%)
  __ARIA_PROP_BASE_DEFINE_BINARY_OPERATOR_WITHOUT_ASSIGNMENT(^)
  __ARIA_PROP_BASE_DEFINE_BINARY_OPERATOR_WITHOUT_ASSIGNMENT(&)
  __ARIA_PROP_BASE_DEFINE_BINARY_OPERATOR_WITHOUT_ASSIGNMENT(|)
  // __ARIA_PROP_BASE_DEFINE_BINARY_OPERATOR_WITHOUT_ASSIGNMENT(~)
  // __ARIA_PROP_BASE_DEFINE_BINARY_OPERATOR_WITHOUT_ASSIGNMENT(!)
  //! Handled by copy constructors and assignment operators.
  // __ARIA_PROP_BASE_DEFINE_BINARY_OPERATOR_WITHOUT_ASSIGNMENT(=)
  __ARIA_PROP_BASE_DEFINE_BINARY_OPERATOR_WITHOUT_ASSIGNMENT(<)
  __ARIA_PROP_BASE_DEFINE_BINARY_OPERATOR_WITHOUT_ASSIGNMENT(>)
  //! Do not trivially support `std::ostream`,
  //! it is recommended to always use `Auto`.
  __ARIA_PROP_BASE_DEFINE_BINARY_OPERATOR_WITHOUT_ASSIGNMENT(<<)
  friend std::ostream &operator<<(std::ostream &os, const TProperty &x) {
    os << x.value();
    return os;
  }
  __ARIA_PROP_BASE_DEFINE_BINARY_OPERATOR_WITHOUT_ASSIGNMENT(>>)
  __ARIA_PROP_BASE_DEFINE_BINARY_OPERATOR_WITHOUT_ASSIGNMENT(==)
  //! Implicitly defined by operator==.
  __ARIA_PROP_BASE_DEFINE_BINARY_OPERATOR_WITHOUT_ASSIGNMENT(!=)
  __ARIA_PROP_BASE_DEFINE_BINARY_OPERATOR_WITHOUT_ASSIGNMENT(<=)
  __ARIA_PROP_BASE_DEFINE_BINARY_OPERATOR_WITHOUT_ASSIGNMENT(>=)
  __ARIA_PROP_BASE_DEFINE_BINARY_OPERATOR_WITHOUT_ASSIGNMENT(&&)
  __ARIA_PROP_BASE_DEFINE_BINARY_OPERATOR_WITHOUT_ASSIGNMENT(||)
  // __ARIA_PROP_BASE_DEFINE_BINARY_OPERATOR_WITHOUT_ASSIGNMENT(++)
  // __ARIA_PROP_BASE_DEFINE_BINARY_OPERATOR_WITHOUT_ASSIGNMENT(--)
  // __ARIA_PROP_BASE_DEFINE_BINARY_OPERATOR_WITHOUT_ASSIGNMENT(->)

  // Binary with assignment.
  __ARIA_PROP_BASE_DEFINE_BINARY_OPERATOR_WITH_ASSIGNMENT(+)
  __ARIA_PROP_BASE_DEFINE_BINARY_OPERATOR_WITH_ASSIGNMENT(-)
  __ARIA_PROP_BASE_DEFINE_BINARY_OPERATOR_WITH_ASSIGNMENT(*)
  __ARIA_PROP_BASE_DEFINE_BINARY_OPERATOR_WITH_ASSIGNMENT(/)
  __ARIA_PROP_BASE_DEFINE_BINARY_OPERATOR_WITH_ASSIGNMENT(%)
  __ARIA_PROP_BASE_DEFINE_BINARY_OPERATOR_WITH_ASSIGNMENT(^)
  __ARIA_PROP_BASE_DEFINE_BINARY_OPERATOR_WITH_ASSIGNMENT(&)
  __ARIA_PROP_BASE_DEFINE_BINARY_OPERATOR_WITH_ASSIGNMENT(|)
  __ARIA_PROP_BASE_DEFINE_BINARY_OPERATOR_WITH_ASSIGNMENT(>>)
  __ARIA_PROP_BASE_DEFINE_BINARY_OPERATOR_WITH_ASSIGNMENT(<<)

  // clang-format on

  // Special operators.
  //! `operator()` and `operator[]` are special cases.
  template <typename... Ts>
  ARIA_HOST_DEVICE decltype(auto) operator()(Ts &&...ts) {
    if constexpr (std::same_as<decltype(derived().value().operator()(std::forward<Ts>(ts)...)), void>) {
      derived().value().operator()(std::forward<Ts>(ts)...);
    } else {
      return Auto(derived().value().operator()(std::forward<Ts>(ts)...));
    }
  }

  template <typename... Ts>
  ARIA_HOST_DEVICE decltype(auto) operator()(Ts &&...ts) const {
    if constexpr (std::same_as<decltype(derived().value().operator()(std::forward<Ts>(ts)...)), void>) {
      derived().value().operator()(std::forward<Ts>(ts)...);
    } else {
      return Auto(derived().value().operator()(std::forward<Ts>(ts)...));
    }
  }

  template <typename... Ts>
  ARIA_HOST_DEVICE decltype(auto) operator[](Ts &&...ts) {
    if constexpr (std::same_as<decltype(derived().value().operator[](std::forward<Ts>(ts)...)), void>) {
      derived().value().operator[](std::forward<Ts>(ts)...);
    } else {
      return Auto(derived().value().operator[](std::forward<Ts>(ts)...));
    }
  }

  template <typename... Ts>
  ARIA_HOST_DEVICE decltype(auto) operator[](Ts &&...ts) const {
    if constexpr (std::same_as<decltype(derived().value().operator[](std::forward<Ts>(ts)...)), void>) {
      derived().value().operator[](std::forward<Ts>(ts)...);
    } else {
      return Auto(derived().value().operator[](std::forward<Ts>(ts)...));
    }
  }

private:
  // Get reference of the derived class with CRTP.
  ARIA_HOST_DEVICE TProperty &derived() { return *static_cast<TProperty *>(this); }

  ARIA_HOST_DEVICE const TProperty &derived() const { return *static_cast<const TProperty *>(this); }
};

}; // namespace property::detail

//
//
//
//
//
#define __ARIA_PROP_GETTER(PROP_NAME) ARIA_CONCAT(PROP_NAME, ARIAPropertyGetterImplementation)

#define __ARIA_PROP_SETTER(PROP_NAME) ARIA_CONCAT(PROP_NAME, ARIAPropertySetterImplementation)

//
//
//
//
//
#define __ARIA_PROP_BEGIN(ACCESS_GET, ACCESS_SET, SPECIFIERS, TYPE, PROP_NAME)                                         \
                                                                                                                       \
  /* Users should not directly access the underlying property types. */                                                \
  static_assert(!property::detail::PropertyType<std::decay_t<TYPE>>,                                                   \
                "The given property value type should not be a property type");                                        \
                                                                                                                       \
  static_assert(!std::is_const_v<std::remove_reference_t<TYPE>>,                                                       \
                "The given property value type should not be const because "                                           \
                "const-ness should be properly handled by setters and getters");                                       \
                                                                                                                       \
  static_assert(!std::is_rvalue_reference_v<TYPE>, "The given property value type should not be a r-value reference"); \
                                                                                                                       \
  /* Use getter accessibility here. */                                                                                 \
  ACCESS_GET:                                                                                                          \
  /* The actual class name of the property, which is anonymous. */                                                     \
  /* Properties are implemented similar to proxies of `std::vector<bool>`. */                                          \
  /* Template class is used to handle both `Vec3` and `const Vec3`, see `TObjectMaybeConst`. */                        \
  /*! Also, methods of template class are compiled ONLY WHEN THEY ARE USED, */                                         \
  /*! which means that operators, getters, and setters are not compiled until they are actually used. */               \
  /*! This is helpful because not all classes support all kinds of operators.  */                                      \
  /*! For example, the `<<` operator is defined for properties with `TYPE` equals to `Vec3`, */                        \
  /*! but we don't get any compiler error until `operator<<()` is actually called. */                                  \
  /*! So we can pre-define everything for all properties, even though many will not work. */                           \
  template <typename TObjectMaybeConst, typename... TUVWArgs>                                                          \
  class ARIA_ANON(PROP_NAME);                                                                                          \
                                                                                                                       \
  /* The actual non-const property method. */                                                                          \
  template <typename... TUVWArgs>                                                                                      \
  [[nodiscard]] SPECIFIERS decltype(auto) PROP_NAME(TUVWArgs &&...propArgs) {                                          \
    /* Generate an instance of the property, that is why `auto` is dangerous. */                                       \
    return ARIA_ANON(PROP_NAME)<decltype(*this), TUVWArgs...>{*this, std::forward<TUVWArgs>(propArgs)...};             \
  }                                                                                                                    \
  /* The actual const property method. */                                                                              \
  template <typename... TUVWArgs>                                                                                      \
  [[nodiscard]] SPECIFIERS decltype(auto) PROP_NAME(TUVWArgs &&...propArgs) const {                                    \
    return ARIA_ANON(PROP_NAME)<decltype(*this), TUVWArgs...>{*this, std::forward<TUVWArgs>(propArgs)...};             \
  }                                                                                                                    \
                                                                                                                       \
  /* Implementation of the actual property class. */                                                                   \
  /* Use CRTP to automatically generate operators, and also, satisfies the `PropertyType` concept. */                  \
  template <typename TObjectMaybeConst, typename... TUVWArgs>                                                          \
      class ARIA_ANON(PROP_NAME) final                                                                                 \
      : public property::detail::PropertyBase < ARIA_ANON(PROP_NAME) < TObjectMaybeConst,                              \
      TUVWArgs... >> {                                                                                                 \
    /* Using the `Type` to support `ARIA_PROP_FUNC` */                                                                 \
  private:                                                                                                             \
    using Type = TYPE;                                                                                                 \
                                                                                                                       \
  private:                                                                                                             \
    /* This `TProperty` will be used by the property methods of sub-properties, */                                     \
    /* to help the template type deduction. */                                                                         \
    using TProperty = ARIA_ANON(PROP_NAME);                                                                            \
                                                                                                                       \
    using TObject = std::remove_const_t<TObjectMaybeConst>;                                                            \
    /* Declared `friend` to call private user-defined getters and setters. */                                          \
    friend std::decay_t<TObject>;                                                                                      \
                                                                                                                       \
    /* Properties owns the reference to the actual object. */                                                          \
    /* That is why `auto` is dangerous. */                                                                             \
    TObjectMaybeConst &object;                                                                                         \
                                                                                                                       \
    cuda::std::tuple<std::decay_t<TUVWArgs>...> propArgs;                                                              \
                                                                                                                       \
    /* Constructor of the property, called by the property methods. */                                                 \
    SPECIFIERS explicit ARIA_ANON(PROP_NAME)(TObjectMaybeConst & object, const TUVWArgs &...propArgs)                  \
        : object(object), propArgs(propArgs...) {}                                                                     \
                                                                                                                       \
    /* Properties use lazy evaluation in order to support operations and getters. */                                   \
    /* For example, `transform.forward().length()` is not immediately evaluated to a float, */                         \
    /* it is still a proxy, until `float v = transform.forward().length()` or something else is called. */             \
    /* That is because we may write `transform.forward().length() = 10`, which will recursively calls */               \
    /* the setter of `length` defined by `Vec3f` and the setter of `forward` defined by `Transform`. */                \
    /* So, lazy evaluations are necessary for proxies. */                                                              \
                                                                                                                       \
    /* This `static` function performs the true evaluation. */                                                         \
    /* This function will be called by `value()`, `operator decltype(auto)()`, and */                                  \
    /* recursively by `Get()`, `Set()` of sub-properties. */                                                           \
                                                                                                                       \
    /* This function is defined `static` to handle `auto c = obj.a().b().c();`. */                                     \
    /* See comments of `ARIA_SUB_PROP_BEGIN`. */                                                                       \
    [[nodiscard]] static SPECIFIERS decltype(auto) Get(TObjectMaybeConst &object, const auto &...propArgs)             \
      requires property::detail::isReferenceOrPointer<Type>                                                            \
    {                                                                                                                  \
      static_assert(                                                                                                   \
          !property::detail::isReferenceOrPointer<Type> ||                                                             \
              property::detail::isReferenceOrPointer<decltype(object.__ARIA_PROP_GETTER(PROP_NAME)(propArgs...))>,     \
          "The getter is only allowed to return reference or pointer when "                                            \
          "the specified property value type is a reference or a pointer");                                            \
                                                                                                                       \
      /* Calls the user-defined getter. */                                                                             \
      return object.__ARIA_PROP_GETTER(PROP_NAME)(propArgs...);                                                        \
    }                                                                                                                  \
    [[nodiscard]] static SPECIFIERS Type Get(TObjectMaybeConst &object, const auto &...propArgs)                       \
      requires(!property::detail::isReferenceOrPointer<Type>)                                                          \
    {                                                                                                                  \
      static_assert(                                                                                                   \
          !property::detail::isReferenceOrPointer<Type> ||                                                             \
              property::detail::isReferenceOrPointer<decltype(object.__ARIA_PROP_GETTER(PROP_NAME)(propArgs...))>,     \
          "The getter is only allowed to return reference or pointer when "                                            \
          "the specified property value type is a reference or a pointer");                                            \
                                                                                                                       \
      /* Calls the user-defined getter. */                                                                             \
      return Auto(object.__ARIA_PROP_GETTER(PROP_NAME)(propArgs...));                                                  \
    }                                                                                                                  \
    template <typename TUVW>                                                                                           \
    static SPECIFIERS void Set(TObject &object, TUVW &&value, const auto &...propArgs) {                               \
      /* Perform type check. */                                                                                        \
      /* This check is performed to restrict behavior of the user-defined setter. */                                   \
      /* For example, users should not set a dog to a cat, */                                                          \
      /* even though their setters can handle this case. */                                                            \
      static_assert(std::convertible_to<decltype(value), std::decay_t<Type>> ||                                        \
                        std::is_same_v<std::decay_t<TUVW>, On> || std::is_same_v<std::decay_t<TUVW>, Off>,             \
                    "The value given to the setter should be convertible to the given property value type");           \
                                                                                                                       \
      /* Also, return type of the setter is restricted to `void`. */                                                   \
      /* TODO: NVCC bug here. */                                                                                       \
      /* static_assert(requires {                                                                                  */  \
      /*   { object.__ARIA_PROP_SETTER(PROP_NAME)(propArgs..., std::forward<TUVW>(value)) } -> std::same_as<void>; */  \
      /* }, "Return type of the setter should be void");                                                           */  \
                                                                                                                       \
      /* Calls the user-defined setter. */                                                                             \
      object.__ARIA_PROP_SETTER(PROP_NAME)(propArgs..., std::forward<TUVW>(value));                                    \
    }                                                                                                                  \
                                                                                                                       \
  public:                                                                                                              \
    ARIA_COPY_MOVE_ABILITY(ARIA_ANON(PROP_NAME), delete, default);                                                     \
                                                                                                                       \
    /* Each property is also designed to be an accessor, which */                                                      \
    /* means that users can set or reset arguments with `obj.a().args(...)`. */                                        \
    /* This will generate new properties with different arguments. */                                                  \
    template <typename... TUVWArgsNew>                                                                                 \
    [[nodiscard]] SPECIFIERS decltype(auto) args(TUVWArgsNew &&...propArgsNew) {                                       \
      return ARIA_ANON(PROP_NAME)<TObjectMaybeConst, TUVWArgsNew...>{this->object,                                     \
                                                                     std::forward<TUVWArgsNew>(propArgsNew)...};       \
    }                                                                                                                  \
    template <typename... TUVWArgsNew>                                                                                 \
    [[nodiscard]] SPECIFIERS decltype(auto) args(TUVWArgsNew &&...propArgsNew) const {                                 \
      return ARIA_ANON(PROP_NAME)<TObjectMaybeConst, TUVWArgsNew...>{this->object,                                     \
                                                                     std::forward<TUVWArgsNew>(propArgsNew)...};       \
    }                                                                                                                  \
                                                                                                                       \
    /* Calls the user-defined getter. */                                                                               \
    [[nodiscard]] SPECIFIERS decltype(auto) value() {                                                                  \
      return cuda::std::apply(                                                                                         \
          [&](const auto &...propArgsTuple) -> decltype(auto) { return Get(object, propArgsTuple...); }, propArgs);    \
    }                                                                                                                  \
    [[nodiscard]] SPECIFIERS decltype(auto) value() const {                                                            \
      return cuda::std::apply(                                                                                         \
          [&](const auto &...propArgsTuple) -> decltype(auto) { return Get(object, propArgsTuple...); }, propArgs);    \
    }                                                                                                                  \
                                                                                                                       \
    /* Calls the user-defined getter. */                                                                               \
    [[nodiscard]] SPECIFIERS operator decltype(auto)() {                                                               \
      return value();                                                                                                  \
    }                                                                                                                  \
    [[nodiscard]] SPECIFIERS operator decltype(auto)() const {                                                         \
      return value();                                                                                                  \
    }                                                                                                                  \
                                                                                                                       \
    /* `operator->()` cannot be handled by CRTP, because it should be defined in-class */                              \
    [[nodiscard]] SPECIFIERS ARIA_ANON(PROP_NAME) *operator-> () {                                                     \
      return this;                                                                                                     \
    }                                                                                                                  \
    [[nodiscard]] SPECIFIERS const ARIA_ANON(PROP_NAME) *operator-> () const {                                         \
      return this;                                                                                                     \
    }                                                                                                                  \
                                                                                                                       \
    /* Use setter accessibility here. */                                                                               \
    /* clang-format off */                                                                                             \
  ACCESS_SET:                                                                                                          \
    /* Calls the user-defined setter. */                                                                               \
    template <typename TUVW>                                                                                           \
     SPECIFIERS ARIA_ANON(PROP_NAME) &operator=(TUVW &&value) {                                                        \
      cuda::std::apply(                                                                                                \
          [&](const auto &...propArgsTuple) { Set(object, std::forward<TUVW>(value), propArgsTuple...); }, propArgs);  \
      return *this;                                                                                                    \
    }                                                                                                                  \
    /* Calls the user-defined setter with an array. */                                                                 \
    template <typename TUVW, size_t n>                                                                                 \
     SPECIFIERS ARIA_ANON(PROP_NAME) &operator=(const TUVW (&args)[n]) {                                               \
      cuda::std::apply([&](const auto &...propArgsTuple) {                                                             \
        Set(object, property::detail::ConstructWithArray<std::decay_t<Type>>(args, std::make_index_sequence<n>{}),     \
            propArgsTuple...);                                                                                         \
      }, propArgs);                                                                                                    \
      return *this;                                                                                                    \
    }                                                                                                                  \
                                                                                                                       \
  private:                                                                                                             \
    class ARIA_CONCAT(DummyClassForPropBegin, PROP_NAME) {}
// clang-format on

// clang-format off
#define __ARIA_PROP_END                                                                                                \
  };                                                                                                                   \
                                                                                                                       \
private:                                                                                                               \
  class ARIA_ANON(DummyClassForPropEnd) {}

#define __ARIA_PROP(ACCESS_GET, ACCESS_SET, SPECIFIERS, TYPE, PROP_NAME)                                               \
  __ARIA_PROP_BEGIN(ACCESS_GET, ACCESS_SET, SPECIFIERS, TYPE, PROP_NAME);                                              \
  __ARIA_PROP_END
// clang-format on

//
//
//
//
//
#define __ARIA_SUB_PROP_BEGIN(SPECIFIERS, TYPE, PROP_NAME)                                                             \
                                                                                                                       \
  /* Very similar to `ARIA_PROP_BEGIN`, please read the comments there. */                                             \
  static_assert(!property::detail::PropertyType<std::decay_t<TYPE>>,                                                   \
                "The given sub-property value type should not be a property type");                                    \
                                                                                                                       \
  static_assert(!std::is_const_v<std::remove_reference_t<TYPE>>,                                                       \
                "The given sub-property value type should not be const because "                                       \
                "const-ness should be properly handled by setters and getters");                                       \
                                                                                                                       \
  static_assert(!std::is_rvalue_reference_v<TYPE>,                                                                     \
                "The given sub-property value type should not be a r-value reference");                                \
                                                                                                                       \
  /* Sub-properties are always public, let property accessibility dominates. */                                        \
public:                                                                                                                \
  template <typename ARIA_ANON(ARIA_CONCAT(TPropertyBaseMaybeConst, PROP_NAME)), typename... TUVWArgs>                 \
  class ARIA_ANON(PROP_NAME);                                                                                          \
                                                                                                                       \
  template <typename... TUVWArgs>                                                                                      \
  [[nodiscard]] SPECIFIERS decltype(auto) PROP_NAME(TUVWArgs &&...propArgs) {                                          \
    /* All sub-properties also owns the actual object. */                                                              \
    /* For example, `obj.a().b().c()`, then `a` owns `obj`, `b` owns `obj`, and `c` also owns `obj`. */                \
    /* There exist another design, let `b` owns `a` and `c` owns `b`. */                                               \
    /* But that will make `auto c = obj.a().b().c();` much more dangerous, */                                          \
    /* because `a` and `b` are temporary variables and vanishes after the expression. */                               \
    /*! But, even we choose the better design, `auto` is still dangerous. */                                           \
    /*! See `Auto.h` for more details. */                                                                              \
                                                                                                                       \
    /* This `TProperty` here is the one defined by the base property, */                                               \
    /* to help the template type deduction. */                                                                         \
    return ARIA_ANON(PROP_NAME)<TProperty, TUVWArgs...>{this->object, std::forward<TUVWArgs>(propArgs)...};            \
  }                                                                                                                    \
  template <typename... TUVWArgs>                                                                                      \
  [[nodiscard]] SPECIFIERS decltype(auto) PROP_NAME(TUVWArgs &&...propArgs) const {                                    \
    return ARIA_ANON(PROP_NAME)<const TProperty, TUVWArgs...>{this->object, std::forward<TUVWArgs>(propArgs)...};      \
  }                                                                                                                    \
                                                                                                                       \
  /* Sub-properties are also property types. */                                                                        \
  template <typename ARIA_ANON(ARIA_CONCAT(TPropertyBaseMaybeConst, PROP_NAME)), typename... TUVWArgs>                 \
      class ARIA_ANON(PROP_NAME) final : public property::detail::PropertyBase < ARIA_ANON(PROP_NAME) <                \
                                         ARIA_ANON(ARIA_CONCAT(TPropertyBaseMaybeConst, PROP_NAME)),                   \
      TUVWArgs... >> {                                                                                                 \
  private:                                                                                                             \
    using Type = TYPE;                                                                                                 \
                                                                                                                       \
  private:                                                                                                             \
    /* This `TProperty` will be used by the property methods of sub-sub-properties, */                                 \
    /* to help the template type deduction. */                                                                         \
    using TProperty = ARIA_ANON(PROP_NAME);                                                                            \
                                                                                                                       \
    /* The base property type. */                                                                                      \
    using TPropertyBase = std::remove_const_t<ARIA_ANON(ARIA_CONCAT(TPropertyBaseMaybeConst, PROP_NAME))>;             \
    /* Declared `friend` to call `Get()` and `Set()` of the base property. */                                          \
    friend std::decay_t<TPropertyBase>;                                                                                \
                                                                                                                       \
    /* As explained above, all sub-properties also owns the actual object. */                                          \
    TObjectMaybeConst &object;                                                                                         \
                                                                                                                       \
    cuda::std::tuple<std::decay_t<TUVWArgs>...> propArgs;                                                              \
                                                                                                                       \
    SPECIFIERS explicit ARIA_ANON(PROP_NAME)(TObjectMaybeConst & object, const TUVWArgs &...propArgs)                  \
        : object(object), propArgs(propArgs...) {}                                                                     \
                                                                                                                       \
    [[nodiscard]] static SPECIFIERS decltype(auto) Get(TObjectMaybeConst &object, const auto &...propArgs)             \
      requires property::detail::isReferenceOrPointer<Type>                                                            \
    {                                                                                                                  \
      decltype(auto) tmp = TPropertyBase::Get(object);                                                                 \
                                                                                                                       \
      static_assert(property::detail::isReferenceOrPointer<decltype(tmp)> ||                                           \
                        !property::detail::isReferenceOrPointer<Type>,                                                 \
                    "Sub-property value type of a non-reference and non-pointer property should "                      \
                    "not be a reference or a pointer type");                                                           \
                                                                                                                       \
      if constexpr (std::is_pointer_v<decltype(tmp)>) {                                                                \
        static_assert(!property::detail::isReferenceOrPointer<Type> ||                                                 \
                          (property::detail::PropertyType<std::decay_t<decltype(tmp->PROP_NAME(propArgs...))>> ||      \
                           property::detail::isReferenceOrPointer<decltype(tmp->PROP_NAME(propArgs...))>),             \
                      "The getter is only allowed to return reference or pointer when "                                \
                      "the specified sub-property value type is a reference or a pointer");                            \
                                                                                                                       \
        if constexpr (property::detail::PropertyType<std::decay_t<decltype(tmp->PROP_NAME(propArgs...))>>)             \
          return tmp->PROP_NAME(propArgs...).value();                                                                  \
        else                                                                                                           \
          return tmp->PROP_NAME(propArgs...);                                                                          \
      } else {                                                                                                         \
        static_assert(!property::detail::isReferenceOrPointer<Type> ||                                                 \
                          (property::detail::PropertyType<std::decay_t<decltype(tmp.PROP_NAME(propArgs...))>> ||       \
                           property::detail::isReferenceOrPointer<decltype(tmp.PROP_NAME(propArgs...))>),              \
                      "The getter is only allowed to return reference or pointer when "                                \
                      "the specified sub-property value type is a reference or a pointer");                            \
                                                                                                                       \
        if constexpr (property::detail::PropertyType<std::decay_t<decltype(tmp.PROP_NAME(propArgs...))>>)              \
          return tmp.PROP_NAME(propArgs...).value();                                                                   \
        else                                                                                                           \
          return tmp.PROP_NAME(propArgs...);                                                                           \
      }                                                                                                                \
    }                                                                                                                  \
    [[nodiscard]] static SPECIFIERS Type Get(TObjectMaybeConst &object, const auto &...propArgs)                       \
      requires(!property::detail::isReferenceOrPointer<Type>)                                                          \
    {                                                                                                                  \
      decltype(auto) tmp = TPropertyBase::Get(object);                                                                 \
                                                                                                                       \
      static_assert(property::detail::isReferenceOrPointer<decltype(tmp)> ||                                           \
                        !property::detail::isReferenceOrPointer<Type>,                                                 \
                    "Sub-property value type of a non-reference property should not be a reference type");             \
                                                                                                                       \
      if constexpr (std::is_pointer_v<decltype(tmp)>) {                                                                \
        static_assert(!property::detail::isReferenceOrPointer<Type> ||                                                 \
                          (property::detail::PropertyType<std::decay_t<decltype(tmp->PROP_NAME(propArgs...))>> ||      \
                           property::detail::isReferenceOrPointer<decltype(tmp->PROP_NAME(propArgs...))>),             \
                      "The getter is only allowed to return reference or pointer when "                                \
                      "the specified sub-property value type is a reference");                                         \
                                                                                                                       \
        return Auto(tmp->PROP_NAME(propArgs...));                                                                      \
      } else {                                                                                                         \
        static_assert(!property::detail::isReferenceOrPointer<Type> ||                                                 \
                          (property::detail::PropertyType<std::decay_t<decltype(tmp.PROP_NAME(propArgs...))>> ||       \
                           property::detail::isReferenceOrPointer<decltype(tmp.PROP_NAME(propArgs...))>),              \
                      "The getter is only allowed to return reference or pointer when "                                \
                      "the specified sub-property value type is a reference");                                         \
                                                                                                                       \
        return Auto(tmp.PROP_NAME(propArgs...));                                                                       \
      }                                                                                                                \
    }                                                                                                                  \
    template <typename TUVW>                                                                                           \
    static SPECIFIERS void Set(TObject &object, TUVW &&value, const auto &...propArgs) {                               \
      static_assert(std::convertible_to<decltype(value), std::decay_t<Type>> ||                                        \
                        std::is_same_v<std::decay_t<TUVW>, On> || std::is_same_v<std::decay_t<TUVW>, Off>,             \
                    "The value given to the setter should be convertible to the given property value type");           \
                                                                                                                       \
      decltype(auto) tmp = TPropertyBase::Get(object);                                                                 \
                                                                                                                       \
      if constexpr (std::is_pointer_v<decltype(tmp)>) {                                                                \
        using TGet = decltype(tmp->PROP_NAME(propArgs...));                                                            \
                                                                                                                       \
        constexpr bool isGetProxy = property::detail::ProxyType<TGet>;                                                 \
        constexpr bool isGetReferenceOrPointer = property::detail::isReferenceOrPointer<TGet>;                         \
        constexpr bool isGetValue = !isGetReferenceOrPointer && !isGetProxy;                                           \
                                                                                                                       \
        static_assert(!isGetValue, "Return type of this member should not be a non-proxy value type");                 \
                                                                                                                       \
        tmp->PROP_NAME(propArgs...) = std::forward<TUVW>(value);                                                       \
                                                                                                                       \
        TPropertyBase::Set(object, std::move(tmp));                                                                    \
      } else {                                                                                                         \
        using TGet = decltype(tmp.PROP_NAME(propArgs...));                                                             \
                                                                                                                       \
        constexpr bool isGetProxy = property::detail::ProxyType<TGet>;                                                 \
        constexpr bool isGetReferenceOrPointer = property::detail::isReferenceOrPointer<TGet>;                         \
        constexpr bool isGetValue = !isGetReferenceOrPointer && !isGetProxy;                                           \
                                                                                                                       \
        static_assert(!isGetValue, "Return type of this member should not be a non-proxy value type");                 \
                                                                                                                       \
        tmp.PROP_NAME(propArgs...) = std::forward<TUVW>(value);                                                        \
                                                                                                                       \
        TPropertyBase::Set(object, std::move(tmp));                                                                    \
      }                                                                                                                \
    }                                                                                                                  \
                                                                                                                       \
  public:                                                                                                              \
    ARIA_COPY_MOVE_ABILITY(ARIA_ANON(PROP_NAME), delete, default);                                                     \
                                                                                                                       \
    template <typename... TUVWArgsNew>                                                                                 \
    [[nodiscard]] SPECIFIERS decltype(auto) args(TUVWArgsNew &&...propArgsNew) {                                       \
      return ARIA_ANON(PROP_NAME)<TObjectMaybeConst, TUVWArgsNew...>{this->object,                                     \
                                                                     std::forward<TUVWArgsNew>(propArgsNew)...};       \
    }                                                                                                                  \
    template <typename... TUVWArgsNew>                                                                                 \
    [[nodiscard]] SPECIFIERS decltype(auto) args(TUVWArgsNew &&...propArgsNew) const {                                 \
      return ARIA_ANON(PROP_NAME)<TObjectMaybeConst, TUVWArgsNew...>{this->object,                                     \
                                                                     std::forward<TUVWArgsNew>(propArgsNew)...};       \
    }                                                                                                                  \
                                                                                                                       \
    [[nodiscard]] SPECIFIERS decltype(auto) value() {                                                                  \
      return cuda::std::apply(                                                                                         \
          [&](const auto &...propArgsTuple) -> decltype(auto) { return Get(object, propArgsTuple...); }, propArgs);    \
    }                                                                                                                  \
    [[nodiscard]] SPECIFIERS decltype(auto) value() const {                                                            \
      return cuda::std::apply(                                                                                         \
          [&](const auto &...propArgsTuple) -> decltype(auto) { return Get(object, propArgsTuple...); }, propArgs);    \
    }                                                                                                                  \
                                                                                                                       \
    [[nodiscard]] SPECIFIERS operator decltype(auto)() {                                                               \
      return value();                                                                                                  \
    }                                                                                                                  \
    [[nodiscard]] SPECIFIERS operator decltype(auto)() const {                                                         \
      return value();                                                                                                  \
    }                                                                                                                  \
                                                                                                                       \
    [[nodiscard]] SPECIFIERS ARIA_ANON(PROP_NAME) *operator-> () {                                                     \
      return this;                                                                                                     \
    }                                                                                                                  \
    [[nodiscard]] SPECIFIERS const ARIA_ANON(PROP_NAME) *operator-> () const {                                         \
      return this;                                                                                                     \
    }                                                                                                                  \
                                                                                                                       \
    template <typename TUVW>                                                                                           \
    SPECIFIERS ARIA_ANON(PROP_NAME) &operator=(TUVW &&value) {                                                         \
      cuda::std::apply(                                                                                                \
          [&](const auto &...propArgsTuple) { Set(object, std::forward<TUVW>(value), propArgsTuple...); }, propArgs);  \
      return *this;                                                                                                    \
    }                                                                                                                  \
    template <typename TUVW, size_t n>                                                                                 \
    SPECIFIERS ARIA_ANON(PROP_NAME) &operator=(const TUVW (&args)[n]) {                                                \
      cuda::std::apply([&](const auto &...propArgsTuple) {                                                             \
        Set(object, property::detail::ConstructWithArray<std::decay_t<Type>>(args, std::make_index_sequence<n>{}),     \
            propArgsTuple...);                                                                                         \
      }, propArgs);                                                                                                    \
      return *this;                                                                                                    \
    }                                                                                                                  \
                                                                                                                       \
  private:                                                                                                             \
    class ARIA_CONCAT(DummyClassForSubPropBegin, PROP_NAME) {}

// clang-format off
#define __ARIA_SUB_PROP_END                                                                                            \
  };                                                                                                                   \
                                                                                                                       \
private:                                                                                                               \
  class ARIA_CONCAT(DummyClassForSubPropEnd, __COUNTER__) {}

#define __ARIA_SUB_PROP(SPECIFIERS, TYPE, PROP_NAME)                                                                   \
  __ARIA_SUB_PROP_BEGIN(SPECIFIERS, TYPE, PROP_NAME);                                                                  \
  __ARIA_SUB_PROP_END
// clang-format on

//
//
//
//
//
#define __ARIA_REF_PROP(ACCESS, SPECIFIERS, PROP_NAME, REFERENCE)                                                      \
                                                                                                                       \
  ACCESS:                                                                                                              \
  /* MUST be `const auto &` and `auto &` here instead of `decltype(auto)`. */                                          \
  /* See C++ value categories. */                                                                                      \
  [[nodiscard]] SPECIFIERS const auto &PROP_NAME() const {                                                             \
    return REFERENCE;                                                                                                  \
  }                                                                                                                    \
  [[nodiscard]] SPECIFIERS auto &PROP_NAME() {                                                                         \
    return REFERENCE;                                                                                                  \
  }                                                                                                                    \
                                                                                                                       \
private:                                                                                                               \
  class ARIA_CONCAT(DummyClassForRefProp, PROP_NAME) {}

//
//
//
//
//
#define __ARIA_PROP_FUNC(ACCESS, SPECIFIERS, DOT_OR_ARROW, FUNC_NAME)                                                  \
  /* Supporting of member functions for properties is non-trivial because */                                           \
  /* there are actually 4 kinds of member functions: */                                                                \
  /*   0. Return something, non-const, */                                                                              \
  /*   1. Void, non-const, */                                                                                          \
  /*   2. Return something, const, */                                                                                  \
  /*   3. Void, const. */                                                                                              \
                                                                                                                       \
  /* What we should do is to provide a function wrapper, */                                                            \
  /* which is called by (const or non-const) property instances, and */                                                \
  /* will call the actual underlying member function. */                                                               \
                                                                                                                       \
  /*! What is difficult is that, there are 4 kinds of member functions. */                                             \
  /*! So, our function wrapper should exactly match their types. */                                                    \
  /*! One way to solve this problem is to provide 4 kinds of */                                                        \
  /*! function wrappers for each kind of member functions. */                                                          \
  /*! But, how to call the proper wrapper for any given function? */                                                   \
  /*! Use concepts, or the so-called SFINAE techniques. */                                                             \
                                                                                                                       \
  /* TODO: A lot of supporting functions are added here to bypass the NVCC bug. */                                     \
private:                                                                                                               \
  /* clang-format off */                                                                                             \
  /* 0. Return something, non-const. */                                                                                \
  template <typename T>                                                                                                \
  [[nodiscard]] static consteval bool ARIA_CONCAT(IsPropFuncCallable0Args0, FUNC_NAME)() {                             \
    return (requires(T &v) { { v DOT_OR_ARROW FUNC_NAME(                                                               \
        )                                                                                                              \
      } -> property::detail::DiffFrom<void>; }); }                                                                     \
                                                                                                                       \
  template <typename T, typename T0>                                                                                   \
  [[nodiscard]] static consteval bool ARIA_CONCAT(IsPropFuncCallable0Args1, FUNC_NAME)() {                             \
    return (requires(T &v, T0 &&t0) { { v DOT_OR_ARROW FUNC_NAME(                                                      \
        std::forward<T0>(t0))                                                                                          \
      } -> property::detail::DiffFrom<void>; }); }                                                                     \
                                                                                                                       \
  template <typename T, typename T0, typename T1>                                                                      \
  [[nodiscard]] static consteval bool ARIA_CONCAT(IsPropFuncCallable0Args2, FUNC_NAME)() {                             \
    return (requires(T &v, T0 &&t0, T1 &&t1) { { v DOT_OR_ARROW FUNC_NAME(                                             \
        std::forward<T0>(t0), std::forward<T1>(t1))                                                                    \
      } -> property::detail::DiffFrom<void>; }); }                                                                     \
                                                                                                                       \
  template <typename T, typename T0, typename T1, typename T2>                                                         \
  [[nodiscard]] static consteval bool ARIA_CONCAT(IsPropFuncCallable0Args3, FUNC_NAME)() {                             \
    return (requires(T &v, T0 &&t0, T1 &&t1, T2 &&t2) { { v DOT_OR_ARROW FUNC_NAME(                                    \
        std::forward<T0>(t0), std::forward<T1>(t1), std::forward<T2>(t2))                                              \
      } -> property::detail::DiffFrom<void>; }); }                                                                     \
                                                                                                                       \
  template <typename T, typename T0, typename T1, typename T2, typename T3>                                            \
  [[nodiscard]] static consteval bool ARIA_CONCAT(IsPropFuncCallable0Args4, FUNC_NAME)() {                             \
    return (requires(T &v, T0 &&t0, T1 &&t1, T2 &&t2, T3 &&t3) { { v DOT_OR_ARROW FUNC_NAME(                           \
        std::forward<T0>(t0), std::forward<T1>(t1), std::forward<T2>(t2), std::forward<T3>(t3))                        \
      } -> property::detail::DiffFrom<void>; }); }                                                                     \
                                                                                                                       \
  template <typename T, typename T0, typename T1, typename T2, typename T3, typename T4>                               \
  [[nodiscard]] static consteval bool ARIA_CONCAT(IsPropFuncCallable0Args5, FUNC_NAME)() {                             \
    return (requires(T &v, T0 &&t0, T1 &&t1, T2 &&t2, T3 &&t3, T4 &&t4) { { v DOT_OR_ARROW FUNC_NAME(                  \
        std::forward<T0>(t0), std::forward<T1>(t1), std::forward<T2>(t2), std::forward<T3>(t3), std::forward<T4>(t4))  \
      } -> property::detail::DiffFrom<void>; }); }                                                                     \
                                                                                                                       \
  /* 1. Void, non-const. */                                                                                            \
  template <typename T>                                                                                                \
  [[nodiscard]] static consteval bool ARIA_CONCAT(IsPropFuncCallable1Args0, FUNC_NAME)() {                             \
    return (requires(T &v) { { v DOT_OR_ARROW FUNC_NAME(                                                               \
        )                                                                                                              \
      } -> std::same_as<void>; }); }                                                                                   \
                                                                                                                       \
  template <typename T, typename T0>                                                                                   \
  [[nodiscard]] static consteval bool ARIA_CONCAT(IsPropFuncCallable1Args1, FUNC_NAME)() {                             \
    return (requires(T &v, T0 &&t0) { { v DOT_OR_ARROW FUNC_NAME(                                                      \
        std::forward<T0>(t0))                                                                                          \
      } -> std::same_as<void>; }); }                                                                                   \
                                                                                                                       \
  template <typename T, typename T0, typename T1>                                                                      \
  [[nodiscard]] static consteval bool ARIA_CONCAT(IsPropFuncCallable1Args2, FUNC_NAME)() {                             \
    return (requires(T &v, T0 &&t0, T1 &&t1) { { v DOT_OR_ARROW FUNC_NAME(                                             \
        std::forward<T0>(t0), std::forward<T1>(t1))                                                                    \
      } -> std::same_as<void>; }); }                                                                                   \
                                                                                                                       \
  template <typename T, typename T0, typename T1, typename T2>                                                         \
  [[nodiscard]] static consteval bool ARIA_CONCAT(IsPropFuncCallable1Args3, FUNC_NAME)() {                             \
    return (requires(T &v, T0 &&t0, T1 &&t1, T2 &&t2) { { v DOT_OR_ARROW FUNC_NAME(                                    \
        std::forward<T0>(t0), std::forward<T1>(t1), std::forward<T2>(t2))                                              \
      } -> std::same_as<void>; }); }                                                                                   \
                                                                                                                       \
  template <typename T, typename T0, typename T1, typename T2, typename T3>                                            \
  [[nodiscard]] static consteval bool ARIA_CONCAT(IsPropFuncCallable1Args4, FUNC_NAME)() {                             \
    return (requires(T &v, T0 &&t0, T1 &&t1, T2 &&t2, T3 &&t3) { { v DOT_OR_ARROW FUNC_NAME(                           \
        std::forward<T0>(t0), std::forward<T1>(t1), std::forward<T2>(t2), std::forward<T3>(t3))                        \
      } -> std::same_as<void>; }); }                                                                                   \
                                                                                                                       \
  template <typename T, typename T0, typename T1, typename T2, typename T3, typename T4>                               \
  [[nodiscard]] static consteval bool ARIA_CONCAT(IsPropFuncCallable1Args5, FUNC_NAME)() {                             \
    return (requires(T &v, T0 &&t0, T1 &&t1, T2 &&t2, T3 &&t3, T4 &&t4) { { v DOT_OR_ARROW FUNC_NAME(                  \
        std::forward<T0>(t0), std::forward<T1>(t1), std::forward<T2>(t2), std::forward<T3>(t3), std::forward<T4>(t4))  \
      } -> std::same_as<void>; }); }                                                                                   \
                                                                                                                       \
  /* 2. Return something, const. */                                                                                    \
  template <typename T>                                                                                                \
  [[nodiscard]] static consteval bool ARIA_CONCAT(IsPropFuncCallable2Args0, FUNC_NAME)() {                             \
    return (requires(const T &v) { { v DOT_OR_ARROW FUNC_NAME(                                                         \
        )                                                                                                              \
      } -> property::detail::DiffFrom<void>; }); }                                                                     \
                                                                                                                       \
  template <typename T, typename T0>                                                                                   \
  [[nodiscard]] static consteval bool ARIA_CONCAT(IsPropFuncCallable2Args1, FUNC_NAME)() {                             \
    return (requires(const T &v, T0 &&t0) { { v DOT_OR_ARROW FUNC_NAME(                                                \
        std::forward<T0>(t0))                                                                                          \
      } -> property::detail::DiffFrom<void>; }); }                                                                     \
                                                                                                                       \
  template <typename T, typename T0, typename T1>                                                                      \
  [[nodiscard]] static consteval bool ARIA_CONCAT(IsPropFuncCallable2Args2, FUNC_NAME)() {                             \
    return (requires(const T &v, T0 &&t0, T1 &&t1) { { v DOT_OR_ARROW FUNC_NAME(                                       \
        std::forward<T0>(t0), std::forward<T1>(t1))                                                                    \
      } -> property::detail::DiffFrom<void>; }); }                                                                     \
                                                                                                                       \
  template <typename T, typename T0, typename T1, typename T2>                                                         \
  [[nodiscard]] static consteval bool ARIA_CONCAT(IsPropFuncCallable2Args3, FUNC_NAME)() {                             \
    return (requires(const T &v, T0 &&t0, T1 &&t1, T2 &&t2) { { v DOT_OR_ARROW FUNC_NAME(                              \
        std::forward<T0>(t0), std::forward<T1>(t1), std::forward<T2>(t2))                                              \
      } -> property::detail::DiffFrom<void>; }); }                                                                     \
                                                                                                                       \
  template <typename T, typename T0, typename T1, typename T2, typename T3>                                            \
  [[nodiscard]] static consteval bool ARIA_CONCAT(IsPropFuncCallable2Args4, FUNC_NAME)() {                             \
    return (requires(const T &v, T0 &&t0, T1 &&t1, T2 &&t2, T3 &&t3) { { v DOT_OR_ARROW FUNC_NAME(                     \
        std::forward<T0>(t0), std::forward<T1>(t1), std::forward<T2>(t2), std::forward<T3>(t3))                        \
      } -> property::detail::DiffFrom<void>; }); }                                                                     \
                                                                                                                       \
  template <typename T, typename T0, typename T1, typename T2, typename T3, typename T4>                               \
  [[nodiscard]] static consteval bool ARIA_CONCAT(IsPropFuncCallable2Args5, FUNC_NAME)() {                             \
    return (requires(const T &v, T0 &&t0, T1 &&t1, T2 &&t2, T3 &&t3, T4 &&t4) { { v DOT_OR_ARROW FUNC_NAME(            \
        std::forward<T0>(t0), std::forward<T1>(t1), std::forward<T2>(t2), std::forward<T3>(t3), std::forward<T4>(t4))  \
      } -> property::detail::DiffFrom<void>; }); }                                                                     \
                                                                                                                       \
  /* 3. Void, const. */                                                                                                \
  template <typename T>                                                                                                \
  [[nodiscard]] static consteval bool ARIA_CONCAT(IsPropFuncCallable3Args0, FUNC_NAME)() {                             \
    return (requires(const T &v) { { v DOT_OR_ARROW FUNC_NAME(                                                         \
        )                                                                                                              \
      } -> std::same_as<void>; }); }                                                                                   \
                                                                                                                       \
  template <typename T, typename T0>                                                                                   \
  [[nodiscard]] static consteval bool ARIA_CONCAT(IsPropFuncCallable3Args1, FUNC_NAME)() {                             \
    return (requires(const T &v, T0 &&t0) { { v DOT_OR_ARROW FUNC_NAME(                                                \
        std::forward<T0>(t0))                                                                                          \
      } -> std::same_as<void>; }); }                                                                                   \
                                                                                                                       \
  template <typename T, typename T0, typename T1>                                                                      \
  [[nodiscard]] static consteval bool ARIA_CONCAT(IsPropFuncCallable3Args2, FUNC_NAME)() {                             \
    return (requires(const T &v, T0 &&t0, T1 &&t1) { { v DOT_OR_ARROW FUNC_NAME(                                       \
        std::forward<T0>(t0), std::forward<T1>(t1))                                                                    \
      } -> std::same_as<void>; }); }                                                                                   \
                                                                                                                       \
  template <typename T, typename T0, typename T1, typename T2>                                                         \
  [[nodiscard]] static consteval bool ARIA_CONCAT(IsPropFuncCallable3Args3, FUNC_NAME)() {                             \
    return (requires(const T &v, T0 &&t0, T1 &&t1, T2 &&t2) { { v DOT_OR_ARROW FUNC_NAME(                              \
        std::forward<T0>(t0), std::forward<T1>(t1), std::forward<T2>(t2))                                              \
      } -> std::same_as<void>; }); }                                                                                   \
                                                                                                                       \
  template <typename T, typename T0, typename T1, typename T2, typename T3>                                            \
  [[nodiscard]] static consteval bool ARIA_CONCAT(IsPropFuncCallable3Args4, FUNC_NAME)() {                             \
    return (requires(const T &v, T0 &&t0, T1 &&t1, T2 &&t2, T3 &&t3) { { v DOT_OR_ARROW FUNC_NAME(                     \
        std::forward<T0>(t0), std::forward<T1>(t1), std::forward<T2>(t2), std::forward<T3>(t3))                        \
      } -> std::same_as<void>; }); }                                                                                   \
                                                                                                                       \
  template <typename T, typename T0, typename T1, typename T2, typename T3, typename T4>                               \
  [[nodiscard]] static consteval bool ARIA_CONCAT(IsPropFuncCallable3Args5, FUNC_NAME)() {                             \
    return (requires(const T &v, T0 &&t0, T1 &&t1, T2 &&t2, T3 &&t3, T4 &&t4) { { v DOT_OR_ARROW FUNC_NAME(            \
        std::forward<T0>(t0), std::forward<T1>(t1), std::forward<T2>(t2), std::forward<T3>(t3), std::forward<T4>(t4))  \
      } -> std::same_as<void>; }); } \
  /* clang-format on */                                                                                                \
                                                                                                                       \
  /* 0. Return something, non-const. */                                                                                \
  template <typename T, typename... Ts>                                                                                \
  [[nodiscard]] static consteval bool ARIA_CONCAT(IsPropFuncCallable0, FUNC_NAME)() {                                  \
    /* return (requires(T &v, Ts &&...ts) { */                                                                         \
    /*   { v DOT_OR_ARROW FUNC_NAME(std::forward<Ts>(ts)...) } -> property::detail::DiffFrom<void>; */                 \
    /* }); */                                                                                                          \
    using TArray = MakeTypeArray<Ts...>;                                                                               \
    if constexpr (TArray::size == 0)                                                                                   \
      return ARIA_CONCAT(IsPropFuncCallable0Args0, FUNC_NAME)<T>();                                                    \
    else if constexpr (TArray::size == 1)                                                                              \
      return ARIA_CONCAT(IsPropFuncCallable0Args1, FUNC_NAME)<T, typename TArray::template Get<0>>();                  \
    else if constexpr (TArray::size == 2)                                                                              \
      return ARIA_CONCAT(IsPropFuncCallable0Args2,                                                                     \
                         FUNC_NAME)<T, typename TArray::template Get<0>, typename TArray::template Get<1>>();          \
    else if constexpr (TArray::size == 3)                                                                              \
      return ARIA_CONCAT(IsPropFuncCallable0Args3,                                                                     \
                         FUNC_NAME)<T, typename TArray::template Get<0>, typename TArray::template Get<1>,             \
                                    typename TArray::template Get<2>>();                                               \
    else if constexpr (TArray::size == 4)                                                                              \
      return ARIA_CONCAT(IsPropFuncCallable0Args4,                                                                     \
                         FUNC_NAME)<T, typename TArray::template Get<0>, typename TArray::template Get<1>,             \
                                    typename TArray::template Get<2>, typename TArray::template Get<3>>();             \
    else if constexpr (TArray::size == 5)                                                                              \
      return ARIA_CONCAT(IsPropFuncCallable0Args5,                                                                     \
                         FUNC_NAME)<T, typename TArray::template Get<0>, typename TArray::template Get<1>,             \
                                    typename TArray::template Get<2>, typename TArray::template Get<3>,                \
                                    typename TArray::template Get<4>>();                                               \
    else                                                                                                               \
      ARIA_STATIC_ASSERT_FALSE("Too many arguments passed to the property function, please contact the developers");   \
  }                                                                                                                    \
                                                                                                                       \
  /* 1. Void, non-const. */                                                                                            \
  template <typename T, typename... Ts>                                                                                \
  [[nodiscard]] static consteval bool ARIA_CONCAT(IsPropFuncCallable1, FUNC_NAME)() {                                  \
    /* return (requires(T &v, Ts &&...ts) { */                                                                         \
    /*   { v DOT_OR_ARROW FUNC_NAME(std::forward<Ts>(ts)...) } -> std::same_as<void>; */                               \
    /* }); */                                                                                                          \
    using TArray = MakeTypeArray<Ts...>;                                                                               \
    if constexpr (TArray::size == 0)                                                                                   \
      return ARIA_CONCAT(IsPropFuncCallable1Args0, FUNC_NAME)<T>();                                                    \
    else if constexpr (TArray::size == 1)                                                                              \
      return ARIA_CONCAT(IsPropFuncCallable1Args1, FUNC_NAME)<T, typename TArray::template Get<0>>();                  \
    else if constexpr (TArray::size == 2)                                                                              \
      return ARIA_CONCAT(IsPropFuncCallable1Args2,                                                                     \
                         FUNC_NAME)<T, typename TArray::template Get<0>, typename TArray::template Get<1>>();          \
    else if constexpr (TArray::size == 3)                                                                              \
      return ARIA_CONCAT(IsPropFuncCallable1Args3,                                                                     \
                         FUNC_NAME)<T, typename TArray::template Get<0>, typename TArray::template Get<1>,             \
                                    typename TArray::template Get<2>>();                                               \
    else if constexpr (TArray::size == 4)                                                                              \
      return ARIA_CONCAT(IsPropFuncCallable1Args4,                                                                     \
                         FUNC_NAME)<T, typename TArray::template Get<0>, typename TArray::template Get<1>,             \
                                    typename TArray::template Get<2>, typename TArray::template Get<3>>();             \
    else if constexpr (TArray::size == 5)                                                                              \
      return ARIA_CONCAT(IsPropFuncCallable1Args5,                                                                     \
                         FUNC_NAME)<T, typename TArray::template Get<0>, typename TArray::template Get<1>,             \
                                    typename TArray::template Get<2>, typename TArray::template Get<3>,                \
                                    typename TArray::template Get<4>>();                                               \
    else                                                                                                               \
      ARIA_STATIC_ASSERT_FALSE("Too many arguments passed to the property function, please contact the developers");   \
  }                                                                                                                    \
                                                                                                                       \
  /* 2. Return something, const. */                                                                                    \
  template <typename T, typename... Ts>                                                                                \
  [[nodiscard]] static consteval bool ARIA_CONCAT(IsPropFuncCallable2, FUNC_NAME)() {                                  \
    /* return (requires(const T &v, Ts &&...ts) { */                                                                   \
    /*   { v DOT_OR_ARROW FUNC_NAME(std::forward<Ts>(ts)...) } -> property::detail::DiffFrom<void>; */                 \
    /* }); */                                                                                                          \
    using TArray = MakeTypeArray<Ts...>;                                                                               \
    if constexpr (TArray::size == 0)                                                                                   \
      return ARIA_CONCAT(IsPropFuncCallable2Args0, FUNC_NAME)<T>();                                                    \
    else if constexpr (TArray::size == 1)                                                                              \
      return ARIA_CONCAT(IsPropFuncCallable2Args1, FUNC_NAME)<T, typename TArray::template Get<0>>();                  \
    else if constexpr (TArray::size == 2)                                                                              \
      return ARIA_CONCAT(IsPropFuncCallable2Args2,                                                                     \
                         FUNC_NAME)<T, typename TArray::template Get<0>, typename TArray::template Get<1>>();          \
    else if constexpr (TArray::size == 3)                                                                              \
      return ARIA_CONCAT(IsPropFuncCallable2Args3,                                                                     \
                         FUNC_NAME)<T, typename TArray::template Get<0>, typename TArray::template Get<1>,             \
                                    typename TArray::template Get<2>>();                                               \
    else if constexpr (TArray::size == 4)                                                                              \
      return ARIA_CONCAT(IsPropFuncCallable2Args4,                                                                     \
                         FUNC_NAME)<T, typename TArray::template Get<0>, typename TArray::template Get<1>,             \
                                    typename TArray::template Get<2>, typename TArray::template Get<3>>();             \
    else if constexpr (TArray::size == 5)                                                                              \
      return ARIA_CONCAT(IsPropFuncCallable2Args5,                                                                     \
                         FUNC_NAME)<T, typename TArray::template Get<0>, typename TArray::template Get<1>,             \
                                    typename TArray::template Get<2>, typename TArray::template Get<3>,                \
                                    typename TArray::template Get<4>>();                                               \
    else                                                                                                               \
      ARIA_STATIC_ASSERT_FALSE("Too many arguments passed to the property function, please contact the developers");   \
  }                                                                                                                    \
                                                                                                                       \
  /* 3. Void, const. */                                                                                                \
  template <typename T, typename... Ts>                                                                                \
  [[nodiscard]] static consteval bool ARIA_CONCAT(IsPropFuncCallable3, FUNC_NAME)() {                                  \
    /* return (requires(const T &v, Ts &&...ts) { */                                                                   \
    /*   { v DOT_OR_ARROW FUNC_NAME(std::forward<Ts>(ts)...) } -> std::same_as<void>; */                               \
    /* }); */                                                                                                          \
    using TArray = MakeTypeArray<Ts...>;                                                                               \
    if constexpr (TArray::size == 0)                                                                                   \
      return ARIA_CONCAT(IsPropFuncCallable3Args0, FUNC_NAME)<T>();                                                    \
    else if constexpr (TArray::size == 1)                                                                              \
      return ARIA_CONCAT(IsPropFuncCallable3Args1, FUNC_NAME)<T, typename TArray::template Get<0>>();                  \
    else if constexpr (TArray::size == 2)                                                                              \
      return ARIA_CONCAT(IsPropFuncCallable3Args2,                                                                     \
                         FUNC_NAME)<T, typename TArray::template Get<0>, typename TArray::template Get<1>>();          \
    else if constexpr (TArray::size == 3)                                                                              \
      return ARIA_CONCAT(IsPropFuncCallable3Args3,                                                                     \
                         FUNC_NAME)<T, typename TArray::template Get<0>, typename TArray::template Get<1>,             \
                                    typename TArray::template Get<2>>();                                               \
    else if constexpr (TArray::size == 4)                                                                              \
      return ARIA_CONCAT(IsPropFuncCallable3Args4,                                                                     \
                         FUNC_NAME)<T, typename TArray::template Get<0>, typename TArray::template Get<1>,             \
                                    typename TArray::template Get<2>, typename TArray::template Get<3>>();             \
    else if constexpr (TArray::size == 5)                                                                              \
      return ARIA_CONCAT(IsPropFuncCallable3Args5,                                                                     \
                         FUNC_NAME)<T, typename TArray::template Get<0>, typename TArray::template Get<1>,             \
                                    typename TArray::template Get<2>, typename TArray::template Get<3>,                \
                                    typename TArray::template Get<4>>();                                               \
    else                                                                                                               \
      ARIA_STATIC_ASSERT_FALSE("Too many arguments passed to the property function, please contact the developers");   \
  }                                                                                                                    \
                                                                                                                       \
  ACCESS:                                                                                                              \
  /* 0. Return something, non-const. */                                                                                \
  /* This wrapper requires the underlying functions to be called only with non-const instances. */                     \
  /* And should return something. */                                                                                   \
  template <typename... Ts>                                                                                            \
    requires(!ARIA_CONCAT(IsPropFuncCallable1, FUNC_NAME) < Type,                                                      \
             Ts... > () && !ARIA_CONCAT(IsPropFuncCallable2, FUNC_NAME) < Type,                                        \
             Ts... > () && !ARIA_CONCAT(IsPropFuncCallable3, FUNC_NAME) < Type,                                        \
             Ts... > () && ARIA_CONCAT(IsPropFuncCallable0, FUNC_NAME) < Type, Ts... > ())                             \
  [[nodiscard]] SPECIFIERS decltype(auto) FUNC_NAME(Ts &&...ts) {                                                      \
    decltype(auto) v = value();                                                                                        \
    using TGet = decltype(v);                                                                                          \
                                                                                                                       \
    using TRes = decltype(v DOT_OR_ARROW FUNC_NAME(std::forward<Ts>(ts)...));                                          \
                                                                                                                       \
    if constexpr (property::detail::SettableProxyType<TRes>) {                                                         \
      /* This requirement is necessary to avoid settable proxies pointing to temporary variables. */                   \
      ARIA_STATIC_ASSERT_FALSE("Return type of the property function should not be a settable proxy type");            \
    } else {                                                                                                           \
      if constexpr (property::detail::isReferenceOrPointer<TRes>) {                                                    \
        ARIA_STATIC_ASSERT_FALSE("Return type of the property function should not be a reference or a pointer");       \
      } else {                                                                                                         \
        auto resAuto = Auto(v DOT_OR_ARROW FUNC_NAME(std::forward<Ts>(ts)...));                                        \
        *this = v; /* Because this is a wrapper for non-const functions. */                                            \
        return resAuto;                                                                                                \
      }                                                                                                                \
    }                                                                                                                  \
  }                                                                                                                    \
                                                                                                                       \
  /* 1. Void, non-const. */                                                                                            \
  template <typename... Ts>                                                                                            \
    requires(!ARIA_CONCAT(IsPropFuncCallable0, FUNC_NAME) < Type,                                                      \
             Ts... > () && !ARIA_CONCAT(IsPropFuncCallable2, FUNC_NAME) < Type,                                        \
             Ts... > () && !ARIA_CONCAT(IsPropFuncCallable3, FUNC_NAME) < Type,                                        \
             Ts... > () && ARIA_CONCAT(IsPropFuncCallable1, FUNC_NAME) < Type, Ts... > ())                             \
  SPECIFIERS void FUNC_NAME(Ts &&...ts) {                                                                              \
    decltype(auto) v = value();                                                                                        \
                                                                                                                       \
    v DOT_OR_ARROW FUNC_NAME(std::forward<Ts>(ts)...);                                                                 \
    *this = v; /* Because this is a wrapper for non-const functions. */                                                \
  }                                                                                                                    \
                                                                                                                       \
  /* 2. Return something, const. */                                                                                    \
  template <typename... Ts>                                                                                            \
    requires(!ARIA_CONCAT(IsPropFuncCallable3, FUNC_NAME) < Type,                                                      \
             Ts... > () && ARIA_CONCAT(IsPropFuncCallable2, FUNC_NAME) < Type, Ts... > ())                             \
  [[nodiscard]] SPECIFIERS decltype(auto) FUNC_NAME(Ts &&...ts) const {                                                \
    decltype(auto) v = value();                                                                                        \
    using TGet = decltype(v);                                                                                          \
                                                                                                                       \
    using TRes = decltype(v DOT_OR_ARROW FUNC_NAME(std::forward<Ts>(ts)...));                                          \
                                                                                                                       \
    if constexpr (property::detail::SettableProxyType<TRes>) {                                                         \
      /* This requirement is necessary to avoid settable proxies pointing to temporary variables. */                   \
      ARIA_STATIC_ASSERT_FALSE("Return type of the property function should not be a settable proxy type");            \
    } else {                                                                                                           \
      if constexpr (property::detail::isReferenceOrPointer<TRes>) {                                                    \
        ARIA_STATIC_ASSERT_FALSE("Return type of the property function should not be a reference or a pointer");       \
      } else {                                                                                                         \
        return Auto(v DOT_OR_ARROW FUNC_NAME(std::forward<Ts>(ts)...));                                                \
      }                                                                                                                \
    }                                                                                                                  \
  }                                                                                                                    \
                                                                                                                       \
  /* 3. Void, const. */                                                                                                \
  template <typename... Ts>                                                                                            \
    requires(!ARIA_CONCAT(IsPropFuncCallable2, FUNC_NAME) < Type,                                                      \
             Ts... > () && ARIA_CONCAT(IsPropFuncCallable3, FUNC_NAME) < Type, Ts... > ())                             \
  SPECIFIERS void FUNC_NAME(Ts &&...ts) const {                                                                        \
    value() DOT_OR_ARROW FUNC_NAME(std::forward<Ts>(ts)...);                                                           \
  }                                                                                                                    \
                                                                                                                       \
private:                                                                                                               \
  class ARIA_CONCAT(DummyClassForPropFunc, FUNC_NAME) {}

} // namespace ARIA
