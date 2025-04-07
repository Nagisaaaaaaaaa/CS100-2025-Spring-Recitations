#pragma once

/// \file
/// \brief Suppose we want to implement a multi-window game
/// (eg: WindowKill, see https://torcado.itch.io/windowkill),
/// we have to handle these questions:
///   1: How many windows are still exist at this time.
///   2: How to iterate through all the existing windows.
///   3. How to ensure thread safety if we create and destroy windows with multiple threads.
///
/// `Registry` provides an easy way to address these questions.
/// It automatically serializes all instances of its derived class, and
/// is optionally thread-safe or thread-unsafe.

//
//
//
//
//
// #include "ARIA/detail/BrokenMutex.h"
#include "./detail/BrokenMutex.h"

#include <mutex>

namespace ARIA {

/// \brief A Registry is a CRTP-based class which
/// automatically serializes all instances of its derived class.
///
/// For example, users will be able to
/// know the number of existing instances of a class with `size`, and
/// visit all existing instances with `range` and `crange`.
///
/// \warning `Registry` is implemented with policy-based design.
/// Whether the following listed functions are thread-safe and the overall performance are
/// based on the template parameter `TMutex`:
///   1. Default constructor,
///   2. Copy and move constructor,
///   3. Copy and move operator,
///   4. swap.
/// By default, `TMutex` is set to `BrokenMutex`, means these functions are all non thread-safe.
/// When `TMutex` is set to a "good" mutex, these functions are thread-safe.
///
/// However, `TMutex` requires that `lock()` and `unlock()` of the given mutex is `noexcept`,
/// see the comments below for the reasons.
/// That means, some implementations of the `std::mutex` may not work (eg: MSVC).
/// You can use the ARIA builtin locks (eg: `SpinLock`) or your own locks.
///
/// All other methods of `Registry` are always not thread-safe themselves.
/// To use these methods with multiple threads, add a external mutex.
///
/// \warning Registry is implemented with singleton, that is,
/// there are many globally `static` variables.
/// So, make sure that all registry-related codes are compiled with one translation unit.
/// See https://stackoverflow.com/questions/1106149/what-is-a-translation-unit-in-c.
/// Or, there will be weird undefined behaviors.
///
/// This is also why all the interfaces are `protected` instead of `public`.
/// We don't want interfaces to be accidentally called by external codes.
///
/// \example ```cpp
/// struct A : public Registry<A> {
///   size_t value{};
///
///   using Base = Registry<A>;
///   using Base::size;
///   using Base::range;
///   using Base::crange;
/// };
///
/// struct B : public Registry<B, SpinLock> {
///   size_t value{};
///
///   using Base = Registry<A, SpinLock>;
///   using Base::size;
///   using Base::range;
///   using Base::crange;
/// };
///
/// {
///   A a0;
///   EXPECT_EQ(A::size(), 1);
///   A a1;
///   EXPECT_EQ(A::size(), 2);
/// }
/// EXPECT_EQ(A::size(), 0);
///
/// {
///   A a0{.value = 1};
///   A a1{.value = 2};
///   A a2{.value = 3};
///
///   size_t totalValue = 0;
///   for (const auto& a : A::range()) {
///     totalValue += a.value;
///   }
///
///   EXPECT_EQ(totalValue, 6);
/// }
/// ```
///
/// \details Registry is implemented with a doubly linked list, see the comments.
/// The idea comes from Fedor G. Pikus, Hands-On Design Patterns with C++.
template <typename TDerived, typename TMutex = BrokenMutex>
class Registry {
protected:
  /// \brief Get the number of existing instances.
  ///
  /// \example ```cpp
  /// std::cout << A::size() << std::endl;
  /// ```
  [[nodiscard]] static size_t size() noexcept { return size_; }

private:
  // Iterators and ranges fwd.
  template <typename TDerivedMaybeConst>
  class Iterator;
  template <typename TItBegin, typename TItEnd>
  class Range;

protected:
  /// \brief Get the non-const begin iterator of the existing instances.
  ///
  /// \example ```cpp
  /// size_t totalValue = 0;
  /// for (auto it = A::begin(); it != A::end(); ++it) {
  ///   totalValue += it->value;
  /// }
  /// ```
  [[nodiscard]] static Iterator<TDerived> begin() noexcept { return Iterator<TDerived>{head_}; }

  /// \brief Get the non-const end iterator of the existing instances.
  [[nodiscard]] static Iterator<TDerived> end() noexcept { return Iterator<TDerived>{nullptr}; }

