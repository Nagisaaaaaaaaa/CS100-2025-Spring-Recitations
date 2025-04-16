#pragma once

/// \file
/// \brief A property is a member that provides a flexible mechanism to
/// read, write, or compute the value of a private field.
/// Properties can be used as if they're public data members, but
/// they're special methods called "getters" and "setters".
/// This feature enables data to be accessed easily and
/// still helps promote the safety and flexibility of methods.
///
/// Property is a built-in feature of C#, but not C++.
/// ARIA provides an implementation of the C#-like property.
/// Support operators, recursive getters, and recursive setters.
/// Working well with other proxy systems, such as `std::vector<bool>` and `thrust::device_vector`.
/// Only several lines of macros need to be injected into your codes.
///
/// Please read the following examples if you are not familiar with C# property.
/// These examples show what a property is, and why it is powerful.
///
/// \example ```cpp
/// #include "ARIA/Property.h"
///
/// template <typename T>
/// class Vector {
/// public:
///   // Define a property, whose type is `size_t`, name is `size`.
///   // The first `public` means external codes are allowed to get the value.
///   // The second `public` means external codes are allowed to set the value.
///   // The "getter" is defined below with `ARIA_PROP_GETTER(size)()`.
///   // The "setter" is defined below with `ARIA_PROP_SETTER(size)(...)`.
///   // The third parameter is the function specifiers, for example,
///   // `__host__`, `__device__`, or nothing, etc.
///   // Note, whether the "getter" or "setter" is inline depends on its
///   // actual implementation, which is defined with `ARIA_PROP_GETTER` or `ARIA_PROP_SETTER`.
///   // You are allowed to declare the "getter" and "setter" in `.h` files, and
///   // implement them in `.cpp` files, that's fine.
///   // So, `inline` has no effects here.
///   //
///   // Later, we will be able to write something like this:
///   // ```cpp
///   // Vector<int> v;
///   // v.size() = 10;
///   // v.size() *= 2;
///   // std::cout << v.size() << std::endl;
///   // ```
///   ARIA_PROP(public, public, __host__, size_t, size);
///
///   // After defining a property, the accessibility is always turned to private.
///   // So, you should explicitly add `public` here if you want to
///   // define a public function `SomePublicFunction`.
///   void SomePrivateFunction() {}
///
/// public:
///   void SomePublicFunction() {}
///
/// private:
///   std::vector<T> v;
///
///   // It is better to declare "getter" and "setter" as private, to avoid population.
///   // Note, the ACTUAL accessibility of the "getter" and "setter" is
///   // defined with `ARIA_PROP(public, public, ...), both are public,
///   // even though the below two functions are declared as private.
/// private:
///   // The "getter" of property `size`.
///   [[nodiscard]] size_t ARIA_PROP_GETTER(size)() const { return v.size(); }
///
///   // The "setter" of property `size`.
///   void ARIA_PROP_SETTER(size)(const size_t &value) { v.resize(value); }
/// };
///
/// template <typename T>
/// class Vec3 {
/// public:
///   Vec3() = default;
///
///   Vec3(const T &x, const T &y, const T &z) : x_(x), y_(y), z_(z) {}
///
///   // Define a property called `x` based on an existing variable `x_`.
///   // `public` means external codes are allowed to
///   // get and set the variable through `x()`.
///   //
///   // Later, we will be able to write something like this:
///   // ```cpp
///   // Vec3f v;
///   // v.x() = 3;
///   // v.y() = 4;
///   // v.z() = 5;
///   // std::cout << v.x() << std::endl;
///   // std::cout << v.y() << std::endl;
///   // std::cout << v.z() << std::endl;
///   // ```
///   ARIA_REF_PROP(public, __host__, x, x_);
///   ARIA_REF_PROP(public, __host__, y, y_);
///   ARIA_REF_PROP(public, __host__, z, z_);
///
///   // You can even write something like this (Never do that, so weird!).
///   ARIA_REF_PROP(public, __host__, xx, xImpl());
///   ARIA_REF_PROP(public, __host__, yy, yImpl());
///   ARIA_REF_PROP(public, __host__, zz, [this]() -> T & { return this->z_; }());
///
///   // Define a property, whose type is `T`, name is `lengthSqr`.
///   // Note the second parameter is set to `private`,
///   // which means the external codes are not allowed to set the value.
///   // So, we even don't need to implement a "getter" for it.
///   // Function specifications are set to empty instead of __host__.
///   ARIA_PROP(public, private, , T, lengthSqr);
///   ARIA_PROP(public, public, , T, length);
///
///   // Should explicitly add public here.
/// public:
///   T Dot(const Vec3 &rhs) const { return x() * rhs.x() + y() * rhs.y() + z() * rhs.z(); }
///
/// private:
///   T x_{}, y_{}, z_{};
///
///   // Declare as private to avoid population.
/// private:
///   T &xImpl() { return x_; }
///
///   const T &yImpl() const { return y_; }
///
///   T &yImpl() { return y_; }
///
///   // The "getter" of property `lengthSqr`.
///   [[nodiscard]] T ARIA_PROP_GETTER(lengthSqr)() const { return Dot(*this); }
///
///   // Note, we don't need to implement a "setter" for `lengthSqr`.
///
///   // The "getter" of property `length`.
///   [[nodiscard]] T ARIA_PROP_GETTER(length)() const { return std::sqrt(lengthSqr()); }
///
///   // The "setter" of property `length`.
///   void ARIA_PROP_SETTER(length)(const T &value) {
///     auto scaling = value / length();
///     x() *= scaling;
///     y() *= scaling;
///     z() *= scaling;
///   }
/// };
///
/// class Transform {
/// public:
///   // Define a property, whose type is `Vec3<float>`, name is `forward`.
///   // This property has several "sub-properties".
///   // You can define more complex properties
///   // with `ARIA_PROP_BEGIN` and `ARIA_PROP_END`,
///   // instead of using `ARIA_PROP`.
///   //
///   // Use `ARIA_SUB_PROP` to define sub-properties.
///   // In this example, there are 5 sub-properties belong to property `forward`.
///   //
///   // Use `ARIA_PROP_FUNC` to define functions.
///   // Note the third parameter, a "dot".
///   // This means that function `Dot` should be called by `forward().Dot(...)`, not `forward()->Dot(...)`.
///   // For properties whose types are pointers, use `->` instead of `.`.
///   ARIA_PROP_BEGIN(public, public, , Vec3<float>, forward);
///     ARIA_SUB_PROP(, float, x); //! Write `float&` here will raise compile errors.
///     ARIA_SUB_PROP(, float, y);
///     ARIA_SUB_PROP(, float, z);
///     ARIA_SUB_PROP(, float, lengthSqr);
///     ARIA_SUB_PROP(, float, length);
///     ARIA_PROP_FUNC(public, , ., Dot);
///   ARIA_PROP_END;
///
///   // `ARIA_PROP_BEGIN` can also handle l-value references and pointers.
///   // You can create something like a "smart reference" or a "smart pointer" which will
///   // 1. For the getter, behave as if they are normal reference or normal pointer.
///   // 2. For the setter, setter will be automatically called whenever
///   //    setter of sub-properties or non-const property functions are called.
///   //
///   // After writing the following codes, we will be able to use the smart reference or pointer:
///   // ```cpp
///   // Property auto smartRef = transform.forwardByRef();
///   // smartRef.x() = ...; // This will call the setter.
///   // ```
///   ARIA_PROP_BEGIN(public, public, , Vec3<double> &, forwardByRef);
///     ARIA_SUB_PROP(, float &, x); //! Since the parent property returns reference, `float&` is allowed here.
///     ARIA_SUB_PROP(, float &, y);
///     ARIA_SUB_PROP(, float &, z);
///     ARIA_SUB_PROP(, float, lengthSqr);
///     ARIA_SUB_PROP(, float, length);
///     ARIA_PROP_FUNC(public, , ., Dot);
///   ARIA_PROP_END;
///
/// private:
///   Vec3<double> forward_; // Note, double here, but type of property `forward` is declared as `Vec3<float>`.
///
///   // The "getter" of property `forward`.
///   [[nodiscard]] Vec3<float> ARIA_PROP_GETTER(forward)() const {
///     return {static_cast<float>(forward_.x()), static_cast<float>(forward_.y()), static_cast<float>(forward_.z())};
///   }
///
///   // The "setter" of property `forward`.
///   void ARIA_PROP_SETTER(forward)(const Vec3<float> &value) {
///     forward_.x() = value.x();
///     forward_.y() = value.y();
///     forward_.z() = value.z();
///   }
///
///   // The "getter" of property `forwardByRef`, const version.
///   [[nodiscard]] const Vec3<double> &ARIA_PROP_GETTER(forwardByRef)() const { return forward_; }
///
///   // The "getter" of property `forwardByRef`, non const version.
///   [[nodiscard]] Vec3<double> &ARIA_PROP_GETTER(forwardByRef)() { return forward_; }
///
///   // The "setter" of property `forwardByRef`.
///   void ARIA_PROP_SETTER(forwardByRef)(const Vec3<double> &value) { forward_ = value; }
/// };
///
/// class Object {
/// public:
///   // Define a property, whose type is `Transform`, name is `transform`.
///   // This property has several NESTED "sub-properties".
///   // Yuo can define much more complex properties
///   // with `ARIA_SUB_PROP_BEGIN` and `ARIA_SUB_PROP_END`,
///   // instead of using `ARIA_SUB_PROP`.
///   // With all the magic introduced, you can define EVERYTHING.
///   ARIA_PROP_BEGIN(public, public, , Transform, transform);
///     ARIA_SUB_PROP_BEGIN(, Vec3<float>, forward);
///       ARIA_SUB_PROP(, float, x);
///       ARIA_SUB_PROP(, float, y);
///       ARIA_SUB_PROP(, float, z);
///       ARIA_SUB_PROP(, float, lengthSqr);
///       ARIA_SUB_PROP(, float, length);
///     ARIA_SUB_PROP_END;
///   ARIA_PROP_END;
///
///   // ...
/// };
///
/// void TestVector() {
///   Vector<int> v;
///
///   auto echo = [&] { fmt::print("{}\n", size_t(v.size())); };
///
///   echo();
///
///   v.size() = 10;
///   echo();
///
///   v.size() *= 2;
///   echo();
///
///   v.size() /= 2;
///   echo();
///
///   ++v.size();
///   echo();
/// }
///
/// void TestVec3() {
///   using Vec3f = Vec3<float>;
///   Vec3f v;
///
///   auto echo = [&] {
///     fmt::print("{} {} {}    {} {}\n", static_cast<float>(v.x()), static_cast<float>(v.y()),
///     static_cast<float>(v.z()),
///                static_cast<float>(v.length()), static_cast<float>(v.lengthSqr()));
///   };
///
///   echo();
///
///   v.x() = 3;
///   v.y() = 4;
///   v.z() = 5;
///   echo();
///
///   v.length() = 7.071068;
///   echo();
///
///   v.length() *= 2;
///   echo();
///
///   v.x() /= 2;
///   v.y() /= 2;
///   v.z() /= 2;
///   echo();
/// }
///
/// void TestTransform() {
///   Transform t;
///
///   auto echo = [&] {
///     fmt::print("{} {} {}    {} {}\n", static_cast<float>(t.forward().x()), static_cast<float>(t.forward().y()),
///                static_cast<float>(t.forward().z()), static_cast<float>(t.forward().length()),
///                static_cast<float>(t.forward().lengthSqr()));
///   };
///
///   echo();
///
///   t.forward().x() = 3;
///   t.forward().y() = 4;
///   t.forward().z() = 5;
///   echo();
///
///   t.forward().length() = 7.071068;
///   echo();
///
///   t.forward().length() *= 2;
///   echo();
///
///   t.forward() = {3.0F, 4.0F, 5.0F};
///   echo();
/// }
/// ```
///
/// \warning All kinds of proxy systems work awfully with `auto`, including this one.
/// Please read all the comments in `Auto.h` before continue.
///
/// It is always safe to use the ARIA property system, until
/// you accidentally combine your newly added proxy system with the existing ARIA property system.
/// Especially when, for example, operators such as `+` are used between an ARIA property and a newly added proxy.
/// Then, `ARIA::Auto` "MAY" be used in `operator+()` instead of your `YourNamespace::Auto`, dangerous here!
/// I say "MAY" because it depends on the complex ADL rules, so complex...
/// So, you may need to implement your own property system.
///
/// Follow the rules below to implement your own property system:
/// 1. Copy all the codes in `detail/PropertyType.h`, `detail/PropertyImpl.h`, and `Property.h` into your project.
/// 2. Change the namespace from `ARIA` to `YourNamespace`, in order to prevent ADL from finding the wrong functions.
/// 3. Modify the implementation of `isProxyType` and `isSettableProxyType`, to similar to your own `Auto`.
///
/// Now, you are all done!
///
/// \note The above example only shows the most primary usages of the ARIA property system.
/// Actually, it's much more powerful than you imagine.
/// Here lists the advanced features:
/// 1. Properties can have any type or number of parameters.
///    For example, you can define getters and setters with parameters, like
///    `ARIA_PROP_GETTER(prop)(int arg0, float arg1)` and
///    `ARIA_PROP_SETTER(prop)(int arg0, float arg1, const T &value)`.
///    Then, call the property with arguments, like `cls.prop(arg0, arg1)`.
/// 2. Overloading is supported.
///    Simply add more getters and setters with the same name.
/// 3. Property arguments can be specified later, just like the so-called "accessors".
///    It's OK to specify the arguments at the first time, like `cls.prop(arg0, arg1)`.
///    You can also type `Property auto p = cls.prop();` and
///    specify the arguments later, like `p.args(arg0, arg1)`.
///    The method `args` is defined for every properties, which
///    can be used to set or reset arguments.
///
/// \see Auto.h

