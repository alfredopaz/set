#ifndef ARRAYSET_H
#define ARRAYSET_H

#include "ISet.h"

class ArraySet : public ISet {
  private:
    int* data;
    int cap;
    int nextFree;

  public:
    ArraySet(int capacity);
    ~ArraySet() override;

    void insert(int value) override; //garantiza que estamos redefiniendo
                                     //un método y no creando uno nuevo
    void remove(int value) override;
    bool contains(int value) const override;
    bool isEmpty() const override;
};

#endif // ARRAYSET_H

