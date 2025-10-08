#ifndef ARRAYSET_H
#define ARRAYSET_H

#include "ISet.hpp"
#include <cassert>

// Versión template, definiciones "en línea" dentro de la clase.
template <class T>
class ArraySet : public ISet<T> {
  T* data;
  std::size_t cap;
  int nextFree;

public:
  explicit ArraySet(std::size_t capacity = 5) :
    data(nullptr),
    cap(capacity),
    nextFree(0) {
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
