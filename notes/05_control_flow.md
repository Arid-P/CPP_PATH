# 05. Control Flow: Conditionals and Loops (CPP-07)

## 1. Conditionals: `if`, `else if`, `else`

In Python, blocks are defined by indentation with `:` and keywords `elif`/`else`.
In C++, conditions must be parenthesized `(...)`, and blocks are enclosed in curly braces `{ ... }`.

```cpp
if (x > 0) {
    std::cout << "Positive\n";
} else if (x < 0) {
    std::cout << "Negative\n";
} else {
    std::cout << "Zero\n";
}
```

### Python vs C++ Comparison:
| Feature | Python | C++ |
| :--- | :--- | :--- |
| Block syntax | `:` + 4-space indentation | `{ ... }` curly braces |
| Else if | `elif condition:` | `else if (condition) {` |
| Boolean conditions | Any truthy value (e.g. `if x:`) | Evaluates truthiness (`0` is false, non-zero is true), but prefer explicit `bool` |
| Variable scope in `if` (C++17) | Global/function scope | `if (int x{get_val()}; x > 0) { ... }` (scoped strictly to the if/else block!) |

---

## 2. The `switch` Statement and the Fallthrough Trap

`switch` tests a single integral value (or `enum`/`char`, but **not** `double` or `std::string`) against constant compile-time labels.

```cpp
switch (choice) {
    case 1:
        std::cout << "Option 1\n";
        break; // Mandatory to prevent fallthrough!
    case 2:
        std::cout << "Option 2\n";
        break;
    default:
        std::cout << "Unknown choice\n";
        break;
}
```

### The Fallthrough Trap:
In C++, if you omit `break;` at the end of a `case`, execution **falls through** into the next case, executing its statements even if the next case label doesn't match!
- In modern C++ (C++17/C++20), if fallthrough is intentional, use the attribute `[[fallthrough]];` to silence compiler warnings (`-Wimplicit-fallthrough`).
- Python added `match/case` in Python 3.10, but Python's `match` does **not** fall through. In C++, fallthrough is the default unless stopped by `break;`.

---

## 3. Loops: `while`, `do-while`, `for`

### `while` Loop:
Evaluates condition before each iteration.
```cpp
int i{0};
while (i < 5) {
    // loop body
    ++i;
}
```

### `do-while` Loop:
Evaluates condition **after** each iteration. The body is **guaranteed to run at least once**.
Notice the **mandatory semicolon `;`** at the very end:
```cpp
int choice{0};
do {
    std::cout << "Enter positive number: ";
    std::cin >> choice;
} while (choice <= 0); // Semicolon required!
```

### `for` Loop:
Consists of three parts separated by semicolons: `for (initialization; condition; increment)`:
```cpp
for (int i{0}; i < 5; ++i) {
    std::cout << i << '\n';
}
```
- Variables defined in initialization (like `int i{0}`) are strictly scoped to the loop!
- Unlike Python's `for i in range(5):` (which requires Python `range` iterator objects), C++'s `for` loop is a direct, zero-overhead machine instruction jumping with counter registers.

---

## 4. Loop Control: `break` and `continue`

Both work identically to Python:
- `break;`: Terminates the innermost loop or `switch` immediately.
- `continue;`: Jumps directly to the end of the loop body. In a `for` loop, `continue` jumps to the **increment statement** (`++i`) before re-evaluating the condition.

