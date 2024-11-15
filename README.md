# Vector Implementation in C++

This repository contains a custom implementation of a dynamic array class, `Vector`, written in C++. The implementation features essential dynamic array operations, iterator support, and the ability to use templates for generalization.

## Table of Contents

- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)
- [Testing](#testing)
- [Contributing](#contributing)
- [License](#license)

---

## Features

### Basic Functionality
- Dynamic resizing with capacity management.
- Access and modify elements with bounds checking.
- Support for various constructors:
  - Default, copy, and parameterized constructors.
- Overloaded assignment operator for deep copies.
- `push_back`, `pop_back`, `clear`, `reserve`, and `shrink_to_fit`.

### Iterators
- Fully functional `Iterator` and `ConstIterator` classes.
- Compatible with STL algorithms (`std::for_each`, etc.).
- Support for `begin()` and `end()` for traversal.

### Insert and Erase
- `insert`: Add elements at a specific position.
- `erase`: Remove elements at a specific position.

### Templates
- Template support allows the `Vector` class to work with any data type.

### Output Formatting
- Overloaded `operator<<` for pretty-printing:
  ```cpp
  Vector v{1, 2, 3};
  std::cout << v; // Outputs: [1, 2, 3]
