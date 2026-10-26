# 01. C++ Basics & The Compilation Model

## 1. Python vs. C++ Architecture

| Feature | Python | C++ |
| :--- | :--- | :--- |
| **Execution Model** | Interpreted / Bytecode VM | Compiled directly to native CPU machine code |
| **Entry Point** | Top-to-bottom script execution, or `if __name__ == '__main__':` | Mandatory function: `int main()` |
| **Typing** | Dynamic & Duck-typed | Static, strict, manifest typing (checked at compile time) |
| **Statements** | Delimited by newlines and indentation | Delimited by semicolons (`;`); whitespace is ignored |
| **Standard Library** | `import sys`, `import math` | `#include <iostream>`, `#include <vector>` |

---

## 2. The 4 Stages of Compilation

When you invoke `g++`, it orchestrates four distinct stages:

```
[hello.cpp] 
     │
     ▼ (1. Preprocessor: cpp)
[Preprocessed Source]   <- Expands #include, macros, strips comments
     │
     ▼ (2. Compiler: cc1plus)
[Assembly Code (.s)]    <- Translates C++ AST into CPU assembly instructions
     │
     ▼ (3. Assembler: as)
[Object File (.o)]      <- Machine code with unresolved symbols (unlinked)
     │
     ▼ (4. Linker: ld)
[Executable Binary]     <- Combines .o files + C++ Standard Library (libstdc++)
```

1. **Preprocessing (`cpp`)**: Directives starting with `#` are processed. `#include <iostream>` literally pastes the header declarations into your file.
2. **Compilation (`cc1plus`)**: Checks syntax, types, and semantics. Translates valid C++ into human-readable assembly language for your CPU architecture (e.g. x86_64).
3. **Assembly (`as`)**: Converts assembly language mnemonics into raw binary machine instructions, stored in an **Object file** (`.o`).
4. **Linking (`ld`)**: Stitches together one or more `.o` files with standard system libraries (resolves references like `std::cout`). Emits the runnable executable.

---

## 3. Dissecting `hello.cpp`

```cpp
#include <iostream>

int main() {
    std::cout << "Hello, World!\n";
    return 0;
}
```

- `#include <iostream>`:
  - **Python equivalent**: roughly `import sys`.
  - **In C++**: It includes the Standard Input/Output Stream header, providing declarations for `std::cout`, `std::cin`, and `std::cerr`.
- `int main()`:
  - **Python equivalent**: `def main(): ... if __name__ == "__main__": main()`
  - **In C++**: The mandatory operating system entry point. Every C++ program must have exactly one `main()`. It returns an `int` (integer) status code to the OS.
- `{ ... }`:
  - Encloses a block of code (replaces Python's 4-space indentation).
- `std::cout`:
  - `std`: Standard library **namespace** (prevents naming collisions).
  - `::`: **Scope resolution operator** ("look inside `std` for `cout`").
  - `cout`: "Character Output", the stream object representing standard output (stdout / terminal).
- `<<`:
  - **Stream insertion operator**. It takes whatever is on the right and feeds it into the stream on the left.
- `"\n"` vs `std::endl`:
  - `\n`: Inserts a newline character. (Fast, preferred).
  - `std::endl`: Inserts a newline *and* flushes the output buffer (slower, rarely needed).
- `;`:
  - Statement terminator. Every simple statement in C++ must end with a semicolon.
- `return 0;`:
  - Signals to the OS that the program finished successfully (exit status 0). Any non-zero value typically indicates an error.

---

## 4. Compiler Commands & Flags

### The Full Pipeline in One Command
```bash
g++ -std=c++20 -Wall -Wextra block1_bits/hello.cpp -o block1_bits/hello
```
- `g++`: The GNU C++ compiler driver command.
- `-std=c++20`: Enforce ISO C++20 standard rules and features.
- `-Wall`: Enables all common compiler warning diagnostics.
- `-Wextra`: Enables additional diagnostic warnings not covered by `-Wall`.
- `block1_bits/hello.cpp`: The source file to compile.
- `-o block1_bits/hello`: Specifies the output binary filename. (Without `-o`, the compiler defaults to creating a binary named `a.out`).

### The Two-Step Manual Compile & Link
```bash
# Step 1: Preprocess, Compile, and Assemble to an Object File (.o)
g++ -std=c++20 -Wall -Wextra -c block1_bits/hello.cpp -o block1_bits/hello.o

# Step 2: Link Object File into Final Executable Binary
g++ block1_bits/hello.o -o block1_bits/hello_manual
```
- `-c`: Flag telling `g++` to compile and assemble, but **stop before linking**.

