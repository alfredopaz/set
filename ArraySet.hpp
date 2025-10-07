#ifndef ARRAYSET_H
#define ARRAYSET_H

#include <cassert>
#include "ISet.h"

// Versión template, definiciones "en línea" dentro de la clase.
template <typename T>
class ArraySet : public ISet<T> {
private:
  T*  data;
  int cap;
  int nextFree;

public:
  explicit ArraySet(int capacity)
    : data(nullptr), cap(capacity), nextFree(0) {
    assert(cap > 0);
    data = new T[cap];
  }

  ~ArraySet() override {
    delete[] data;
  }

  void insert(const T& value) override {
    if (contains(value)) return;
    assert(nextFree < cap);
    data[nextFree++] = value;
  }

  void remove(const T& value) override {
    int idx = -1;
    for (int i = 0; i < nextFree; ++i) 
      if (data[i] == value) { idx = i; break; }
    
    if (idx < 0) return;
    for (int i = idx + 1; i < nextFree; ++i) 
      data[i - 1] = data[i];
    
    --nextFree;
  }

  bool contains(const T& value) const override {
    for (int i = 0; i < nextFree; ++i) 
      if (data[i] == value) return true;
    
    return false;
  }

  bool isEmpty() const override {
    return nextFree == 0;
  }
};

#endif // ARRAYSET_H

