#ifndef STATIC_SET_HPP
#define STATIC_SET_HPP

#include <algorithm>
#include <cassert>
#include <concepts>
#include <functional>
#include <memory>

// Like ArraySet, but lives on the stack
template <class T, std::size_t N, class Eq = std::equal_to<T>>
requires std::predicate<Eq, const T&, const T&>
class StaticSet {
  // unions don't call constructors or destructors manually
  // we use this to reserve and align the right amount of memory
  // there are other ways to do this (e.g. std::aligned_storage )
  // however i'm pretty sure this is Undefined Behaviour (spooky ahh code)
  // C++ 26 has std::inplace_vector which implements this correctly
  union {
    T data[N];
  };
  std::size_t length;
  Eq eq;

public:
  StaticSet() : StaticSet(Eq{}) {}
  StaticSet(const Eq& _eq) : length(0), eq(_eq) {}
  StaticSet(const StaticSet& other) : length(other.length), eq(other.eq) {
    for (std::size_t i = 0; i < other.length; ++i)
      std::construct_at(&data[i], other.data[i]);
  }
  StaticSet(StaticSet&& other) : length(other.length), eq(std::move(other.eq)) {
    for (std::size_t i = 0; i < other.length; ++i)
      std::construct_at(&data[i], std::move(other.data[i]));
    other.clear();
  }
  StaticSet& operator=(const StaticSet& other) {
    if (this == &other)
      return *this;
    this->~StaticSet();
    return *std::construct_at(this, other);
  }
  StaticSet& operator=(StaticSet&& other) {
    if (this == &other)
      return *this;
    this->~StaticSet();
    return *std::construct_at(this, std::move(other));
  }
  ~StaticSet() {
    clear();
  }

  void insert(const T& value) {
    if (contains(value))
      return;
    assert(length < N);
    // manual initialization
    std::construct_at(&data[length++], value);
  }

  void erase(const T& value) {
    std::size_t idx = N;
    for (std::size_t i = 0; i < length; ++i)
      if (eq(data[i], value)) {
        idx = i;
        break;
      }

    if (idx == N)
      return;
    for (std::size_t i = idx + 1; i < length; ++i)
      // prefer move assignment
      data[i - 1] = std::move(data[i]);
    data[--length].~T();
  }

  bool contains(const T& value) const {
    for (std::size_t i = 0; i < length; ++i)
      if (eq(data[i], value))
        return true;
    return false;
  }

  std::size_t size() const {
    return length;
  }

  bool empty() const {
    return length == 0;
  }

  void clear() {
    std::destroy_n(data, length);
    length = 0;
  }
};

#endif
