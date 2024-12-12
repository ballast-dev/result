#ifndef RESULT_H
#define RESULT_H

#include <cstdlib> // for std::abort
#include <functional>
#include <type_traits>
#include <utility>

#if __cplusplus >= 202002L
// C++20 and later implementation
#include <memory> // for std::construct_at, std::destroy_at

namespace noexception {

template <typename T, typename E> class Result {
private:
  struct OkType {};
  struct ErrType {};

  union {
    T val;
    E err;
  };
  bool ok;

  Result(T v, OkType) : ok(true) {
    std::construct_at(std::addressof(val), std::move(v));
  }

  Result(E e, ErrType) : ok(false) {
    std::construct_at(std::addressof(err), std::move(e));
  }

public:
  static Result<T, E> Ok(T v) { return Result<T, E>(std::move(v), OkType{}); }
  static Result<T, E> Err(E e) { return Result<T, E>(std::move(e), ErrType{}); }

  bool is_ok() const { return ok; }
  bool is_err() const { return !ok; }

  T &unwrap() {
    if (!ok)
      std::abort();
    return val;
  }

  const T &unwrap() const {
    if (!ok)
      std::abort();
    return val;
  }

  E &unwrap_err() {
    if (ok)
      std::abort();
    return err;
  }

  const E &unwrap_err() const {
    if (ok)
      std::abort();
    return err;
  }

  T unwrap_or(T default_value) const { return ok ? val : default_value; }

  T unwrap_or_else(std::function<T()> f) const { return ok ? val : f(); }

  template <typename U> Result<U, E> map(std::function<U(T)> f) const {
    if (ok)
      return Result<U, E>::Ok(f(val));
    return Result<U, E>::Err(err);
  }

  template <typename F>
  auto map_err(F f) const -> Result<T, decltype(f(std::declval<E>()))> {
    using E2 = decltype(f(std::declval<E>()));
    if (ok)
      return Result<T, E2>::Ok(val);
    return Result<T, E2>::Err(f(err));
  }

  template <typename F>
  auto and_then(F f) const -> decltype(f(std::declval<T>())) {
    if (ok)
      return f(val);
    using R = decltype(f(std::declval<T>()));
    return R::Err(err);
  }

  template <typename F>
  auto or_else(F f) const -> decltype(f(std::declval<E>())) {
    if (!ok)
      return f(err);
    using R = decltype(f(std::declval<E>()));
    return R::Ok(val);
  }

  ~Result() {
    if (ok) {
      std::destroy_at(std::addressof(val));
    } else {
      std::destroy_at(std::addressof(err));
    }
  }

  Result(Result &&other) noexcept(
      std::is_nothrow_move_constructible<T>::value &&
      std::is_nothrow_move_constructible<E>::value)
      : ok(other.ok) {
    if (ok) {
      std::construct_at(std::addressof(val), std::move(other.val));
    } else {
      std::construct_at(std::addressof(err), std::move(other.err));
    }
  }

  Result(const Result &other) : ok(other.ok) {
    if (ok) {
      std::construct_at(std::addressof(val), other.val);
    } else {
      std::construct_at(std::addressof(err), other.err);
    }
  }

  Result &operator=(Result &&other) noexcept(
      std::is_nothrow_move_assignable<T>::value &&
      std::is_nothrow_move_assignable<E>::value) {
    if (this == &other)
      return *this;
    this->~Result();
    ok = other.ok;
    if (ok) {
      std::construct_at(std::addressof(val), std::move(other.val));
    } else {
      std::construct_at(std::addressof(err), std::move(other.err));
    }
    return *this;
  }

  Result &operator=(const Result &other) {
    if (this == &other)
      return *this;
    this->~Result();
    ok = other.ok;
    if (ok) {
      std::construct_at(std::addressof(val), other.val);
    } else {
      std::construct_at(std::addressof(err), other.err);
    }
    return *this;
  }
};

} // namespace noexception

