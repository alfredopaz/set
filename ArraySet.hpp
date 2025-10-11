#ifndef ARRAY_SET_H
#define ARRAY_SET_H

#include <algorithm>
#include <cassert>
#include <vector>

template <class T, class Eq = std::equal_to<T>>
requires std::predicate<Eq, const T&, const T&>
class ArraySet {
  std::vector<T> data;
  Eq eq;

public:
  // Thanks std::vector, for making everything so easy!
  ArraySet() = default;
  explicit ArraySet(const Eq& _eq) : eq(_eq) {}
  ArraySet(const ArraySet&) = default;
  ArraySet(ArraySet&&) noexcept = default;
  ArraySet& operator=(const ArraySet&) = default;
  ArraySet& operator=(ArraySet&&) noexcept = default;
  ~ArraySet() = default;

  void insert(const T& value) {
    if (!contains(value))
      data.push_back(value);
  }

  void erase(const T& value) {
    std::erase_if(data, [&](const T& t) { return eq(t, value); });
  }

  bool contains(const T& value) const {
    return std::ranges::any_of(data, [&](const T& t) { return eq(t, value); });
  }

  bool empty() const {
    return data.empty();
  }
};

#endif
