# 03. Variables, Initialization, Constness, and Types

## 1. Variables & Memory in C++

In Python, a variable is an object reference/pointer dynamically bound to a heap-allocated object (`x = 5`).
In C++, a variable is a **named region of memory (RAM)** with a fixed size and fixed type determined at compile time.

### Forms of Initialization:
```cpp
int a;       // 1. Uninitialized: Contains GARBAGE bits from previous memory usage! (DANGEROUS)
int b = 5;   // 2. Copy initialization: Inherited from C.
int c(5);    // 3. Direct initialization.
int d{5};    // 4. Direct list initialization (Brace initialization) -> PREFERRED
int e{};     // 5. Value initialization: Zero-initializes the variable (e becomes 0).
```

### Why Modern C++ Prefers Brace Initialization (`{}`):
**It prevents narrowing conversions.**
- In Python, `int(4.9)` truncates to `4`.
- In C++, copy initialization silently drops data without error:
  ```cpp
  int x = 4.9; // Compiles! Silently truncates to 4 (loss of data).
  ```
- Brace initialization turns accidental data loss into a **compile-time error**:
  ```cpp
  int x{4.9}; // COMPILE ERROR: narrowing conversion of '4.9' from 'double' to 'int'
  ```

---

## 2. Immutability: `const` vs. `constexpr`

In Python, constants are just a naming convention (e.g., `MAX_RETRIES = 5`), with no compiler enforcement.
In C++, immutability is strictly enforced by the compiler:

| Feature | `const` | `constexpr` |
| :--- | :--- | :--- |
| **When is value decided?** | At runtime or compile-time. | Strictly at **compile-time**. |
| **Can use runtime inputs (`cin`)?** | Yes: `const int x{user_input};` | **No.** Value must be fixed before the program runs. |
| **Modification after init?** | Illegal (compiler error). | Illegal (compiler error). |
| **Typical use** | Read-only values from user/file/computation. | Fixed math constants, array sizes, compile-time tables. |

Example:
```cpp
constexpr int gravity{10};       // Known at compile time
const int user_choice{input};    // Known only when user enters it, but read-only afterwards
```

---

## 3. Fundamental Data Types & `sizeof`

| Type | Typical Size | Range / Purpose | Python Equivalent |
| :--- | :--- | :--- | :--- |
| `bool` | 1 byte | `true` (1) or `false` (0) | `bool` |
| `char` | 1 byte | -128 to 127 (or 0 to 255). Stores ASCII small int. | `chr()` / `ord()` / 1-char `str` |
| `int` | 4 bytes (32-bit) | $-2,147,483,648$ to $2,147,483,647$ | `int` (but Python has infinite precision) |
| `unsigned int` | 4 bytes (32-bit) | $0$ to $4,294,967,295$ (strictly non-negative) | None (Python ints are signed) |
| `double` | 8 bytes (64-bit) | $\approx \pm 1.7 \times 10^{\pm 308}$ ($\approx 15\text{--}17$ sig figs) | `float` |

### `sizeof` Operator
`sizeof(type)` or `sizeof(variable)` returns the exact size in bytes allocated in memory on your specific machine.

### `char` is a Small Integer
In C++, a `char` is **literally a 1-byte integer**.
- When you do `char c{'A'};`, the byte in memory actually contains the integer number `65`.
- `std::cout << c;` prints `A` because `std::cout` inspects the type (`char`) and formats it as a character.
- If you cast it to an integer using `static_cast<int>(c)` or assign it to an `int`, you see `65` (equivalent to Python's `ord('A')`).