//
//
//
//
//
#include "ARIA/detail/PropertyImpl.h"

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

/// \brief Getters of a property should be defined only with the help of this macro.
///
/// \param propName Name of the property defined by `ARIA_PROP` or `ARIA_PROP_BEGIN`.
#define ARIA_PROP_GETTER(propName) __ARIA_PROP_GETTER(propName)

/// \brief Setters of a property should be defined only with the help of this macro.
///
/// \param propName Name of the property defined by `ARIA_PROP` or `ARIA_PROP_BEGIN`.
#define ARIA_PROP_SETTER(propName) __ARIA_PROP_SETTER(propName)

//
//
//
//
//
/// \brief Define a complex property, whose type is `type`, name is `propName`.
/// `accessGet` and `accessSet` defines the accessibility of this property.
/// `specifiers` are the function specifiers.
/// This macro should be used together with `ARIA_PROP_END`.
/// Use `ARIA_PROP` if you only want to define a simple property with no sub-properties and functions.
/// Within the begin-end region, sub-properties can be defined with `ARIA_SUB_PROP` or `ARIA_SUB_PROP_BEGIN`.
///
/// \param accessGet The accessibility of the property getter by external codes.
/// Should be `public`, `protected`, or `private`.
/// \param accessSet The accessibility of the property setter by external codes.
/// Should be `public`, `protected`, or `private`.
/// \param specifiers Function specifiers such as `__host__`, `__device__`, etc.
/// Note, whether the getter or setter is inline depends on its actual implementation, which
/// is defined with `ARIA_PROP_GETTER` or `ARIA_PROP_SETTER`.
/// So, `inline` has no effects here.
/// \param type Type of the property, can be value or reference.
/// \param propName Name of the property.
#define ARIA_PROP_BEGIN(accessGet, accessSet, specifiers, type, propName)                                              \
  __ARIA_PROP_BEGIN(accessGet, accessSet, specifiers, type, propName)

