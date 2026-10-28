# 04. Fixed-Width Integers and Operators

## 1. Fixed-Width Integers (`<cstdint>`)

In Python, integers have arbitrary precision (they automatically grow to handle numbers of any size without overflow).
In standard C++, primitive types like `int`, `long`, and `short` only have *minimum* guaranteed sizes, which vary between operating systems (e.g., `long` is 4 bytes on Windows 64-bit, but 8 bytes on Linux 64-bit).

To guarantee exact bit widths across all platforms, C++ provides fixed-width integer types in the standard library header `#include <cstdint>`:

| Type | Size | Range | Equivalent Python Concept |
| :--- | :--- | :--- | :--- |
| `std::int8_t` | 1 byte (8 bits) | $-128$ to $127$ | Signed byte |
| `std::uint8_t` | 1 byte (8 bits) | $0$ to $255$ | Unsigned byte (`bytes([x])`) |
| `std::int16_t` | 2 bytes (16 bits) | $-32,768$ to $32,767$ | 16-bit signed integer |
| `std::uint16_t` | 2 bytes (16 bits) | $0$ to $65,535$ | 16-bit unsigned integer |
| `std::int32_t` | 4 bytes (32 bits) | $\approx -2.14 \times 10^9$ to $2.14 \times 10^9$ | 32-bit signed integer |
| `std::uint32_t` | 4 bytes (32 bits) | $0$ to $\approx 4.29 \times 10^9$ | 32-bit unsigned integer |
| `std::int64_t` | 8 bytes (64 bits) | $\approx -9.22 \times 10^{18}$ to $9.22 \times 10^{18}$ | 64-bit signed integer |
| `std::uint64_t` | 8 bytes (64 bits) | $0$ to $\approx 1.84 \times 10^{19}$ | 64-bit unsigned integer |
| `std::size_t` | 8 bytes (on 64-bit OS) | $0$ to $2^{64}-1$ | Unsigned type for sizes and indexing (from `<cstddef>`) |

### The `uint8_t` / `int8_t` Printing Gotcha:
In GCC and Clang, `std::uint8_t` is defined as a `typedef` for `unsigned char`.
Because `std::cout` inspects the type at compile time:
- `std::cout << val;` attempts to print it as an **ASCII character**, not a number.
- To display it as an integer, you must promote/cast it:
  ```cpp
  std::cout << static_cast<int>(val); // prints as a number
  // or unary plus promotion:
  std::cout << +val;                  // promotes to int before printing
  ```

---

## 2. Integer Overflow: Unsigned vs. Signed

### Unsigned Overflow = Well-Defined Modular Wraparound
The C++ standard defines unsigned arithmetic as modulo $2^N$ (where $N$ is the number of bits).
- For `std::uint8_t`, the range is $0$ to $255$.
- $255 + 1 \implies 0$ (wraps around).
- $0 - 1 \implies 255$.

### Signed Overflow = Undefined Behavior (UB)
- If a signed integer (`int`, `std::int32_t`, etc.) exceeds its maximum positive limit (e.g., $2^{31}-1$), the behavior is **undefined**.
- The C++ standard makes no guarantees: it does NOT wrap around reliably!
- The compiler is allowed to assume signed overflow *never happens* and may eliminate checks, produce incorrect code, or cause crashes.

---

## 3. Arithmetic Operators & Python Differences

C++ provides standard arithmetic operators: `+`, `-`, `*`, `/`, `%`.

### The Critical Python vs. C++ Difference: Division and Modulo with Negatives

| Expression | Python Result | C++ Result | Explanation |
| :--- | :--- | :--- | :--- |
| `-7 / 2` (or `-7 // 2`) | `-4` (in Python `//`) | `-3` | **Python** floors toward $-\infty$.<br>**C++** truncates toward zero ($0$). |
| `-7 % 3` | `2` | `-1` | **Python** `%` takes the sign of the divisor (denominator).<br>**C++** `%` takes the sign of the dividend (numerator). |
| `7 % -3` | `-2` | `1` | In C++, `a % b` formula satisfies: `(a / b) * b + (a % b) == a`. |

> Note: In C++, the `%` operator works **only** on integral types (`int`, `char`, `long`), never on `double` or `float`. (For floats, `<cmath>` provides `std::fmod`).

---

## 4. Increment and Decrement: Pre vs. Post

Both modify the variable by adding or subtracting 1, but their return value in an expression differs:

| Operator | Syntax | Name | Behavior in an Expression |
| :--- | :--- | :--- | :--- |
| Pre-increment | `++x` | Prefix | Increments `x` first, then returns the **new** value of `x`. |
| Post-increment | `x++` | Postfix | Returns a copy of the **old** value of `x`, then increments `x`. |

```cpp
int a{5};
int b = ++a; // a becomes 6, b is 6 (pre-increment)

int x{5};
int y = x++; // x becomes 6, y is 5 (post-increment)
```

In idiomatic C++, **prefer `++x` (pre-increment)** unless you specifically need the old value. Pre-increment is more direct and avoids unnecessary copies.

---

## 5. Comparison and Logical Operators

### Comparison Operators:
`==` (equal), `!=` (not equal), `<` (less than), `<=` (less or equal), `>` (greater than), `>=` (greater or equal).
- Return type is `bool` (`true` or `false`).
- To print `true`/`false` as words rather than `1`/`0`, use `std::cout << std::boolalpha;`.

### Logical Operators:
- `&&` (Logical AND) - Equivalent to Python's `and`.
- `||` (Logical OR) - Equivalent to Python's `or`.
- `!` (Logical NOT) - Equivalent to Python's `not`.

### Short-Circuit Evaluation:
Just like Python:
- For `A && B`: If `A` is `false`, `B` is **not** evaluated.
- For `A || B`: If `A` is `true`, `B` is **not** evaluated.

