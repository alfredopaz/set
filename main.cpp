#include "ArraySet.hpp"
#include "BstSet.hpp"
#include "Set.hpp"
#include "StaticSet.hpp"
#include <cassert>
#include <print>
#include <set>
#include <utility>

template <Set<int> T, class... Args>
void test(Args&&... args) {
  // A1: in(init(), x) == false
  {
    T s(std::forward<Args>(args)...);
    std::println("A1: conjunto recién creado debe estar vacío");
    assert(s.empty());
    assert(!s.contains(10));
  }

  // A2: in(insert(S, x), x) == true
  {
    T s(std::forward<Args>(args)...);
    std::println("A2: insertar un elemento debe hacerlo perteneciente");
    s.insert(7);
    assert(s.contains(7));
  }

  // A8: insert(insert(S, x), x) == insert(S, x)
  {
    T s(std::forward<Args>(args)...);
    std::println(
      "A8: insertar dos veces el mismo elemento no cambia el conjunto"
    );
    s.insert(4);
    s.insert(4); // duplicado
    assert(s.contains(4));
    s.erase(4);
    assert(s.empty());
  }

  // A4: in(erase(S, x), x) == false
  {
    T s(std::forward<Args>(args)...);
    std::println("A4: eliminar un elemento lo hace no perteneciente");
    s.insert(3);
    s.erase(3);
    assert(!s.contains(3));
  }

  // A7: erase(init(), x) == init()
  {
    T s(std::forward<Args>(args)...);
    std::println("A7: eliminar en conjunto vacío no altera el estado");
    assert(s.empty());
    s.erase(9);
    assert(s.empty());
  }

  // Secuencia combinada (integración de varios axiomas)
  {
    T s(std::forward<Args>(args)...);
    std::println("Secuencia combinada: inserción, duplicado y eliminación");
    s.insert(1); // A2
    s.insert(1); // A8
    s.insert(2);
    s.erase(1); // A4
    s.erase(3); // A7
    assert(!s.contains(1));
    assert(s.contains(2));
  }

  std::println();
  std::println("Todas las pruebas de axiomas superadas exitosamente.");
  std::println("--------------------------------");
}

void dyn_test() {
  test<DynSet<int>>(std::in_place_type<StaticSet<int, 5>>);
  test<DynSet<int>>(std::in_place_type<ArraySet<int>>);
  test<DynSet<int>>(std::in_place_type<BstSet<int>>);
  test<DynSet<int>>(std::in_place_type<std::set<int>>);
  // DynSet satisfies Set :D
  test<DynSet<int>>(
    std::in_place_type<DynSet<int>>, std::in_place_type<BstSet<int>>
  );

  DynSet<std::string> s = std::in_place_type<ArraySet<std::string>>;
  s.insert("hi");
  s = {std::in_place_type<std::set<std::string>>};
  std::println("{}", s.empty());
  s.insert("hiii");
  std::println("{}", s.empty());
  s = {std::in_place_type<ArraySet<std::string>>};
  for (auto&& e : {"alice", "bob", "mallory"})
    s.insert(e);
  for (auto&& e : {"alice", "bob", "mallory"})
    s.erase(e);
}

int main() {
  std::println("Pruebas del TDA Set (ArraySet)");
  std::println("--------------------------------");
  test<ArraySet<int>>();

  std::println("Pruebas del TDA Set (StaticSet)");
  std::println("--------------------------------");
  test<StaticSet<int, 5>>();

  std::println("Pruebas del TDA Set (BstSet)");
  std::println("--------------------------------");
  test<BstSet<int>>();

  // std::set satisfies set
  std::println("Pruebas del TDA Set (std::set)");
  std::println("--------------------------------");
  test<std::set<int>>();

  return 0;
}
