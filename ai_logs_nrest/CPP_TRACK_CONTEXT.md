# C++ Track Master Context (Phase 3: Block 1 — Bits & Basics)

*Temporary handover & synchronization document between Chat 3.1.1, Chat 3.1.2, Chat 3.1.3, Chat 3.1.4, and the upcoming `cmain` coordinator chat.*

---

## 1. Architectural Scope & Track Identity

- **Track Hierarchy:**
  - **Phase 3:** C++, Electronics, Digital Logic, Embedded (Simulated), Systems Programming.
  - **Block 1:** Bits & Basics (~45 hours total: light start Oct–Dec 2026 ~13h, resumption Apr–Jun 2027 ~32h).
  - **Pacing:** Block 1 C++ Atoms (CPP-01 through CPP-13) are split across **4 Chats**:
    - **3.1.1 (Chat 1):** Checkpoints P3-1 & P3-2 (CPP-01, 02, 03, 04 pt 1, 05) — **Completed** (2.0 hrs)
    - **3.1.2 (Chat 2):** Checkpoints P3-3 & P3-4 (CPP-04 pt 2, 06, 07; Ports p12, p02, p09) — **Completed** (4.0 hrs)
    - **3.1.3 (Chat 3):** Checkpoints P3-5 & P3-6 (Overflow hardening, CPP-08 Functions, headers/sources, Makefiles, CPP-09 Scope/lifetime; Port p13) — **Next**
    - **3.1.4 (Chat 4):** Checkpoints P3-7 (CPP-10 Arrays/vector, CPP-11 Strings, CPP-12 File I/O, CPP-13 GDB; Ports p14, p06, p18) — **Upcoming**
- **Repository Setup:**
  - Workspace root: `/home/hp/Programing-Workspace/CPP_PATH/` (its own independent git repo).
  - Working code directory: `block1_bits/`
  - Reference Python programs: `block1_bits/python_reference/` (CBSE Class 11 lab programs).
  - Documentation:
    - Teacher notes: `notes/01_...` to `notes/05_...`
    - Student personal cheat sheet: `README.md`
    - Session tracking: `SESSION_STATE.md`
    - Verbatim verification logs: `qna_and_verification_bank.md`
    - Session reports: `report/chat_01_report.md`, `report/chat_02_report.md`
  - Toolchain: Ubuntu Linux, `g++ 15.2.0`, standard flags `-std=c++20 -Wall -Wextra`.

---

## 2. Learner Profile & Hard Pedagogical Rules

1. **Student Baseline:** Strong Python logic (loops, functions, lists/dicts, CBSE practicals, easy-medium LeetCode). Weak on C++ boilerplate, toolchains, memory boundaries. Zero C/C++ background prior to Chat 1.
2. **Teaching Rules:**
   - Teacher explains, quizzes, and debugs *with* the learner.
   - **Teacher NEVER writes student code** in `block1_bits/` unless explicitly commanded. Tiny syntax examples ($\le 5$ lines) only when stuck.
   - Every compilation warning from `-Wall -Wextra` must be addressed or explained.
   - Use explicit `std::` prefixes (strict ban on `using namespace std;`).
   - All C++ ports must run differential tests against Python originals on shared input files (`diff -u`).
3. **Verification & Evidence Standard:**
   - After each checkpoint: **6–8 atomic True/False statements** (subtle falses, answer key hidden until answered).
   - Student answers recorded **VERBATIM** in `qna_and_verification_bank.md`.
   - Graded strictly as Correct / Partial / Incorrect (no "mostly correct").
   - Cold-writes: 10 minutes, blank file, no notes/AI; student pastes real code and terminal output.
   - Conventional Commits (`feat(cpp): ...`, `docs: ...`, `refactor: ...`) in small logical chunks.

---

## 3. Detailed Progress & Completed Atoms (Chats 1 & 2)

