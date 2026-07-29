# Dominus C++ Style Guide

The gold standard is **clean, readable, professional code**.

Style rules exist to make the codebase easier to understand and maintain. When a rule conflicts with clarity, prefer the clearest reasonable code and remain consistent with the surrounding file.

## Formatting

- Use four spaces for indentation. Never use tabs.
- Use Allman braces.

```cpp
if (AtEnd())
{
    return EndOfFile();
}
```

- Put one statement on each line.
- Use spaces around binary operators and after commas.
- Wrap long or conceptually dense expressions where the structure becomes easier to read.
- Keep related code visually grouped with blank lines.
- Write pointer and reference symbols beside the variable name.

```cpp
Source *source;
const Source &source;
```

- Avoid trailing whitespace and end files with a newline.

## Naming

| Construct | Convention | Example |
|---|---|---|
| Namespace | lowercase | `dominus` |
| Types | PascalCase | `SourceSpan` |
| Functions and methods | PascalCase | `NextToken()` |
| Variables and parameters | snake_case | `source_offset` |
| Private data members | leading underscore + snake_case | `_source_text` |
| Constants | ALL_CAPS | `MAX_SOURCE_LENGTH` |
| Enum values | PascalCase | `TokenKind::IntegerLiteral` |
| Headers | snake_case.hpp | `source_span.hpp` |
| Implementations | snake_case.cpp | `source_span.cpp` |

Use leading underscores only for private data members.

Choose names that describe the domain concept rather than its implementation detail.

## Files and Includes

- Use `.hpp` for headers and `.cpp` for implementations.
- Prefer one principal type or closely related subsystem per file.
- Public headers belong under `include/dominus/`.
- Internal-only headers belong under `src/`.
- Use `#pragma once`.
- Each file should directly include the declarations it uses.

Group includes in this order, separated by blank lines:

1. The corresponding header.
2. Other Dominus headers.
3. Third-party headers.
4. Standard-library headers.
5. Platform-specific headers.

## C++ Practices

- Prefer direct, explicit code over clever code.
- Prefer values and stable IDs over pointer-heavy object graphs.
- Make ownership and lifetime clear.
- Use references when an object is required and pointers when absence is meaningful.
- Prefer RAII and standard-library containers.
- Do not use manual `new` or `delete`.
- Use `std::unique_ptr` for genuine exclusive heap ownership.
- Use `std::shared_ptr` only when ownership is genuinely shared.
- Use `const` where it communicates a real read-only guarantee.
- Prefer `enum class` for enumerations.
- Make single-argument constructors `explicit` unless implicit conversion is intentional.
- Do not use C-style casts.
- Handle malformed input and failure states deliberately.
- Avoid premature abstraction, generalisation, and optimisation.
- Do not create wrappers, getters, setters, or inheritance hierarchies without a concrete benefit.

Use `auto` when the exact type is unimportant or excessively verbose. Prefer an explicit type when it communicates domain meaning, ownership, units, or numeric representation.

## Comments

Comments should explain intent, invariants, non-obvious decisions, or important steps.

Do not mechanically comment code that is already self-explanatory. Keep comments accurate as the implementation changes.

## Tests

- Production behaviour must be covered by tests.
- Treat tests as executable statements of Dominus semantics.
- Prefer small tests with clear behavioural names.
- Keep each TDD increment focused.
- Test code should meet the same readability standard as production code.
- Assert stable behaviour rather than incidental implementation details.

## Final Rule

A reader should be able to understand the code without fighting its formatting, naming, control flow, or abstractions.

When uncertain, choose the version that is simplest to read correctly.