#else
// C++11 implementation
#include <memory> // for allocator, allocator_traits

namespace noexception {

template <typename T, typename E> class Result {
private:
  struct OkType {};
  struct ErrType {};

  union {
    T val;
    E err;
  };
  bool ok;

  template <typename U, typename... Args>
  static void construct(U *ptr, Args &&...args) {
    std::allocator<U> alloc;
    std::allocator_traits<std::allocator<U>>::construct(
        alloc, ptr, std::forward<Args>(args)...);
  }

  template <typename U> static void destroy(U *ptr) {
    std::allocator<U> alloc;
    std::allocator_traits<std::allocator<U>>::destroy(alloc, ptr);
  }

  Result(T v, OkType) : ok(true) { construct(&val, std::move(v)); }

  Result(E e, ErrType) : ok(false) { construct(&err, std::move(e)); }

public:
  static Result<T, E> Ok(T v) { return Result<T, E>(std::move(v), OkType{}); }
  static Result<T, E> Err(E e) { return Result<T, E>(std::move(e), ErrType{}); }

  bool is_ok() const { return ok; }
  bool is_err() const { return !ok; }

  T &unwrap() {
    if (!ok)
      std::abort();
    return val;
  }

  const T &unwrap() const {
    if (!ok)
      std::abort();
    return val;
  }

  E &unwrap_err() {
    if (ok)
      std::abort();
    return err;
  }

  const E &unwrap_err() const {
    if (ok)
      std::abort();
    return err;
  }

  T unwrap_or(T default_value) const { return ok ? val : default_value; }

  T unwrap_or_else(std::function<T()> f) const { return ok ? val : f(); }

  template <typename U> Result<U, E> map(std::function<U(T)> f) const {
    if (ok)
      return Result<U, E>::Ok(f(val));
    return Result<U, E>::Err(err);
  }

  template <typename F>
  auto map_err(F f) const -> Result<T, decltype(f(std::declval<E>()))> {
    using E2 = decltype(f(std::declval<E>()));
    if (ok)
      return Result<T, E2>::Ok(val);
    return Result<T, E2>::Err(f(err));
  }

  template <typename F>
  auto and_then(F f) const -> decltype(f(std::declval<T>())) {
    if (ok)
      return f(val);
    using R = decltype(f(std::declval<T>()));
    return R::Err(err);
  }

  template <typename F>
  auto or_else(F f) const -> decltype(f(std::declval<E>())) {
    if (!ok)
      return f(err);
    using R = decltype(f(std::declval<E>()));
    return R::Ok(val);
  }

  ~Result() {
    if (ok) {
      destroy(&val);
    } else {
      destroy(&err);
    }
  }

  Result(Result &&other) noexcept(
      std::is_nothrow_move_constructible<T>::value &&
      std::is_nothrow_move_constructible<E>::value)
      : ok(other.ok) {
    if (ok) {
      construct(&val, std::move(other.val));
    } else {
      construct(&err, std::move(other.err));
    }
  }

  Result(const Result &other) : ok(other.ok) {
    if (ok) {
      construct(&val, other.val);
    } else {
      construct(&err, other.err);
    }
  }

  Result &operator=(Result &&other) noexcept(
      std::is_nothrow_move_assignable<T>::value &&
      std::is_nothrow_move_assignable<E>::value) {
    if (this == &other)
      return *this;
    this->~Result();
    ok = other.ok;
    if (ok) {
      construct(&val, std::move(other.val));
    } else {
      construct(&err, std::move(other.err));
    }
    return *this;
  }

  Result &operator=(const Result &other) {
    if (this == &other)
      return *this;
    this->~Result();
    ok = other.ok;
    if (ok) {
      construct(&val, other.val);
    } else {
      construct(&err, other.err);
    }
    return *this;
  }
};

} // namespace noexception

#endif // __cplusplus >= 202002L

#endif // RESULT_H