### Chat 1 (3.1.1): P3-1 & P3-2 (2.0 hrs)
- **CPP-01 (Toolchain):** 4-stage pipeline (Preprocessing, Compilation, Assembly, Linking); manual build with `g++ -c hello.cpp -o hello.o` and `g++ hello.o -o hello`.
- **CPP-02 (Basic Structure & I/O):** `main()`, statements, `#include <iostream>`, `std::cout`, `std::cin`, `\n`. Cold-write: `sum.cpp`. (Verification: 7/7).
- **CPP-03 (Variables & Initialization):** Garbage memory vs brace initialization (`{}` prevents narrowing conversions like `int x{4.9}`).
- **CPP-04 Part 1 (Fundamental Types & Sizes):** `bool` (1B), `char` (1B, stores ASCII code), `int` (4B), `unsigned int` (4B), `double` (8B), `sizeof` hardware queries, `static_cast<int>(c)`.
- **CPP-05 (Immutability):** Runtime `const` vs compile-time `constexpr`. (Verification: 7/7).
- **Key Struggles, Quirks & Breakthroughs (Chat 1):**
  - *Linux `$PATH` & `./` Execution Trap:* Typing `sum` directly in bash triggered the system utility `/usr/bin/sum` (GNU checksum tool) which silently hung waiting for stdin. Mastered why `.` is excluded from `$PATH` and why `./sum` or `./block1_bits/sum` is mandatory.
  - *Quoting Semantics (`'` vs `"`):* Encountered syntax error using single quotes for strings; learned `' '` is strictly a 1-byte `char` (integer ASCII), whereas `" "` is a null-terminated string literal (`const char[]`).
  - *Linker Mental Model:* Transitioned from guessing "hardware variations" to understanding modular/separate compilation (recompiling 1 changed `.cpp` $\to$ `.o` without rebuilding the entire project) and linking precompiled libraries (`libstdc++`).
  - *Narrowing Enforcement:* Witnessed hard compile error on `int x{4.9}` (`-Wnarrowing`), contrasting with C-style silent truncation (`int x = 4.9`).
  - *Git & Linux Binaries:* Because Linux binaries have no extension (`hello`, `sum`), updated `.gitignore` to filter binaries while keeping `.cpp`, `.h`, `.md`, and Python references.

### Chat 2 (3.1.2): P3-3 & P3-4 (4.0 hrs)
- **CPP-04 Part 2 (Fixed-Width Types & Overflow):**
  - `<cstdint>` fixed-width types: `std::uint8_t`, `std::int32_t`, `std::uint64_t`.
  - Unsigned overflow = well-defined modular wraparound ($255 + 1 \implies 0$). Tested in `overflow_demo.cpp`.
  - Signed overflow = **Undefined Behavior (UB)**.
  - `uint8_t` stream gotcha: aliased to `unsigned char`, prints glyph unless promoted with `static_cast<int>` or unary `+`.
- **CPP-06 (Operators & Expressions):**
  - C++ integer division truncates toward zero (`-7 / 3 == -2`; `-7 / 2 == -3`).
  - C++ modulo takes sign of dividend (`-7 % 3 == -1`; `134 % -6 == 2`). Formula: `(a/b)*b + (a%b) == a`.
  - Prefix `++x` (increments and returns new value; preferred) vs postfix `x++` (returns old value).
  - Logical operators `&&`, `||`, `!` with short-circuit evaluation. (Verification: 7/7).
- **CPP-07 (Control Flow & Functions):**
  - `if`, `else if`, `else`, block scoping.
  - `switch`: restricted to integral types/enums for $O(1)$ jump-table dispatch; fallthrough trap and `break;`.
  - Loops: `for (int i{0}; i < n; ++i)` with loop-scoped variables, `while`, `do-while` (mandatory trailing `;`), `break`, `continue`.
  - Introduction to `void` return types (no return value, `return;` early exit, no `return 0;`).
- **Python Reference Ports & Cold-Write:**
  - `p12_gcd_lcm.cpp`: Euclid's algorithm using temporary swap variable; LCM computed via `(a * b) / gcd`. (Also satisfied P3-4 cold-write GCD requirement).
  - `p02_prime_check.cpp`: Prime verification with boundary fix `d * d <= n` to correctly catch perfect squares (`4`, `9`, `25`); handled `0`, `1`, negatives.
  - `p09_fibonacci_series.cpp`: Streaming Fibonacci sequence with $O(1)$ memory, formatting delimiter logic, boundary guards for $N$ and limit $M$. (Verification: 7/7).

---

