#include "ArraySet.hpp"
#include "BstSet.hpp"
#include "Set.hpp"
#include "StaticSet.hpp"
#include <cassert>
#include <iostream>
#include <set>

template <Set<int> T>
void test() {
  // A1: in(init(), x) == false
  {
    T s;
    std::cout << "A1: conjunto recién creado debe estar vacío...\n";
    assert(s.empty());
    assert(!s.contains(10));
  }

  // A2: in(insert(S, x), x) == true
  {
    T s;
    std::cout << "A2: insertar un elemento debe hacerlo perteneciente...\n";
    s.insert(7);
    assert(s.contains(7));
  }

  // A8: insert(insert(S, x), x) == insert(S, x)
  {
    T s;
    std::cout
      << "A8: insertar dos veces el mismo elemento no cambia el conjunto...\n";
    s.insert(4);
    s.insert(4); // duplicado
    assert(s.contains(4));
    s.erase(4);
    assert(s.empty());
  }

  // A4: in(erase(S, x), x) == false
  {
    T s;
    std::cout << "A4: eliminar un elemento lo hace no perteneciente...\n";
    s.insert(3);
    s.erase(3);
    assert(!s.contains(3));
  }

  // A7: erase(init(), x) == init()
  {
    T s;
    std::cout << "A7: eliminar en conjunto vacío no altera el estado...\n";
    assert(s.empty());
    s.erase(9);
    assert(s.empty());
  }

  // Secuencia combinada (integración de varios axiomas)
  {
    T s;
    std::cout << "Secuencia combinada: inserción, duplicado y eliminación...\n";
    s.insert(1); // A2
    s.insert(1); // A8
    s.insert(2);
    s.erase(1); // A4
    s.erase(3); // A7
    assert(!s.contains(1));
    assert(s.contains(2));
  }

  std::cout << "\nTodas las pruebas de axiomas superadas exitosamente.\n";
  std::cout << "--------------------------------\n";
}

int main() {
  std::cout << "Pruebas del TDA Set (ArraySet)\n";
  std::cout << "--------------------------------\n";
  test<ArraySet<int>>();

  std::cout << "Pruebas del TDA Set (StaticSet)\n";
  std::cout << "--------------------------------\n";
  test<StaticSet<int, 5>>();

  std::cout << "Pruebas del TDA Set (BstSet)\n";
  std::cout << "--------------------------------\n";
  test<BstSet<int>>();

  std::cout << "Pruebas del TDA Set (std::set)\n";
  std::cout << "--------------------------------\n";
  test<std::set<int>>();

  return 0;
}
