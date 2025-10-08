#ifndef BST_SET_HPP
#define BST_SET_HPP

#include <cassert>
#include <memory>

template <class T>
class BstSet {
  struct Node {
    T val;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
    explicit Node(const T& v) : val(v) {}
  };

  std::unique_ptr<Node> root;

public:
  void insert(const T& value) {
    // sometimes raw pointers to pointers are truly inevitable
    auto* p_current = &root;
    while (*p_current)
      if (value < (*p_current)->val)
        p_current = &(*p_current)->left;
      else if (value > (*p_current)->val)
        p_current = &(*p_current)->right;
      else
        return; // already here

    *p_current = std::make_unique<Node>(value);
  }

  void erase(const T& value) {
    // yuck
    auto* p_current = &root;
    while (*p_current)
      if (value < p_current->get()->val)
        p_current = &p_current->get()->left;
      else if (value > p_current->get()->val)
        p_current = &p_current->get()->right;
      else
        break;

    // get rid of this blaspehmy
    auto& current = *p_current;
    if (!current)
      return;

    // no children
    if (!current->left && !current->right)
      current.reset();
    // only right
    else if (!current->left)
      current = std::move(current->right);
    // only left
    else if (!current->right)
      current = std::move(current->left);
    // parent of succesor
    else if (!current->right->left) {
      current->right->left = std::move(current->left);
      current = std::move(current->right);
    } else {
      auto* p_successor = &current->right;
      while (p_successor->get()->left)
        p_successor = &p_successor->get()->left;
      auto& successor = *p_successor;

      auto y = std::move(successor);
      successor = std::move(y->right);
      y->left = std::move(current->left);
      y->right = std::move(current->right);
      current = std::move(y);
    }
  }

  bool contains(const T& value) const {
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

  bool empty() const {
    return !root;
  }
};

#endif
