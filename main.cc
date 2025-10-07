
#include <iostream>
#include <cassert>
#include "ArraySet.h"
#include "Persona.h"

struct IgualPorDni {
  bool operator()(const Persona& a, const Persona& b) const {
    return a.dni == b.dni;
  }
};

int main() {
  std::cout << "Pruebas del TDA Set (ArraySet)\n";
  std::cout << "--------------------------------\n";

  // A1: in(init(), x) == false
  {
    ArraySet<int> s(5);
    std::cout << "A1: conjunto recién creado debe estar vacío...\n";
    assert(s.isEmpty());
    assert(!s.contains(10));
  }

  // A2: in(insert(S, x), x) == true
  {
    ArraySet<int> s(5);
    std::cout << "A2: insertar un elemento debe hacerlo perteneciente...\n";
    s.insert(7);
    assert(s.contains(7));
  }

  // A8: insert(insert(S, x), x) == insert(S, x)
  {
    ArraySet<int> s(5);
    std::cout << "A8: insertar dos veces el mismo elemento no cambia el conjunto...\n";
    s.insert(4);
    s.insert(4); // duplicado
    assert(s.contains(4));
    s.remove(4);
    assert(s.isEmpty());
  }

  // A4: in(remove(S, x), x) == false
  {
    ArraySet<int> s(5);
    std::cout << "A4: eliminar un elemento lo hace no perteneciente...\n";
    s.insert(3);
    s.remove(3);
    assert(!s.contains(3));
  }

  // A7: remove(init(), x) == init()
  {
    ArraySet<int> s(5);
    std::cout << "A7: eliminar en conjunto vacío no altera el estado...\n";
    assert(s.isEmpty());
    s.remove(9);
    assert(s.isEmpty());
  }

  // Secuencia combinada (integración de varios axiomas)
  {
    ArraySet<int> s(5);
    std::cout << "Secuencia combinada: inserción, duplicado y eliminación...\n";
    s.insert(1);   // A2
    s.insert(1);   // A8
    s.insert(2);
    s.remove(1);   // A4
    s.remove(3);   // A7
    assert(!s.contains(1));
    assert(s.contains(2));
  }

  std::cout << "\nTodas las pruebas de axiomas superadas exitosamente.\n";
  std::cout << "--------------------------------\n";

  {
    ArraySet<Persona, IgualPorDni> s(5); // Usa el functor
    s.insert({"70234567","Jorge Gonzales"});
    if(s.contains({"70234567","ANA PEREZ"}))
      std::cerr << "EXISTE\n";
    else
      std::cerr << "NO existe\n";
  }
  return 0;
}
