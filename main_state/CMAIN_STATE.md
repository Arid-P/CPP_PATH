# CMAIN Master Rolling State

**File Version:** 1.0  
**Last Updated:** 2026-11-25  
**Owner:** `cmain` (Phase 3 Planner / Auditor)  
**Standard:** Governed by `~/Programing-Workspace/Journey_Docs/PLANNER_CHARTER.md` and `Journey_Docs/00_START_HERE_MASTER.md` §2.

---

## 1. Track Architecture & Current Pointer

- **Current Track Pointer:** Phase 3, Block 1 (Bits & Basics), Part A.
- **Chats Completed:** Chat 1 (P3-1 & P3-2), Chat 2 (P3-3 & P3-4).
- **Current Active Chat:** Ready to launch **Chat 3 of 4 (Checkpoints P3-5 & P3-6)**.
- **Logged Student Hours:** **6.0 hrs** total (Chat 1: 2.0 h, Chat 2: 4.0 h; ~1.5 h/checkpoint vs 2.0 h planned). Pace ~2 h/week.
- **Pause Schedule:** C++ pauses Jan–Mar 2027 for CBSE Class 12. Block 1 Part B (CPP-12, CPP-13 gdb, DG-02/03/06, EM-01, SIM-01, formal SD-01, Build 1) resumes Apr–Jun 2027.

---

## 2. Atoms Status & Evidence Ledger

| Atom ID | Description | Status | Evidence / Notes |
| :--- | :--- | :--- | :--- |
| **CPP-01** | Toolchain (preprocess, compile, assemble, link; `g++ -c`) | `[x]` Verified | Manual link verified, Q&A 7/7, 0 warnings. |
| **CPP-02** | Structure (`main()`, statements, `#include`, `cin`/`cout`) | `[x]` Verified | Cold-write sum passed, Q&A 7/7. |
| **CPP-03** | Variables, brace init `{}` (narrowing caught), naming | `[x]` Verified | Verification 7/7, types demo. |
| **CPP-04** | Types (`bool`, `char`, `int`, fixed-width `<cstdint>`, overflow) | `[~]` Partial | Unsigned wraparound verified. Blocked on 3 signed-overflow defect fixes & 2-statement retest (signed vs unsigned comparison, unary `+`). |
| **CPP-05** | Constants (`const` runtime vs `constexpr` compile-time) | `[x]` Verified | Verification 7/7. |
| **CPP-06** | Operators (truncating `/`, dividend `%`, `++x` vs `x++`, precedence) | `[x]` Verified | Verification 7/7, modulo formula. |
| **CPP-07** | Control flow (`if`, `switch` fallthrough, loops, `break`/`continue`) | `[x]` Verified | Verification 7/7, ports p12/p02/p09 built. |
| **CPP-08** | Functions (declaration/definition, pass-by-value, `.h`/`.cpp`, Makefile) | `[ ]` Pending | Target for Chat 3 (P3-5 Part 1, P3-6 Part 2). |
| **CPP-09** | Scope & lifetime (local, global, shadowing, `static` locals) | `[ ]` Pending | Target for Chat 3 (P3-6). |
| **CPP-10** | Arrays (C-style UB demo, `std::array`, `std::vector` basics) | `[ ]` Pending | Target for Chat 4 (P3-7). |
| **CPP-11** | Strings (`std::string` ops, C-string `\0`) | `[ ]` Pending | Target for Chat 4 (P3-7). |
| **CPP-12** | File I/O with `<fstream>` | `[ ]` Scheduled | Apr–Jun 2027. |
| **CPP-13** | Debug basics (`-Wall -Wextra`, gdb intro) | `[ ]` Scheduled | Apr–Jun 2027. |

*Note: Pass-by-reference (`&`, `const &`) belongs strictly to Block 2 (`CPP-14`).*

---

## 3. Verified Defects in Ported Code (Chat 3 Fix List)

Real runs under `g++ -std=c++20 -fsanitize=undefined -g` verified these exact failures:

1. **`block_1/src/p12_gcd_lcm.cpp`**:
   - `(100000, 100000)` $\implies$ runtime error: signed integer overflow ($10^{10} > 2.14 \times 10^9$). Output is `14100` instead of `100000`.
   - `(0, 0)` $\implies$ runtime error: division by zero, crashes with SIGFPE core dump.
   - `(-4, 6)` $\implies$ returns GCD 6, LCM -4 (silent drop of input validation present in Python original).
2. **`block_1/src/p02_prime_check.cpp`**:
   - `2147483647` (prime) $\implies$ runtime error: signed integer overflow `46341 * 46341`. Reports "composite".
   - `is_prime(0)`, `is_prime(1)`, `is_prime(-5)` $\implies$ return `1` (true) when invoked directly because boundary checks were isolated in `main()`.
3. **`block_1/src/p09_fibonacci_series.cpp`**:
   - `first_n_terms(48)` $\implies$ runtime error: signed integer overflow on term 47 ($1836311903 + 1134903170$). Term 48 prints `-1323752223`.
   - `terms_upto_m(2147483647)` $\implies$ infinite loop / UB.

*Auditor rule: The learner writes all fixes by hand.*

---

## 4. Sub-Chat Roster & Context Boundaries

- **Chat 1 of 4 (3.1.1):** P3-1 & P3-2. Completed (2.0 h).
- **Chat 2 of 4 (3.1.2):** P3-3 & P3-4. Completed (4.0 h).
- **Chat 3 of 4 (3.1.3):** P3-5 & P3-6. Next.
  - Sees only `CPP_PATH/`.
  - Fixes p12, p02, p09 first; administers 2-statement CPP-04 retest.
  - Teaches CPP-08 part 1 (pass-by-value only); ports p13.
  - Teaches CPP-08 part 2 (`.h`/`.cpp`, Makefile) & CPP-09.
- **Chat 4 of 4 (3.1.4):** P3-7 & Block 1 Part A wrap-up. Upcoming.
  - Ports p14, p06, p18; CPP-10, CPP-11.

---

## 5. Decision Log (Phase 3)

- **D-P3-01:** Workspace restructured into modular blocks (`block_1/src/`, `block_1/notes/`, `block_1/python_reference/`). Compiled binaries gitignored.
- **D-P3-02:** AI coordination files centralized in `ai_logs_nrest/` (`SESSION_STATE.md`, `CPP_TRACK_CONTEXT.md`, `qna_and_verification_bank.md`, `report/`).
- **D-P3-03:** Pass-by-reference confirmed locked to Block 2 (CPP-14); P3-5 restricted to pass-by-value.
- **D-P3-04:** `main_state/CMAIN_STATE.md` established as the single rolling state handover document for CMAIN.
