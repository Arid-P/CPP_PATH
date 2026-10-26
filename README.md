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

---

## 3. Personal Gotchas & "Aha!" Moments

None Yet

- **Gotcha 1:**
- **Gotcha 2:**

---

## 4. C++ Jargon & Symbols Glossary

- `::` (Scope Resolution Operator): Tells the compiler which namespace or class to look inside (e.g., `std::cout`).
- `<<` (Stream Insertion): Data flows left into the stream.
- `>>` (Stream Extraction): Data flows right into the variable.
- `\n` vs `std::endl`: Prefer `\n`; `std::endl` forces an expensive buffer flush.