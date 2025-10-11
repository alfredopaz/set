#ifndef STATIC_SET_HPP
#define STATIC_SET_HPP

#include <algorithm>
#include <cassert>
#include <concepts>
#include <functional>

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
  ~StaticSet() {
    for (int i = 0; i < length; ++i)
      // manual destructor call
      data[i].~T();
  }

  void insert(const T& value) {
    if (contains(value))
      return;
    assert(length < N);
    // placement new (manual initialization)
    new (&data[length++]) T(value);
  }

  void erase(const T& value) {
    int idx = -1;
    for (int i = 0; i < length; ++i)
      if (eq(data[i], value)) {
        idx = i;
        break;
      }

    if (idx < 0)
      return;
    for (int i = idx + 1; i < length; ++i)
      // prefer move assignment
      data[i - 1] = std::move(data[i]);
    data[--length].~T();
  }

  bool contains(const T& value) const {
    for (int i = 0; i < length; ++i)
      if (eq(data[i], value))
        return true;
    return false;
  }

  bool empty() const {
    return length == 0;
  }
};

#endif
