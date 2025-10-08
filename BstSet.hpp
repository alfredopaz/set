#ifndef TREE_SET_HPP
#define TREE_SET_HPP

#include "ISet.hpp"
#include <cassert>
#include <memory>

template <class T>
class BstSet : public ISet<T> {
  struct Node {
    T val;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
    explicit Node(const T& v) : val(v) {}
  };

  std::unique_ptr<Node> root;

public:
  BstSet() = default;
  virtual ~BstSet() override = default;
  virtual void insert(const T& value) override {
    // sometimes raw pointers are truly inevitable
    auto* current = &root;
    while (*current) {
      if (value < (*current)->val)
        current = &(*current)->left;
      else if (value > (*current)->val)
        current = &(*current)->right;
      else
        return; // already here
    }
    *current = std::make_unique<Node>(value);
  }

  void remove(const T& value) override {
    auto* current = &root;
    while (*current)
      if (value < (*current)->val)
        current = &(*current)->left;
      else if (value > (*current)->val)
        current = &(*current)->right;
      else
        break;

    if (!*current)
      return;

    // no children
    if (!(*current)->left && !(*current)->right)
      current->reset();
    // only right
    else if (!(*current)->left)
      *current = std::move((*current)->right);
    // only left
    else if (!(*current)->right)
      *current = std::move((*current)->left);
    // parent of succesor
    else if (!(*current)->right->left) {
      (*current)->right->left = std::move((*current)->left);
      *current = std::move((*current)->right);
    } else {
      auto* successor = &(*current)->right;
      while ((*successor)->left)
        successor = &(*successor)->left;

      auto y = std::move(*successor);
      *successor = std::move(y->right);
      y->left = std::move((*current)->left);
      y->right = std::move((*current)->right);
      *current = std::move(y);
    }
  }

  virtual bool contains(const T& value) const override {
    auto current = root.get();
    while (current)
      if (value < current->val)
        current = current->left.get();
      else if (value > current->val)
        current = current->right.get();
      else
        return true;
    return false;
  }

  virtual bool isEmpty() const override {
    return !root;
  }
};

#endif
