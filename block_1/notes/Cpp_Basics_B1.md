# C++ Systems Programming Notes (Phase 3: Block 1)

My personal notebook, mental models, and cheat sheets as I transition from Python logic to low-level C++.

---

## 1. Quick Compiler & Tooling Cheat Sheet

- **Standard Build Command:**
  ```bash
  g++ -std=c++20 -Wall -Wextra <file.cpp> -o <binary_name>
  ```
- **Flag Glossary:**
  - `-std=c++20`: Enforces ISO C++20 standard.
  - `-Wall`: Turns on all standard warning diagnostics.
  - `-Wextra`: Turns on extra compiler diagnostics.
  - `-c`: Compiles and assembles to object file (`.o`), stops before linking.
  - `-o <name>`: Names the generated executable.

- **Compilation Pipeline:**
  1. `Preprocessing` (`#include`, text replacement)
  2. `Compilation` (C++ to architecture assembly `.s`)
  3. `Assembly` (Assembly to unlinked machine code `.o`)
  4. `Linking` (Stitches `.o` files with standard runtime/libraries into executable)

---

## 2. What Actually Clicked: Python to C++ Mental Shift

### 2.1 The Core Execution & Machine Model
- **Output:** `<<` pushes data to stream; no auto-newline like in Python.
  - **Python Equivalent `print()`:** `print("Hello")`
  - *Syntax:*
    ```cpp
    std::cout << "Hello\n";
    ```
- **Input:** `>>` extracts and converts directly to variable type bcz the data type is predefined. NOTE: cin automatically skips the leading whitespace so `10 20` is equivalent to `10` enter `20`.
  - **Python Equivalent `input()`:** `x = int(input())`
  - *Syntax:*
    ```cpp
    int x{};
    std::cin >> x;
    ```
- **Blocks:** In cpp whitespace is ignored by the compiler.
  - **Python Equivalent Blocks:** 4-space indentation with `:`
  - *Syntax:*
    ```cpp
    {
        // statements
    }
    ```
- **Statements:** Semicolon `;` terminated. Every expression statement requires `;`.
  - **Python Equivalent Statements:** Newline terminated.
- **Typing:** Static. Type is fixed at compile-time; memory is allocated directly.
  - **Python Equivalent Typing:** Dynamic (`x = 5`).
  - *Syntax:*
    ```cpp
    int x{5};
    ```
- **Quotes:** In cpp `'` and `"` are different data types. `'` are char while `"` are string. In cpp char data type is a single character (1 byte), eg, `'2'`, `'4'`, `'Z'`, etc. While strings are a sequence/array of multiple characters.
  - **Python Equivalent Quotes:** Both `'` and `"` are same data type, ie, string (`'hello'` == `"hello"`).

### 2.2 Variables, Immutability, Data Types & Fixed-Width Integers
- **Variable initialisation:** Static and several methods to assign. In Modern C++ `{}` brace initialization is prevalent bcz it raises a compile time error if the value inside it doesnt match the data type defined. Like `int x = 4.8;` truncated 4.8 to 4; while `int x{4.9};` raises a compile time error to tell to change the value or data type.
  - **Python Equivalent Initialization:** Dynamic, done through assignment operator (`x = 5`).
  - *Syntax:*
    ```cpp
    int x{5};   // direct brace init
    int y{};    // value init (0)
    ```

- **Constants:** Enforced through two ways:
  - **`const`**: Runtime or compile time constant. Once initialized, it can never change. You can initialise it form inputs like cin.
  - **`constexpr`**: Compile time constant. Must be defined before the compilation occurs.
  - **Python Equivalent Constants:** No run time compulsion, only practice/convention (`PI = 3.14`).
  - *Syntax:*
    ```cpp
    constexpr int gravity{10};
    const int user_choice{input};
    ```

- **Data Types:** Fixed with a wide variety and can be used according to the use.

- **Fixed Width integer:** It provides exact bit (byte) size for different integers, so that least memory is wasted. In windows and linux the default size for a data type can change (`long` is 32 bits on windows, 64 on linux). To prevent this, C++ provides exact-size types via `#include <cstdint>`:
  - `std::int8_t` / `std::uint8_t` (1 byte, 8 bits)
  - `std::int16_t` / `std::uint16_t` (2 bytes, 16 bits)
  - `std::int32_t` / `std::uint32_t` (4 bytes, 32 bits)
  - `std::int64_t` / `std::uint64_t` (8 bytes, 64 bits)  
  *(u means unsigned, positive numbers only)*
  - **Python Equivalent:** No such thing (Python ints have arbitrary precision).

### 2.3 Integer Overflow
- **Overflow:** It is of two types:
  1. **Unsigned Overflow (for unsigned integer) [Well defined]:** cpp just performs modulo $2^N$. For `std::uint8_t` (range $0$ to $255$), $255 + 1$ is guaranteed to wrap around to $0$.
  2. **Signed overflow (for signed integers) [Undefined behaviour]:** If a signed overflow occurs then there is no guarantee; the program might crash, produce garbage, or compiler's optimizer might erase your safety checks assuming overflow "is impossible".
  - **Python Equivalent Overflow:** Doesn't happen (Python automatically expands integers).

