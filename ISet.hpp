#ifndef ISET_H
#define ISET_H

template <typename T>
class ISet {
  public:
    virtual ~ISet() = default;
    virtual void insert(const T&) = 0;
    virtual void remove(const T&) = 0;
    virtual bool contains(const T&) const = 0;
    virtual bool isEmpty() const = 0;
};

#endif