## 4. Auditor / Planner Findings & Open Bug Backlog (CRITICAL for Chat 3)

The high-level roadmap auditor (`Journey_Docs/07_PROGRESS_LOG.md:86` & `00_START_HERE_MASTER.md:145`) reviewed the Chat 2 ports and identified three real-world **32-bit signed integer overflow vulnerabilities**:

1. **Bug 1: `p12_gcd_lcm.cpp`**
   - In `compute_lcm`: `(a * b) / gcd` will overflow 32-bit signed `int` if $a \times b > 2,147,483,647$ (e.g., $a = 60000, b = 60000$), causing undefined behavior before division!
   - *Fix:* Reorder operations to `(a / gcd) * b` or cast intermediate to `std::int64_t`.
   - Also handle $(0, 0)$ crash and non-positive inputs safely.
2. **Bug 2: `p02_prime_check.cpp`**
   - In `is_prime`: The condition `d * d <= n` overflows 32-bit `int` when `n` is large (e.g. `n = 2147483647`), causing `d * d` to wrap to negative numbers in signed overflow UB!
   - *Fix:* Use `d <= n / d` to prevent multiplication overflow entirely.
3. **Bug 3: `p09_fibonacci_series.cpp`**
   - The Fibonacci sequence exceeds 32-bit signed `int` ($2 \times 10^9$) at term $N = 47$ ($F_{46} = 1,836,311,903$, $F_{47} = 2,971,215,073$).
   - If user requests $N \ge 47$ or limit $M \ge 1,836,311,903$, `b += temp` invokes signed integer overflow UB or an infinite loop!
   - *Fix:* Use `std::int64_t` or cap inputs with descriptive warnings.
4. **Scope Correction for P3-5:**
   - Note: Pass-by-reference (`&`) belongs to **Block 2 (CPP-14)**! P3-5 in Block 1 focuses strictly on **Pass-by-value**, declaration vs definition, header files (`.h`), and multi-file builds.

---

## 5. Roadmap Ahead: Chat 3 (3.1.3) & Chat 4 (3.1.4)

### Chat 3 (3.1.3): Checkpoints P3-5 & P3-6
- **Checkpoint P3-5:**
  - Fix the 3 overflow bugs in `p12`, `p02`, `p09` and retest.
  - **CPP-08 Part 1:** Functions deep dive (declaration vs definition, signatures, parameters, pass-by-value semantics, call stack frames).
  - Port **`p13_factorial_permutations.py`** $\to$ `block1_bits/p13_factorial_permutations.cpp`.
- **Checkpoint P3-6:**
  - **CPP-08 Part 2:** Modular C++ projects: header files (`.h`/`.hpp`), source files (`.cpp`), header guards (`#ifndef` / `#pragma once`), multi-file compilation, and basic `Makefile`.
  - **CPP-09:** Scope, linkage, and storage duration (local vs global, `static` local variables).

### Chat 4 (3.1.4): Checkpoint P3-7 & Block 1 Wrap-Up
- **CPP-10:** Containers: C-style fixed arrays, `std::array`, and dynamic `std::vector` basics (`push_back`, indexing, `.size()`).
- **CPP-11:** Strings: `std::string`, operations, `.length()`, difference from C-strings (`const char*`).
- **Ports:** `p14_second_largest_in_list.py`, `p06_list_linear_search_min_max.py`, `p18_string_text_statistics.py`.
- **CPP-12:** File I/O stream basics (`<fstream>`, `std::ifstream`, `std::ofstream`).
- **CPP-13:** Debugging toolchain: `-Wall -Wextra`, print debugging, introductory `gdb` session (breakpoints, `run`, `next`, `print`).
- **Block 1 Final Audit:** Cumulative hours check, verification log closure, transition to Digital Logic / Circuit Simulator atoms.

---

## 6. Current Metrics Summary

- **Total Student Reported Hours:** **6.0 hrs** (Chat 1: 2.0 hrs, Chat 2: 4.0 hrs).
- **Total Q&A Score:** **28 / 28 (100% first-pass accuracy)** across P3-1, P3-2, P3-3, P3-4.
- **Git State:** 17 commits on `main`, zero warnings under `-Wall -Wextra`.
