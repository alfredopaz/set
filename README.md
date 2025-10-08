# TDA Set — Implementación con Arreglos y Verificación Algebraica

## 1. Introducción

Este proyecto implementa el **Tipo de Dato Abstracto (TDA) Set** (*conjunto*) de enteros en C++ clásico, utilizando un **arreglo dinámico** como estructura interna.  
El objetivo principal es mostrar cómo una **especificación algebraica** puede traducirse a código, y cómo se pueden **verificar los axiomas del TDA** mediante `assert`.

Esta primera versión:

- No usa STL (`std::set`, `std::vector`, etc.).
- No usa plantillas (`template`).
- No usa manejo de excepciones (`try/catch`, `std::nothrow`).
- Es deliberadamente **simple, autocontenida y verificable**.

---

## 2. Especificación algebraica del TDA Set

Un conjunto (`Set`) es un tipo abstracto que cumple con las siguientes operaciones y axiomas.

### Operaciones

| Operación | Firma | Descripción |
|------------|--------|-------------|
| `init`     | → Set | conjunto vacío |
| `insert`   | Set × Int → Set | inserta un elemento |
| `erase`   | Set × Int → Set | elimina un elemento |
| `in`       | Set × Int → Bool | determina si un elemento pertenece |
| `isEmpty`  | Set → Bool | indica si el conjunto está vacío |

### Axiomas fundamentales

1. **Vacío:**  
   `in(init(), x) = false`
2. **Inserción:**  
   `in(insert(S, x), x) = true`
3. **Idempotencia:**  
   `insert(insert(S, x), x) = insert(S, x)`
4. **Eliminación:**  
   `in(erase(S, x), x) = false`
5. **Eliminar en vacío:**  
   `erase(init(), x) = init()`
6. **Eliminar tras insertar:**  
   `erase(insert(S, x), x) = S`
7. **Inserción no afecta a otros elementos:**  
   `y ≠ x ⇒ in(insert(S, x), y) = in(S, y)`
8. **Eliminación no afecta a otros elementos:**  
   `y ≠ x ⇒ in(erase(S, x), y) = in(S, y)`

Estos axiomas definen la **semántica matemática** del TDA Set, independientemente de su implementación concreta.

---

## 3. Diseño de la implementación

El código está dividido en dos partes:

### 3.1. Interfaz (`ISet.h`)

Define las operaciones del TDA, sin especificar cómo se implementan:

```cpp
class ISet {
public:
  virtual ~ISet() {}
  virtual void insert(int value) = 0;
  virtual void erase(int value) = 0;
  virtual bool contains(int value) const = 0;
  virtual bool isEmpty() const = 0;
};
```

### 3.2. Implementación (`ArraySet.cpp` / `ArraySet.h`)

Usa un arreglo dinámico de enteros (`int* data`) para almacenar los elementos.  
Se asume un límite máximo fijo (`cap`) y un contador de ocupación (`nextFree`).

#### Invariantes estructurales

- `0 <= nextFree <= cap`
- `data != nullptr`
- No hay duplicados en las posiciones `[0, nextFree)`

#### Verificación de axiomas

La implementación incluye `assert` que verifican los axiomas más relevantes:

| Axioma | Método | Explicación |
|--------|---------|-------------|
| A1 `in(init(), x) == false` | Constructor | Un conjunto recién creado está vacío |
| A2 `in(insert(S, x), x) == true` | `insert()` | Tras insertar, el elemento pertenece |
| A3 `insert(insert(S, x), x) == insert(S, x)` | `insert()` | Insertar un duplicado no cambia el conjunto |
| A4 `in(erase(S, x), x) == false` | `erase()` | Tras eliminar, el elemento ya no pertenece |
| A5 `erase(init(), x) == init()` | `erase()` | Eliminar en vacío no altera el conjunto |
| A6 `erase(insert(S, x), x) == S` | `erase()` | Eliminar tras insertar restaura el conjunto |
| A7 `y ≠ x ⇒ in(insert(S, x), y) = in(S, y)` | `insert()` | Insertar un elemento no afecta otros |
| A8 `y ≠ x ⇒ in(erase(S, x), y) = in(S, y)` | `erase()` | Eliminar un elemento no afecta otros |

Compilando con `-DNDEBUG`, todas las aserciones desaparecen,  
dejando solo el comportamiento funcional.

---

## 4. Uso del Makefile

El proyecto incluye un archivo **Makefile** para simplificar la compilación y ejecución.

### Comandos principales

| Comando | Descripción |
|----------|--------------|
| `make` | Compila el programa con las verificaciones `assert` activadas (modo depuración). |
| `make run` | Ejecuta el programa después de compilarlo. |
| `make release` | Compila el programa en modo *release*, desactivando los `assert` (añade `-DNDEBUG`). |
| `make clean` | Elimina los archivos objeto (`.o`) y el ejecutable. |

### Ejemplos

```bash
# Compilar y ejecutar con assert
make
make run

# Compilar sin assert (modo release)
make release
./set

# Limpiar archivos generados
make clean

