#ifndef ISET_H
#define ISET_H

#include <iostream> //sólo para depuración

class ISet {
  public:
    virtual ~ISet(){
      std::cerr << "ISet::~ISet\n";
    }
    virtual void insert(int) = 0;
    virtual void remove(int) = 0;
    virtual bool contains(int) const = 0;
    virtual bool isEmpty() const = 0;
};

#endif
