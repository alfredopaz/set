#include <iostream>
#include <cassert>
#include "ArraySet.h"
void expectEmpty(const ArraySet& s, const char* label) {
  std::cerr << label << ": " << (s.isEmpty() ? "OK": "ERROR") << "\n";
}

int main() {
  std::cout << "Pruebas del TDA Set (ArraySet)\n";
  std::cout << "--------------------------------\n";

  // A1: in(init(), x) == false
  {
    ArraySet s(5);
    std::cout << "A1: conjunto recién creado debe estar vacío...\n";
    assert(s.isEmpty());
    assert(!s.contains(10));
  }

  // A2: in(insert(S, x), x) == true
  {
    ArraySet s(5);
    std::cout << "A2: insertar un elemento debe hacerlo perteneciente...\n";
    s.insert(7);
    assert(s.contains(7));
  }

  // A8: insert(insert(S, x), x) == insert(S, x)
  {
    ArraySet s(5);
    std::cout << "A8: insertar dos veces el mismo elemento no cambia el conjunto...\n";
    s.insert(4);
    s.insert(4); // duplicado
    assert(s.contains(4));
    s.remove(4);
    assert(s.isEmpty());
  }

  // A4: in(remove(S, x), x) == false
  {
    ArraySet s(5);
    std::cout << "A4: eliminar un elemento lo hace no perteneciente...\n";
    s.insert(3);
    s.remove(3);
    assert(!s.contains(3));
  }

  // A7: remove(init(), x) == init()
  {
    ArraySet s(5);
    std::cout << "A7: eliminar en conjunto vacío no altera el estado...\n";
    assert(s.isEmpty());
    s.remove(9);
    assert(s.isEmpty());
  }

  // Secuencia combinada (integración de varios axiomas)
  {
    ArraySet s(5);
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
    std::cerr << "\n--- Demostración de destructores virtuales ---\n";
    ISet* s = new ArraySet(4);
    s->insert(10);
    s->insert(20);
    delete s;
  }

  {
    ArraySet s(4);
    s.insert(42); // s NO está vacío

    expectEmpty(s,   "control (debería FALLAR)");
    expectEmpty(1,   "conversión implicita no deseada");
  }
  return 0;
}

