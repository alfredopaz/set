#include "ArraySet.h"
#include <cassert>
#include <iostream> //sólo para depuración

ArraySet::ArraySet(int capacity)
  : data(0), cap(capacity), nextFree(0) {
  assert(cap > 0);
  data = new int[cap];
  assert(isEmpty());                         // A1
}

ArraySet::~ArraySet() {
  std::cerr << "ArraySet::~ArraySet\n";
  delete[] data;
}

void ArraySet::insert(int value) {
  assert(data != 0);
  assert(nextFree >= 0 && nextFree <= cap);

  int before = nextFree;
  bool alreadyPresent = contains(value);

  if (!alreadyPresent) {
    assert(nextFree < cap);
    data[nextFree++] = value;
  }

  assert(contains(value));                   // A2
  assert(nextFree == before + (alreadyPresent ? 0 : 1)); // A8
}

void ArraySet::remove(int value) {
  assert(data != 0);
  assert(nextFree >= 0 && nextFree <= cap);

  bool wasEmpty = isEmpty();
  int before = nextFree;

  for (int i = 0; i < nextFree; ++i) {
    if (data[i] == value) {
      data[i] = data[nextFree - 1];
      --nextFree;
      break;
    }
  }

  assert(!contains(value));                  // A4
  if (wasEmpty) assert(isEmpty());           // A7
  assert(nextFree >= 0 && nextFree <= before);
}

bool ArraySet::contains(int value) const {
  assert(data != 0);
  for (int i = 0; i < nextFree; ++i)
    if (data[i] == value) return true;
  return false;
}

bool ArraySet::isEmpty() const {
  return nextFree == 0;
}

