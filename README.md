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

## 2. Python $\rightarrow$ C++ Mental Mapping

| Concept | Python | C++ | My Notes / Differences |
| :--- | :--- | :--- | :--- |
| **Output** | `print("Hello")` | `std::cout << "Hello\n";` | `<<` pushes data to stream; no auto-newline |
| **Input** | `x = int(input())` | `int x{}; std::cin >> x;` | `>>` extracts and converts directly to variable type bcz the data type is predefine. NOTE: cin automatically skips the leading whitespace so `10 20` is equivalent to `10` enter `20`  |
| **Blocks** | 4-space indentation | `{ ... }` curly braces | Whitespace is ignored by the compiler |
| **Statements** | Newline terminated | Semicolon `;` terminated | Every expression statement requires `;` |
| **Typing** | Dynamic (`x = 5`) | Static (`int x{5};`) | Type is fixed at compile-time; memory is allocated |
|**Quotes**|Both ', " are same ata stype, ie, string|In cpp ', " are different data types. ' are char while " are string|In cpp char data type is a single character (1 byte), eg, '2', '4', 'Z', etc. While strings are a sequence/array of multiple characters|
|Variable initialisation|Dynamic, and dnt thorugh assignmkent operator|Static and several methods to assign. Modern C++ {}|The {} is prevelant bcz it raises compile time error if the value inside it doesnt match the data type defined. Like int x = 4.8 truncated 4.9 to 4; while int x{4.9}raises a compile time error to tell to change the value or data type|
|Constants|No run time compulsion, only practice (PI = .14)|Enforced through two ways: const and constexpr|<br>**const**: Runtime or compile time constant. Once initialized, it can never change.You can initalise it form inputs like cin. <br>**constexpr**: Compile time constant. Must be defined before the conpilation occurs. <br> `constexpr int gravity{10};`<br> `user_choice{input};` |
|Data Types|Fixed but not very good|Also fixed but a wide variety and can be used accordingnnto the use| Refer to [Variable Types](/notes/03_variables_types_and_const.md#L51)|
|**Fixed Width integer**|No such thing|It provides exact bit (byte) size for different integers, so that least memory is wasted. In windows and linux the default size for a data type can change (long, 32 bits on windows, 64 on linux).| To prevent this, C++ provides exact-size types via `#include <cstdint>`: <br> - `std::int8_t` / `std::uint8_t` (1 byte, 8 bits) <br> - `std::int16_t` / `std::uint16_t` (2 bytes, 16 bits) <br> - `std::int32_t` / `std::uint32_t` (4 bytes, 32 bits) <br> - `std::int64_t` / `std::uint64_t` (8 bytes, 64 bits) <br>(u means unsigned, positive numbers only)|
|Overflow|Doesnt happen (can but very rare)|It is of two types, <br>1. Unsigned Overflow (for unsigned integer)[Well defined]<br>2.Signed overflow (for signed intgers) [Undefined behaviour]|For unsigned overflow/wraparound, cpp just performs modulo ${2}^{N}$. For `std::uint8_t` (range $0$ to $255$), $255+1$ is guaranteed to wrap around to $0$.<br>If a signed overflow occurs thne there is not garuntte, the programmight crash, produce garbage, or compiler's optimizer might erase your safety checks assuming overflow "is impossible".|
|**Arithmetic Operators**|AS yOU HAVE STUDIED|A slight difference in division(`/`) and modulo (`%`)|C++ integer division `/` **truncates toward zero** (discards fractional part). So `-7 / 3` is `-2` (line int(-7 / 2)) in python.<br>C++ modulo `%` takes the **sign of the dividend** (the left-hand side / numerator). So `-7 % 3` is -`1`.|
|**Formula Garunteed for Modulo**|Check Python|$`dividend=\frac{dividend}{divisor}\cdot divisor + {dividend}%{divisor}`$|See the above point|
|**Increment Operators**|No direct ones available|Two types, pre-increment (`++x`) and post increment (`x++`)|When used as a standalone statement, `++x`; and `x++`; do the same thing: add 1. However, **inside an expression, their return values differ**:<br>`++x` **(Prefix)**: Increments first, then returns the new value.<br>`x++` **(Postfix)**: Increments, but returns a copy of the old value.,br. Refer to [Gotcha 2](/README.md#L63) for an example|
|**s**|s|s|s|
|**s**|s|s|s|
|**s**|s|s|s|


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
  ```

- **Gotcha 2:** Pre and Post Increment Operators, they are best expained by an example as given below:  (Understand both, but make a habit of using mostly one type)
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