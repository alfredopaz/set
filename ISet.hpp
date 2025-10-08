#ifndef ISET_H
#define ISET_H

// As it stands, this interface can't work for move-only types
// maybe add Iset::insert(T&&)
// (move semantics are important yo)
template <class T>
struct ISet {
  virtual ~ISet() = default;
  virtual void insert(const T&) = 0;
  virtual void remove(const T&) = 0;
  virtual bool contains(const T&) const = 0;
  virtual bool isEmpty() const = 0;
};

#endif