//
//
//
/// \brief Terminate the definition of a property.
/// This macro should be used together with `ARIA_PROP_BEGIN`.
#define ARIA_PROP_END __ARIA_PROP_END

//
//
//
/// \brief Define a simple property, whose type is `type`, name is `propName`.
/// `accessGet` and `accessSet` defines the accessibility of this property.
/// `specifiers` are the function specifiers.
/// Use `ARIA_PROP_BEGIN` together with `ARIA_PROP_END` if you want to define
/// a complex property with sub-properties and functions.
///
/// \param accessGet The accessibility of the property getter by external codes.
/// Should be `public`, `protected`, or `private`.
/// \param accessSet The accessibility of the property setter by external codes.
/// Should be `public`, `protected`, or `private`.
/// \param specifiers Function specifiers such as `__host__`, `__device__`, etc.
/// Note, whether the getter or setter is inline depends on its actual implementation, which
/// is defined with `ARIA_PROP_GETTER` or `ARIA_PROP_SETTER`.
/// So, `inline` has no effects here.
/// \param type Type of the property, can be value or reference.
/// \param propName Name of the property.
#define ARIA_PROP(accessGet, accessSet, specifiers, type, propName)                                                    \
  __ARIA_PROP(accessGet, accessSet, specifiers, type, propName)

