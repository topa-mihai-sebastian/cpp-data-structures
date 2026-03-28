# Custom C++ Vector

This project is a custom implementation of the `std::vector` container from the C++ Standard Template Library (STL). Located under the `sebi::vector<T>` namespace, the project serves a strictly educational purpose, being built from scratch to deepen the understanding of advanced C++ concepts (dynamic memory management, the "Rule of 5", templating, and iterators).

## Implemented Features

As of now, the `sebi::vector<T>` class supports the following operations and concepts:

### 1. Core Concepts and the "Rule of 5"
- **Various Constructors**: 
  - Standard (Default).
  - Capacity-based allocation (`vector(size_t _capacity)`).
  - Constructor with `std::initializer_list` (supports syntax like `vector<int> v = {1, 2, 3};`).
- **Copy Constructor & Copy Assignment Operator**: For performing a safe, full deep copy.
- **Move Constructor & Move Assignment Operator** (`noexcept`): For fast, exception-free resource transfer without new allocations, applying `std::move` semantics.
- **Destructor**: Prevents memory leaks by deallocating the underlying array via `delete[] data;`.

### 2. State Modifiers
- `push_back(const T& element)`: Insertion at the end. Includes auto-reallocation logic (doubling the capacity) when the limit is reached.
- `pop_back()`: Fast deletion of the last element by decrementing the size (logical free).
- `reserve(size_t new_cap)`: Memory pre-allocation for increased efficiency, avoiding repeated inefficient reallocations.
- `clear()`: Empties the vector's content by setting its visible size to 0 while keeping the allocated capacity.

### 3. Iterators and "Range-based for loops"
- The class defines internal types `iterator` (`T*`) and `const_iterator` (`const T*`).
- Provides the standard `begin()` and `end()` functions, offering native compatibility with modern range-based for loops: `for(const auto& item : v) { ... }`.

### 4. Status Query & Element Access
- `operator[]`: Extremely fast positional memory access (both read and write).
- `back()`: Protected function (throws `std::out_of_range`) to return the last element.
- `size()`, `capacity()`, `empty()`: Return current indexing capacities.

### 5. Additional Operators
- `operator+=(const vector<T>&)` and `operator+(const vector<T>&)`: Implemented for member-by-member addition, ideal for linear math simulations, with dimension guard checks.
