#ifndef STATIC_SET_HPP
#define STATIC_SET_HPP

#include "ISet.hpp"
#include <cassert>

template <class T, std::size_t N>
class StaticSet : public ISet<T> {
  // this is potentially dangerous, it calls the default constructor for every
  // element of the array, even if T has a default constructor, this is
  // wasteful, we should initialize memory manually upon insertion (and
  // uninitialize upon deletion)
  T data[N];
  std::size_t nextFree;

public:
  explicit StaticSet() : nextFree(0) {}
  virtual ~StaticSet() override = default;

  virtual void insert(const T& value) override {
    if (contains(value))
      return;
    assert(nextFree < N);
    data[nextFree++] = value;
  }

  virtual void remove(const T& value) override {
    int idx = -1;
    for (int i = 0; i < nextFree; ++i)
      if (data[i] == value) {
        idx = i;
        break;
      }

    if (idx < 0)
      return;
    for (int i = idx + 1; i < nextFree; ++i)
      data[i - 1] = data[i];

    --nextFree;
  }

  virtual bool contains(const T& value) const override {
    for (int i = 0; i < nextFree; ++i)
      if (data[i] == value)
        return true;
    return false;
  }

  virtual bool isEmpty() const override {
    return nextFree == 0;
  }
};

#endif // ARRAYSET_H