//
//
//
//
//
/// \brief Define a complex sub-property, whose type is `type`, name is `propName`.
/// `specifiers` are the function specifiers.
/// This macro should be used together with `ARIA_SUB_PROP_END`.
/// Use `ARIA_SUB_PROP` if you only want to define a simple sub-property with no sub-sub-properties and functions.
/// Within the begin-end region, sub-sub-properties can be defined with `ARIA_SUB_PROP` or `ARIA_SUB_PROP_BEGIN`.
///
/// \param specifiers Function specifiers such as `__host__`, `__device__`, etc.
/// Note, whether the getter or setter is inline depends on its actual implementation, which
/// is defined with `ARIA_PROP_GETTER` or `ARIA_PROP_SETTER`.
/// So, `inline` has no effects here.
/// \param type Type of the sub-property.
/// \param propName Name of the sub-property.
#define ARIA_SUB_PROP_BEGIN(specifiers, type, propName) __ARIA_SUB_PROP_BEGIN(specifiers, type, propName)

//
//
//
/// \brief Terminate the definition of a sub-property.
/// This macro should be used together with `ARIA_SUB_PROP_BEGIN`.
#define ARIA_SUB_PROP_END __ARIA_SUB_PROP_END

//
//
//
/// \brief Define a simple sub-property, whose type is `type`, name is `propName`.
/// `specifiers` are the function specifiers.
/// Use `ARIA_SUB_PROP_BEGIN` together with `ARIA_SUB_PROP_END` if
/// you want to define a complex sub-property with sub-sub-properties and functions.
///
/// \param specifiers Function specifiers such as `__host__`, `__device__`, etc.
/// Note, whether the getter or setter is inline depends on its actual implementation, which
/// is defined with `ARIA_PROP_GETTER` or `ARIA_PROP_SETTER`.
/// So, `inline` has no effects here.
/// \param type Type of the sub-property.
/// \param propName Name of the sub-property.
#define ARIA_SUB_PROP(specifiers, type, propName) __ARIA_SUB_PROP(specifiers, type, propName)

