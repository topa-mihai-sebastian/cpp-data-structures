# Modern C++ Data Structures

This repository is a personal educational project dedicated to implementing standard data structures from scratch using modern C++. 

The main goal is to deeply understand how the C++ Standard Template Library (STL) works under the hood. By rebuilding these core components, this project explores advanced C++ topics such as:

- **Manual Dynamic Memory Management** (`new[]` / `delete[]`)
- **The "Rule of 5"** (Deep copy semantics vs. Move semantics)
- **Exception Safety** and `noexcept` guarantees
- **Templating** and generic programming
- **Pointer-based Iterators** and native compatibility with modern language features like range-based for loops.

## Implemented Data Structures

### 1. [Vector](./Vector/)
A fully functional, custom implementation of `std::vector` inside the `sebi` namespace. It replicates the core behavior of the standard sequence container.
- **Key functionalities:** Features dynamic memory reallocation (via `push_back` and `reserve`), strict Rule of 5 compliance for safe abstractions, mathematical operator overloads (`+`, `+=`), and `std::initializer_list` support.
- For detailed technical specifics and usage examples, check out the [Vector README](./Vector/README.md).