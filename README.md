# Phase 3: C++, Electronics & Systems Programming Track

Master repository for **Phase 3** of the systems curriculum. This repository documents hands-on systems programming, starting from fundamental C++20 and machine models to electronics, digital logic, and embedded simulation.

---

## 1. Track Architecture & Block Structure

The track is partitioned into modular blocks, each having its own self-contained source code, notes, and references:

- **[`block_1/`](block_1/) — Bits & Basics (~45 hrs)**
  - **Focus:** C++20 fundamentals, fixed-width integers, memory sizes, control flow, functions, modular compilation units (`.h`/`.cpp`), Makefiles, vectors, strings, and file I/O.
  - **Directory Layout:**
    - `notes/`: Block 1 conceptual guides, design notes, and digital number systems.
    - `src/`: Hand-crafted C++20 implementation files.
    - `python_reference/`: CBSE Class 11 reference programs used for differential testing (`diff -u`).
- **[`block_2/`](block_2/) — Memory & Circuits (~45 hrs)**
  - **Focus:** Pointers, references, memory management (stack vs. heap), RAII, smart pointers, structs/classes, basic electronics (Ohm's law, Kirchhoff's laws, dividers), and simulated circuits (Falstad).
- **[`block_3/`](block_3/) — Data & Sensors (~45 hrs)**
  - **Focus:** STL deep dive, data structures from scratch (dynamic array, linked list, tree), embedded sensor interfaces (Wokwi/Arduino).

---

## 2. Toolchain & Development Standards

- **Compiler:** `g++` (Ubuntu Linux, GCC 15.2.0)
- **Standard Flags:**
  ```bash
  g++ -std=c++20 -Wall -Wextra <source.cpp> -o <binary_name>
  ```
- **Undefined Behavior Sanitizer (Audit Mode):**
  ```bash
  g++ -std=c++20 -Wall -Wextra -fsanitize=undefined -g <source.cpp> -o <binary_name>
  ```
- **Code Rules:**
  - Strict explicit namespace prefixes (`std::`), **never** `using namespace std;`.
  - Zero compiler warnings tolerated under `-Wall -Wextra`.
  - All ports verified via differential testing (`diff -u`) against Python reference outputs.

---

## 3. Coordination & Evidence Tracking

All agent orchestration, session state, and verification audit files are preserved in:
- **[`ai_logs_nrest/`](ai_logs_nrest/)**:
  - `SESSION_STATE.md`: Real-time session checkpoint tracker, hours log, and atom status.
  - `CPP_TRACK_CONTEXT.md`: Cross-chat master handover document.
  - `qna_and_verification_bank.md`: Verbatim student Q&A verification logs.
  - `report/`: Post-session completion reports.
