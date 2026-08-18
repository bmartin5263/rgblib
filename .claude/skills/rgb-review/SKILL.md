---
name: rgb-review
description: Review changed files (and files that depend on them) in the rgblib C++ codebase for correctness bugs, dynamic memory allocation, and missing test coverage, then check README.md for staleness. Use when the user asks to review a diff/branch/PR in this repo, or explicitly invokes /rgb-review.
tools: Read, Grep, Glob, Bash, ReportFindings
---

# Rgb-review

Review changed C++ files in this embedded LED-framework codebase, trace their dependents, and flag correctness bugs, unwanted dynamic allocation, and missing tests. Finish by checking `README.md` for staleness.

This targets embedded hardware (Arduino Nano ESP32) and its core promise, per `README.md`, is **"Allocation-free after initialization"** — heap allocation after startup is a real bug here, not a style nit.

## 1. Scope the diff

`git status` + `git diff HEAD` by default; diff against a named branch/PR/commit range if given. Skip generated/binary scratch files unless asked about them.

## 2. Find dependents

For each changed header/source, grep for `#include "File.h"`, subclasses/overrides, and call sites of changed public methods across `src include test templates examples`. Read enough of each dependent to confirm signatures, semantics, and lifetime assumptions still hold.

## 3. Review for bugs

Read each changed file in full (not just diff hunks) plus its dependents. Check for: logic/off-by-one/boundary errors; lifetime/dangling-reference issues around `Handle` and pooled subsystems (`PriorityNodePool`, `Animations`, `Effects`, `Timer`); Rule-of-5 violations; const-correctness gaps; signed/unsigned and overflow issues in pixel/duration math; uninitialized members; header/implementation mismatches; behavior differences across `RGB_*` compile flags.

If you can compile, verify with `/opt/homebrew/bin/pio run -e debug` and `/opt/homebrew/bin/pio run -e release`.

## 4. Flag dynamic allocation

Search changed/dependent files for `new`/`delete`, `malloc`/`calloc`/`realloc`/`free`, and heap-backed STL (`std::vector`, `std::string`, `std::map`, `std::unique_ptr`/`shared_ptr`, etc.). Note whether each is one-time setup (fine) or in a runtime hot path like `update()`/`draw()`/per-frame callbacks (likely a bug) — suggest the fixed-capacity pool pattern used elsewhere when relevant.

`std::function` should be evaluated for whether the framework is in danger of doing a dynamic allocation or a dynamic allocation would be something the user would choose to do. The latter is fine, the former is questionable

## 5. Flag missing tests

Tests live in `test/test_*.cpp` (googletest, `pio test -e native`), stubs in `test/stubs`. For each changed file with non-trivial logic, check whether a matching test exists/was updated, and name specific missing cases (edge conditions, new branches, bug-fix regressions) rather than a generic "add tests."

## 6. Flag overly verbose or redundant comments

Comments should seldomly be used, and large text blocks are almost always wrong. Strive for one-line explanations when possible.

## 7. Check README staleness

Compare `README.md` against the changes: new/changed public API not reflected in Basics/Features, new compile flags missing from the Configuration table, examples that no longer match current signatures, or claims (e.g. allocation-free) the change would violate.

## 8. Report

Use `ReportFindings` for bugs, allocation, and test-coverage findings (prefix `category` with `allocation`/`test-coverage` where relevant), ranked most-severe first. Then add a short plain-text list of README staleness items — they're doc gaps, not code defects, so they don't fit the findings schema.
