# Custom C++ Vector 🚀

Acest proiect este o implementare custom a containerului `std::vector` din C++ Standard Template Library (STL). Sub namespace-ul `sebi::vector<T>`, proiectul are scop pur educațional, fiind construit from scratch pentru a aprofunda concepte avansate de C++ (gestionarea dinamică a memoriei, "Rule of 5", templating și iteratori).

## Funcționalități Implementate ✨

Până în acest moment, clasa `sebi::vector<T>` suportă următoarele operații și concepte:

### 1. Concepte de bază și "Rule of 5"
- **Constructori variați**: 
  - Standard (Default).
  - Alocare pe bază de capacitate (`vector(size_t _capacity)`).
  - Constructor cu `std::initializer_list` (suport pentru syntaxa `vector<int> v = {1, 2, 3};`).
- **Copy Constructor & Copy Assignment Operator**: Pentru efectuarea unei copierii complete (deep copy) cap-coadă în siguranță.
- **Move Constructor & Move Assignment Operator** (`noexcept`): Pentru un transfer de resurse rapid și lipsit de excepții (fără alocări noi) aplicând semantica `std::move`.
- **Destructor**: Previne *memory leak-urile* dealocând memoria array-ului `delete[] data;`.

### 2. Modificatori de stare
- `push_back(const T& element)`: Inserare la final. Include logică de realocare automată a memoriei (dublarea capacității) atunci când limita a fost atinsă.
- `pop_back()`: Ștergere rapidă a ultimului element prin decrementarea mărimii (free logic).
- `reserve(size_t new_cap)`: Pre-realocare de memorie pentru o eficiență sporită, evitând re-alocările ineficiente repetate.
- `clear()`: Golește conținutul vectorului setând o mărime vizibilă ca 0, păstrând capacitatea alocată.

### 3. Iteratori și "Range-based for loops"
- Clasa implementează intern tipurile `iterator` (`T*`) și `const_iterator` (`const T*`).
- Oferă funcțiile standard `begin()` și `end()`, oferind compatibilitate nativă cu loop-urile moderne for-each: `for(const auto& item : v) { ... }`.

### 4. Interogare Status & Acces Elemente
- `operator[]`: Acces pozițional extrem de rapid spre memorie (atât read cât și write).
- `back()`: Funcție cu un layer activ de protecție (aruncă `std::out_of_range`) pentru returnarea ultimului element.
- `size()`, `capacity()`, `empty()`: Returnează date referitoare la capacitățile de indexare curente.

### 5. Operatori Suplimentari
- `operator+=(const vector<T>&)` și `operator+(const vector<T>&)` implementați pentru adunare membru-cu-membru, ideal în simulările de matematică liniară, cu guard checks pentru siguranța indexării.