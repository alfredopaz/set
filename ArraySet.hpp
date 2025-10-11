#ifndef ARRAYSET_H
#define ARRAYSET_H

#include "ISet.hpp"
#include <cassert>
#include <functional>

// this REALLY should just use a std::vector, doing things this way is dangerous
// and error prone when you're not dealing with mere int's
template <class T, class Eq = std::equal_to<T>>
class ArraySet : public ISet<T> {
  T* data;
  std::size_t cap;
  int nextFree;
  Eq eq;

public:
  explicit ArraySet(const Eq& _eq = {}) : ArraySet(5, _eq) {}
  explicit ArraySet(std::size_t capacity, const Eq& _eq = {}) :
    data(nullptr),
    cap(capacity),
    nextFree(0),
    eq(_eq) {
    assert(cap > 0);
    data = new T[cap];
  }

  virtual ~ArraySet() override {
    delete[] data;
  }

  virtual void insert(const T& value) override {
    if (contains(value))
      return;
    assert(nextFree < cap);
    data[nextFree++] = value;
  }

  virtual void remove(const T& value) override {
    int idx = -1;
    for (int i = 0; i < nextFree; ++i)
      if (eq(data[i], value)) {
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
      if (eq(data[i], value))
        return true;

    return false;
  }

  virtual bool isEmpty() const override {
    return nextFree == 0;
  }
};

#endif