### 2.4 Division, Modulo, Increment Operators
- **Arithmetic Operators:** A slight difference in division (`/`) and modulo (`%`):
  - C++ integer division `/` **truncates toward zero** (discards fractional part). So `-7 / 2` evaluates to `-3` (in Python `int(-7 / 2)`).
  - C++ modulo `%` takes the **sign of the dividend** (the left-hand side / numerator). So `-7 % 3` is `-1`.
  - **Formula Modulo:**  
    $$dividend = \left(\frac{dividend}{divisor}\right) \cdot divisor + (dividend \pmod{divisor})$$
  - **Python Equivalent Division/Modulo:** Python's `//` floors toward negative infinity (`-7 // 2` is `-4`), and Python's `%` takes the sign of the divisor (`-7 % 3` is `2`).

- **Increment Operators:** Two types: pre-increment (`++x`) and post-increment (`x++`). When used as a standalone statement, `++x;` and `x++;` do the same thing: add 1. However, **inside an expression, their return values differ**:
  - `++x` **(Prefix):** Increments first, then returns the new value.
  - `x++` **(Postfix):** Increments, but returns a copy of the old value.
  - **Python Equivalent:** No direct ones available (we use `x += 1`).
  - *Example:*
    ```cpp
    int a{5};
    int b = ++a; // a is 6, b is 6
    int c = a++; // a is 7, c is 6
    ```

### 2.5 Conditionals & Switch Case
- **Conditionals:** In cpp we have `if`, `else if`, and `else`, and the boolean expression must be enclosed in parentheses `(...)`, and in place of `:` & indentation we have curly brackets `{...}` in which the body for each block is present.
  - **Python Equivalent Conditionals:** `if-elif-else`, where the boolean expression is open, and for the body of `if`/`elif`/`else` we use `:` and indentation.
  - *Example:*
    ```cpp
    if (x > 0) {
        std::cout << "Positive\n";
    } else if (x < 0) {
        std::cout << "Negative\n";
    } else {
        std::cout << "Zero\n";
    }
    ```
- **Switch Case:** It can save you time in place of long if-else if-else chains, **but only for integral values (int, long, char, bool, enum)**. The compiler can optimize this using jump tables or branch trees.  
  > ***The `break;` line must be present otherwise, the execution will fall in the next case regardless of whether the label matches or not!***
  - **Python Equivalent Switch:** `match / case` (added in Python 3.10, does not fall through).
  - *Example:*
    ```cpp
    switch (val) {
        case 1:
            std::cout << "One\n";
            break;  // WITHOUT 'break', execution falls right into case 2!
        case 2:
            std::cout << "Two\n";
            break;
        default:
            std::cout << "Other\n";
            break;
    }
    ```

### 2.6 Loops: `for`, `while`, `do-while` & Control
- **Loops:** 3 types in C++:
  1. **`for`**: When range or count is known. Consists of three parts separated by semicolons: `for (initialization; condition; increment)`.
  2. **`while`**: Based on a condition, if false then don't execute.
  3. **`do-while`**: Also based on condition but will execute at least one time. Has a necessary semicolon at the end!
  - **Python Equivalent Loops:** 2 types: `for` and `while`.
  - *Example:*
    ```cpp
    // For Loop
    for (int i{0}; i < 5; ++i) {
        std::cout << i << '\n';
    }

    // While Loop
    int i{0};
    while (i < 5) {
        std::cout << i << '\n';
        ++i;
    }

    // Do-While Loop (runs at least once)
    int choice{0};
    do {
        std::cout << "Enter positive number: ";
        std::cin >> choice;
    } while (choice <= 0); // Semicolon required!
    ```
- **Break & Continue:** Exactly as Python with a slight change in continue:
  - `break;`: Terminates the innermost loop or switch immediately.
  - `continue;`: Moves directly to the end of the loop body. *In a `for` loop, `continue` jumps to the increment statement (`++i`) before re-evaluating the condition.*
  - **Python Equivalent:** `break` and `continue`.

---

## 3. Personal Gotchas & "Aha!" Moments

- **Gotcha 1:** On Linux GCC, `std::uint8_t` is defined under the hood as `unsigned char`. If you pass it directly to `std::cout`, it **treats it as a character glyph (ASCII)** rather than a number:
  ```cpp
  // Syntax snippet: casting a byte to display as a number
  #include <cstdint>
  #include <iostream>

  std::uint8_t byte_val{65};
  std::cout << byte_val << '\n';                    // Prints 'A' (ASCII 65)
  std::cout << static_cast<int>(byte_val) << '\n';  // Prints 65 (numeric)
  std::cout << +byte_val << '\n';                   // Prints 65 (unary + promotion)
  ```

- **Gotcha 2:** Pre and Post Increment Operators, they are best explained by an example as given below: (Understand both, but make a habit of using mostly one type)
  ```cpp
  int a{5};
  int b = ++a; // a is 6, b is 6
  int c = a++; // a is 7, c is 6
  ```

---

## 4. C++ Jargon & Symbols Glossary

- `::` (Scope Resolution Operator): Tells the compiler which namespace or class to look inside (e.g., `std::cout`).
- `<<` (Stream Insertion): Data flows left into the stream.
- `>>` (Stream Extraction): Data flows right into the variable.
- `\n` vs `std::endl`: Prefer `\n`; `std::endl` forces an expensive buffer flush.
