#ifndef STATIC_SET_HPP
#define STATIC_SET_HPP

#include "ISet.hpp"
#include <algorithm>
#include <cassert>

// Like ArraySet, but lives on the stack
template <class T, std::size_t N>
class StaticSet : public ISet<T> {
  // unions don't call constructors or destructors manually
  // we use this to reserve and align the right amount of memory
  // there are other ways to do this (e.g. std::aligned_storage )
  // however i'm pretty sure this is Undefined Behaviour (spooky ahh code)
  // C++ 26 has std::inplace_vector which implements this correctly
  union {
    T data[N];
  };
  std::size_t length;

public:
  StaticSet() : length(0) {}
  virtual ~StaticSet() override {
    for (int i = 0; i < length; ++i)
      // manual destructor call
      data[i].~T();
  }

  virtual void insert(const T& value) override {
    if (contains(value))
      return;
    assert(length < N);
    // placement new (manual initialization)
    new (&data[length++]) T(value);
  }

  virtual void remove(const T& value) override {
    int idx = -1;
    for (int i = 0; i < length; ++i)
      if (data[i] == value) {
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

  virtual bool contains(const T& value) const override {
    for (int i = 0; i < length; ++i)
      if (data[i] == value)
        return true;
    return false;
  }

  virtual bool isEmpty() const override {
    return length == 0;
  }
};

#endif
