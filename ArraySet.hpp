#ifndef ARRAY_SET_H
#define ARRAY_SET_H

#include <algorithm>
#include <cassert>
#include <vector>

template <class T>
class ArraySet {
  std::vector<T> data;

public:
  void insert(const T& value) {
    if (!contains(value))
      data.push_back(value);
  }

  void erase(const T& value) {
    std::erase(data, value);
  }

  bool contains(const T& value) const {
    return std::ranges::contains(data, value);
  }

  bool empty() const {
    return data.empty();
  }
};

#endif
