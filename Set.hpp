#ifndef SET_HPP
#define SET_HPP

#include <concepts>
#include <memory>
#include <utility>

template <class S, class T>
concept Set = requires(S& s, const T& t) {
  { s.insert(t) };
  { s.erase(t) };
  { std::as_const(s).contains(t) } -> std::same_as<bool>;
  { std::as_const(s).empty() } -> std::same_as<bool>;
};

template <class T>
class DynSet {
  struct VTable {
    void (*insert)(void*, const T&);
    void (*erase)(void*, const T&);
    bool (*contains)(const void*, const T&);
    bool (*empty)(const void*);
  };
  template <class S>
  static constexpr VTable V_TABLE = {
    [](void* ptr, const T& t) { ((S*)ptr)->insert(t); },
    [](void* ptr, const T& t) { ((S*)ptr)->erase(t); },
    [](const void* ptr, const T& t) { return ((const S*)ptr)->contains(t); },
    [](const void* ptr) { return ((const S*)ptr)->empty(); },
  };

  std::unique_ptr<void, void (*)(void*)> set;
  const VTable* v_table;

public:
  template <Set<T> S, class... Args>
  DynSet(std::in_place_type_t<S>, Args&&... args) :
    set(
      new S(std::forward<Args>(args)...), [](void* ptr) { delete ((S*)ptr); }
    ),
    v_table(&V_TABLE<S>) {}

  void insert(const T& t) {
    return v_table->insert(set.get(), t);
  }
  void erase(const T& t) {
    return v_table->erase(set.get(), t);
  }
  bool contains(const T& t) const {
    return v_table->contains(set.get(), t);
  }
  bool empty() const {
    return v_table->empty(set.get());
  }
};

#endif
