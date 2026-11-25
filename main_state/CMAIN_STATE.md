# CMAIN Rolling State & Track Audit

**Track:** Phase 3 (C++, Electronics, Digital Logic, Embedded Simulation, Systems)  
**Role:** `cmain` (Central Planner, Auditor, and Curriculum Architect)  
**Current Date:** 2026-11-25  
**Current Pointer:** Phase 3 Block 1, Checkpoint P3-5 (Entry gate: Signed-overflow defect fixes)

---

## 1. Verified Track Baseline

- **Logged Hours:** 6.0 hrs total (Chat 1: 2.0 h | Chat 2: 4.0 h; ~1.5 h/checkpoint vs 2.0 h planned).
- **Atoms Achieved [x]:**
  - `CPP-01`: Toolchain, compilation stages, manual link with `g++ -c`.
  - `CPP-02`: Program structure, `main()`, `std::cin`/`std::cout`, cold-write sum.
  - `CPP-03`: Brace initialization `{}`, narrowing prevention, naming.
  - `CPP-05`: `const` runtime immutability vs `constexpr` compile-time evaluation.
  - `CPP-06`: Arithmetic operators, division truncation toward zero, dividend-signed modulo, increment operators.
  - `CPP-07`: Control flow (`if/else`, `switch` fallthrough, `for`, `while`, `do-while`, `break`, `continue`).
- **Atoms Partial [~]:**
  - `CPP-04`: Fundamental & fixed-width types. Held at partial until real-world signed overflow defects are fixed and the 2-statement retest passes.
- **Verification Score:** 28 / 28 first-pass atomic statements clean (100%).
- **Mini-Check (12 statements):** 10 clean, 1 wrong (#4: signed vs unsigned comparison implicitly converts signed to unsigned, which can cause `-1 > 1u` to evaluate to true), 1 partial (#12: unary `+` promotes `uint8_t` to `int` for stream printing).

---

## 2. Real-World Defect Audit (Verified Live with `-fsanitize=undefined -g`)

All defects flagged by the Claude planner were verified directly in the terminal by compiling with `g++ -std=c++20 -Wall -Wextra -fsanitize=undefined -g`:

1. **`block_1/src/p12_gcd_lcm.cpp`**:
   - `(100000, 100000)`: Triggers `runtime error: signed integer overflow: 100000 * 100000 cannot be represented in type 'int'`. Returns `14100` instead of `100000`.
   - `(0, 0)`: Triggers `runtime error: division by zero` and crashes with `Floating point exception (core dumped)`.
   - `(-4, 6)`: Returns GCD `6`, LCM `-4`. The Python original rejected non-positive inputs; the C++ port dropped this check.
2. **`block_1/src/p02_prime_check.cpp`**:
   - `2147483647`: Triggers `runtime error: signed integer overflow: 46341 * 46341 cannot be represented in type 'int'`. Causes infinite execution or wrong composite classification.
   - `is_prime(0)`, `is_prime(1)`, `is_prime(-5)`: If called directly, returns `true` because the function only checks `n == 2` and loop `d * d <= n`. The function relies on `main()` for input sanitation instead of being correct on its own.
3. **`block_1/src/p09_fibonacci_series.cpp`**:
   - `first_n_terms(48)`: Triggers `runtime error: signed integer overflow: 1836311903 + 1134903170 cannot be represented in type 'int'` and prints negative numbers (`-1323752223`).
   - `terms_upto_m(2147483647)`: Overflow wraps `a` to negative, causing an **infinite loop** that spews numbers indefinitely.

---

## 3. Scope, Rules & Architectural Decisions

1. **Teacher vs Planner Separation:**
   - Sub-chats (Teacher bots) teach, quiz, guide, and debug *with* the learner.
   - Teacher bots **never write code in `block_1/src/`**.
   - Planner (`cmain`) audits evidence, verifies compilation/sanitizers, maintains track pacing, and keeps cross-chat state synchronized.
2. **Scope Boundary Enforcement:**
   - **Pass-by-reference (`&`) belongs strictly in Block 2 (`CPP-14`).** P3-5 covers **pass-by-value only**, functions in-depth, stack frame mechanics, and porting `p13`.
3. **Workspace Organization:**
   - `block_1/src/`: Hand-written C++ source files.
   - `block_1/python_reference/`: CBSE Class 11 reference scripts.
   - `block_1/notes/`: Conceptual student notes (`Cpp_Basics_B1.md`, etc.).
   - `ai_logs_nrest/`: Coordination logs (`SESSION_STATE.md`, `qna_and_verification_bank.md`, reports).
   - `main_state/`: `CMAIN_STATE.md` (this rolling audit file).

---

## 4. Immediate Roadmap (Block 1 Part A Completion)

- **Chat 3 (P3-5 & P3-6):**
  - **Fix First (~30–45 mins):** Learner writes fixes for `p12`, `p02`, `p09`. Verify under `-fsanitize=undefined`. Pass CPP-04 retest. Mark `CPP-04` [x].
  - **P3-5:** CPP-08 Part 1 (function prototypes vs definitions, pass-by-value, stack frames), port `p13_factorial_permutations.cpp` (investigate 20! vs 21! 64-bit overflow), differential test (`diff -u`). Verification statements.
  - **P3-6:** CPP-08 Part 2 (headers `.h`, source `.cpp`, include guards, multi-file compilation, 10-line `Makefile`), CPP-09 (storage duration, linkage, `static` locals). Cold-write: 2-function library split.
- **Chat 4 (P3-7 & Part A Wrap-Up):**
  - `CPP-10` (Arrays, `std::array`, `std::vector`), `CPP-11` (`std::string`), Ports `p06`, `p14`, `p18`. Part A wrap-up.
- **Deferred to Apr–Jun 2027:**
  - `CPP-12` (File I/O), `CPP-13` (GDB), `DG-02/03/06`, `EM-01`, `SIM-01`, `SD-01`, Build 1.
  - C++ track paused Jan–Mar 2027 for CBSE Class 12 preparation.