//
//
//
//
//
/// \brief Define a property called `propName` based on a reference `reference`.
/// `access` defines the accessibility of the property getter and setter.
/// `specifiers` are the function specifiers.
///
/// \param access The accessibility of the property getter and setter by external codes.
/// Should be `public`, `protected`, or `private`.
/// \param specifiers Function specifiers such as `__host__`, `__device__`, etc.
/// Note, whether the getter or setter is inline depends on its actual implementation, which
/// is defined with `ARIA_PROP_GETTER` or `ARIA_PROP_SETTER`.
/// So, `inline` has no effects here.
/// \param propName Name of the property.
/// \param reference The reference which the property is based on.
///
/// \todo Support get + private set
#define ARIA_REF_PROP(access, specifiers, propName, reference) __ARIA_REF_PROP(access, specifiers, propName, reference)

//
//
//
//
//
/// \brief Define a function, whose name is `funcName` for
/// the property defined by `ARIA_PROP_BEGIN` or `ARIA_SUB_PROP_BEGIN`.
/// `access` defines the accessibility for this function.
/// `specifiers` are the function specifiers.
///
/// \param access The accessibility for this function by external codes.
/// Should be `public`, `protected`, or `private`.
/// \param specifiers Function specifiers such as `__host__`, `__device__`, etc.
/// Note, whether the getter or setter is inline depends on its actual implementation, which
/// is defined with `ARIA_PROP_GETTER` or `ARIA_PROP_SETTER`.
/// So, `inline` has no effects here.
/// \param funcName Name of the function.
///
/// \todo To make life easier, MSVC bugs are simply handled by a copy of the whole codes with a little modifications.
#define ARIA_PROP_FUNC(access, specifiers, dotOrArrow, funcName)                                                       \
  __ARIA_PROP_FUNC(access, specifiers, dotOrArrow, funcName)

//
//
//
//
//
/// \brief Use properties like smart references or smart pointers.
///
/// \example ```cpp
/// Property auto trans = object.transform();
/// ```
template <typename T>
concept Property = property::detail::PropertyType<T>;

} // namespace ARIA