  /// \brief Get the const begin iterator of the existing instances.
  ///
  /// \example ```cpp
  /// size_t totalValue = 0;
  /// for (auto it = A::cbegin(); it != A::cend(); ++it) {
  ///   totalValue += it->value;
  /// }
  /// ```
  [[nodiscard]] static Iterator<const TDerived> cbegin() noexcept { return Iterator<const TDerived>{head_}; }

  /// \brief Get the const end iterator of the existing instances.
  [[nodiscard]] static Iterator<const TDerived> cend() noexcept { return Iterator<const TDerived>{nullptr}; }

  /// \brief Get the non-const range of the existing instances.
  ///
  /// \example ```cpp
  /// size_t totalValue = 0;
  /// for (auto &a : A::range()) {
  ///   totalValue += a.value;
  /// }
  ///
  /// size_t totalValue = 0;
  /// for (auto &a : A::range() | std::views::take(5) | std::views::reverse) {
  ///   totalValue += a.value;
  /// }
  /// ```
  [[nodiscard]] static Range<Iterator<TDerived>, Iterator<TDerived>> range() noexcept { return {begin(), end()}; }

  /// \brief Get the const range of the existing instances.
  ///
  /// \example ```cpp
  /// size_t totalValue = 0;
  /// for (auto &a : A::crange()) {
  ///   totalValue += a.value;
  /// }
  ///
  /// size_t totalValue = 0;
  /// for (auto &a : A::crange() | std::views::take(5) | std::views::reverse) {
  ///   totalValue += a.value;
  /// }
  /// ```
  [[nodiscard]] static Range<Iterator<const TDerived>, Iterator<const TDerived>> crange() noexcept {
    return {cbegin(), cend()};
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
private:
  // Doubly linked list and CRTP related variables and methods.
  static constinit inline size_t size_ = 0;

  static constinit inline TDerived *head_{};
  static constinit inline TDerived *tail_{};

  //! We already have a mutex here, `mutex_`, but why we cannot let users use this mutex to
  //! access `size()` and other methods with multiple threads?
  //! For example, add a `protected` method `mutex()` and return the reference to `mutex_`.
  //!
  //! Because this mutex is always used in the 6 functions (constructor + destructor + 4).
  //! If some thread manually acquires this mutex, and calls `swap`,
  //! then there will be a dead lock here.
  //! So, users should use another mutex.
  static constinit inline TMutex mutex_{};
  static_assert(noexcept(mutex_.lock()) && noexcept(mutex_.unlock()),
                "Methods `lock` and `unlock` of the registry mutex have to be `noexcept`, "
                "to make it able to implement a `noexcept swap`. "
                "See https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom.");

  TDerived *prev_{};
  TDerived *next_{};

  friend TDerived;

  [[nodiscard]] static TDerived *derivedP(Registry *ptr) noexcept { return static_cast<TDerived *>(ptr); }

  [[nodiscard]] static const TDerived *derivedP(const Registry *ptr) noexcept {
    return static_cast<const TDerived *>(ptr);
  }

  [[nodiscard]] TDerived *derivedP() noexcept { return derivedP(this); }

  [[nodiscard]] const TDerived *derivedP() const noexcept { return derivedP(this); }

  //
  //
  //
  //
  //
protected:
  // The default constructor just push back the new node to the end of the doubly linked list.
  // The destructor just remove the new node from the list.
  // The copy constructor just call the default constructor, and do nothing else.
  //
  //! The move constructor, copy operator, and move operator are implemented with the copy-and-swap idiom.
  //! See https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom for more details.
  //
  //! The only difference is that, EVERYTHING is `noexcept` in our case.
  //! It is because we have required `lock` and `unlock` of the registry mutex to be `noexcept`.
  //! This requirement is NECESSARY and ESSENTIAL.
  //! Otherwise, NOTHING is `noexcept`.
  //
  // You may argue that lock acquirement and list operations are redundantly performed.
  // Yes, for example, the move constructor requires the lock for 2 times, and
  // calls 1 constructor and 1 destructor, that's redundant.
  //! But, using copy-and-swap is the only way to implement it safely with few codes, QAQ...
  Registry() noexcept {
    std::lock_guard guard{mutex_};

    ++size_;

    if (tail_) { // If list non-empty.
      tail_->next_ = derivedP();
      prev_ = tail_;
      tail_ = derivedP();
    } else { // If list empty.
      head_ = derivedP();
      tail_ = derivedP();
    }
  }

  Registry(const Registry &) noexcept : Registry() {}

  friend void swap(Registry &lhs, Registry &rhs) noexcept {
    std::lock_guard guard{mutex_};

    using std::swap;

    // Handle self-swap.
    if (&lhs == &rhs)
      return;

    // Update the next pointers.
    if (lhs.next_)
      lhs.next_->prev_ = derivedP(&rhs);
    if (rhs.next_)
      rhs.next_->prev_ = derivedP(&lhs);

    // Update the prev pointers.
    if (lhs.prev_)
      lhs.prev_->next_ = derivedP(&rhs);
    if (rhs.prev_)
      rhs.prev_->next_ = derivedP(&lhs);

    // Swap the prev and next pointers themselves.
    swap(lhs.next_, rhs.next_);
    swap(lhs.prev_, rhs.prev_);

    // Now handle the special cases where head or tail needs to be updated.
    if (head_ == &lhs)
      head_ = derivedP(&rhs);
    else if (head_ == &rhs)
      head_ = derivedP(&lhs);

    if (tail_ == &lhs)
      tail_ = derivedP(&rhs);
    else if (tail_ == &rhs)
      tail_ = derivedP(&lhs);
  }

  Registry(Registry &&other) noexcept : Registry() { swap(*this, other); }

  Registry &operator=(Registry other) noexcept {
    swap(*this, other);
    return *this;
  }

  virtual ~Registry() noexcept {
    std::lock_guard guard{mutex_};

    //! WARNING, we don't need to check whether `prev_` and `next_` are both `nullptr` because
    //! this will NEVER happen since we implement move with swap.
    //! For example, the default constructor is always called by the move constructor.
    //! `++size` is performed there, and `--size` is performed here, by the destructor.
    //
    //! So, every nodes are well contained in the linked list,
    //! when they are constructed, and
    //! until they are destructed.
    // if (!prev_ && !next_) // Never call this line.
    //   return;             // Never call this line.

    --size_;

    if (prev_) // If this node is not head.
      prev_->next_ = next_;
    else // If this node is head.
      head_ = next_;

    if (next_) // If this node is not tail.
      next_->prev_ = prev_;
    else // If this node is tail.
      tail_ = prev_;
  }

  //
  //
  //
  //
  //
private:
  // Iterators implementation.
  template <typename TDerivedMaybeConst>
  class Iterator {
  public:
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = TDerivedMaybeConst;
    using pointer = TDerivedMaybeConst *;
    using reference = TDerivedMaybeConst &;

  public:
    //! The ranges library requires that iterators should be default constructable,
    //! so iterators are constructed to `end` by default.
    Iterator() noexcept = default;

    explicit Iterator(TDerivedMaybeConst *ptr) noexcept : ptr_(ptr) {}

    ARIA_COPY_MOVE_ABILITY(Iterator, default, default);

  public:
    reference operator*() const { return *ptr_; }

    pointer operator->() noexcept { return ptr_; }

    // ++it
    Iterator &operator++() {
      ptr_ = ptr_->next_;
      return *this;
    }

    // it++
    Iterator operator++(int) {
      Iterator tmp = *this;
      ++(*this);
      return tmp;
    }

    // --it
    Iterator &operator--() {
      ptr_ = ptr_->prev_;
      return *this;
    }

    // it--
    Iterator operator--(int) {
      Iterator tmp = *this;
      --(*this);
      return tmp;
    }

    friend bool operator==(const Iterator &a, const Iterator &b) noexcept { return a.ptr_ == b.ptr_; }

    friend bool operator!=(const Iterator &a, const Iterator &b) noexcept { return a.ptr_ != b.ptr_; }

  private:
    TDerivedMaybeConst *ptr_{}; // Equals to `end` by default.
  };

  static_assert(std::bidirectional_iterator<Iterator<TDerived>> &&
                    std::bidirectional_iterator<Iterator<const TDerived>>,
                "The registry iterators should be at least bidirectional to cooperate with the ranges library");

  // Ranges implementation.
  template <typename TItBegin, typename TItEnd>
  class Range {
  public:
    Range(const TItBegin &begin, const TItEnd &end) : begin_(begin), end_(end) {}

    ARIA_COPY_MOVE_ABILITY(Range, default, default);

  public:
    TItBegin begin() const { return begin_; }

    TItEnd end() const { return end_; }

  private:
    TItBegin begin_;
    TItEnd end_;
  };
};

} // namespace ARIA
