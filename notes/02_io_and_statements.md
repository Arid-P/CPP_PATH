# 02. Statements and Standard I/O (`std::cout`, `std::cin`)

## 1. Output with `std::cout` and the Insertion Operator `<<`

In C++, stream operators point in the direction of data flow:

```cpp
std::cout << "Data flows to cout";
```
- The arrows point **left** towards `std::cout`—you are inserting data into the console output stream.
- You can chain insertions:
  ```cpp
  std::cout << "Sum: " << (a + b) << '\n';
  ```

---

## 2. Input with `std::cin` and the Extraction Operator `>>`

In Python:
```python
x = int(input("Enter number: "))
```
- In Python, `input()` always returns a string (`str`). You must explicitly convert it with `int()`.

In C++:
```cpp
int x;
std::cin >> x;
```
- `std::cin` ("Character Input", pronounced "see-in") is the stream object connected to `stdin`.
- `>>` is the **stream extraction operator**.
- The arrows point **right** into the variable—data is extracted *from* the terminal stream and poured *into* `x`.
- **Automatic Type Conversion:** Because `x` is declared as an `int`, `std::cin >> x` automatically parses characters as an integer.
- **Whitespace Skipping:** By default, `>>` automatically skips leading whitespace (spaces, tabs, newlines) until it encounters the first character of the number.
- **Chaining Input:**
  ```cpp
  int a;
  int b;
  std::cin >> a >> b;
  ```
  This single line reads both `a` and `b`, separated by any whitespace (spaces, tabs, or enters).

---

## 3. Python vs. C++ Comparison Table

| Concept | Python | C++ |
| :--- | :--- | :--- |
| **Output** | `print("Hello", x)` | `std::cout << "Hello " << x << '\n';` |
| **Input** | `x = int(input())` | `int x; std::cin >> x;` |
| **Two numbers** | `a, b = map(int, input().split())` | `int a; int b; std::cin >> a >> b;` |
| **Separator** | Python handles strings, splits on spaces | C++ `std::cin` splits on whitespace by default |



---

## 4. Single Quotes `'` vs. Double Quotes `"`

In Python, `'hello'` and `"hello"` are identical. In C++, they are completely different types:

| Literal | Syntax | Type | Example | Use Case |
| :--- | :--- | :--- | :--- | :--- |
| **Character Literal** | Single quotes `' '` | `char` (exactly 1 character/byte) | `'A'`, `'9'`, `'\n'` | Single characters, single delimiters |
| **String Literal** | Double quotes `" "` | Array of `const char` (`const char[]`) | `"Hello"`, `"A"`, `"123"` | Words, sentences, multiple characters |

- `'a'` is a single character (ASCII value 97).
- `"a"` is a string literal containing two bytes in memory: `'a'` and the null terminator `'\0'`.
- `'hello'` is invalid syntax in C++ (causes a compiler error or multi-character literal warning).

---

## 5. Linux Shell Execution: Why `./` is Required

In Linux, when you type a command (like `sum`), the shell searches only the directories listed in your `$PATH` environment variable (e.g. `/usr/bin`, `/bin`).
- There is already a built-in Linux utility at `/usr/bin/sum` that computes checksums and waits for stdin.
- The current working directory (`.`) is intentionally **not** in `$PATH` for security reasons.
- To execute a program in your current directory, you **must** tell the shell the path explicitly using `./`:
  ```bash
  ./sum                  # If you are inside block1_bits/
  ./block1_bits/sum      # If you are in the CPP_PATH root directory
  ```
