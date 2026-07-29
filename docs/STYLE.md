# Dominus C++ Style Guide

This guide records the project conventions that are not fully enforced by `.clang-format`.

The goal is readable, consistent code without unnecessary ceremony. Prefer direct code, explicit types, and abstractions that protect real invariants rather than abstractions added only to satisfy generic “good OO” advice.

## Formatting

`.clang-format` is authoritative for mechanical formatting.

- Four spaces; never tabs.
- Allman braces.
- Pointer and reference symbols are written beside the variable name:

```cpp
Source *source;
const Source &source;
```

- There is no mechanically enforced maximum line length. Wrap long or conceptually complex expressions manually where doing so improves readability.
- Short function calls may remain on one line.
- When an ordinary function call, constructor call, declaration, or definition
  is split across lines:
  - place each argument or parameter on its own line;
  - place the closing parenthesis on its own line.
- When a multiline braced initializer is passed directly to a function, keep
  the function call and type together, place each initializer on its own line,
  and close the expression with `});`.

```cpp
const auto next_line = std::upper_bound(
    source.line_starts.begin(),
    source.line_starts.end(),
    byte_offset
);

return SourceLocation(
    source_id,
    byte_offset,
    line,
    byte_column
);

_sources.push_back(Source{
    .name = std::move(name),
    .text = std::move(text),
    .line_starts = std::move(line_starts)
});
```

- Includes are sorted automatically.

## Naming

| Construct | Convention | Example |
|---|---|---|
| Namespace | lowercase | `dominus` |
| Types | PascalCase | `SourceSpan` |
| Functions and methods | PascalCase | `NextToken()` |
| Variables and parameters | snake_case | `source_offset` |
| Private members | leading underscore + snake_case | `_source_text` |
| Constants | ALL_CAPS | `MAX_SOURCE_LENGTH` |
| Enum values | PascalCase | `TokenKind::IntegerLiteral` |
| Headers | snake_case.hpp | `source_span.hpp` |
| Implementations | snake_case.cpp | `source_span.cpp` |

A leading underscore is reserved for private data members only. Never use names beginning with an underscore followed by an uppercase letter, double underscores, or leading underscores at namespace scope.

Project macros, where unavoidable, use a `DOMINUS_` prefix:

```cpp
#define DOMINUS_DEBUG_MODE
```

## Files and Headers

- Use `.hpp` for headers and `.cpp` for implementations.
- Prefer one principal type or subsystem per file.
- Use `#pragma once`.
- Headers must include every dependency they require and must not depend on accidental include order.
- Public headers belong under `include/dominus/`.
- Internal headers belong under `src/`.

## Include Order

Use the following groups, separated by blank lines:

1. The corresponding header for a `.cpp` file.
2. Other Dominus headers.
3. Third-party headers.
4. C++ standard-library headers.
5. Platform-specific headers.

Example:

```cpp
#include "source_span.hpp"

#include <dominus/source.hpp>

#include <doctest/doctest.h>

#include <cstddef>
#include <string>
```

## C++ Usage

- Prefer values and stable IDs over pointer-heavy object graphs.
- Raw pointers and references are non-owning.
- Use references when an object is required and pointers when absence is meaningful.
- Prefer `std::unique_ptr` when heap ownership is genuinely required.
- Use `std::shared_ptr` only when ownership is genuinely shared.
- Do not use manual `new` or `delete`.
- Do not use C-style casts. Use explicit C++ casts when conversion is necessary.
- Do not use production `assert()` calls. Malformed input and failure states must be handled deliberately.
- Use `const` where it communicates meaningful read-only intent or is required by an interface; do not add it mechanically.
- Do not create getters, setters, wrapper types, or indirection solely to satisfy abstract OO conventions. Encapsulation should protect a real invariant.

## `auto` usage

- Prefer explicit types when the type communicates domain meaning, ownership,
  units, or numeric representation.
- Use `auto` when the initializer makes the type clear and spelling the exact
  type would add noise or expose an implementation detail. Iterators and lambda
  types are common examples.
- Do not use `auto` merely to shorten a meaningful domain type.
- When using `auto`, write reference and const qualifiers deliberately.

```cpp
// Good: the exact iterator type is verbose and unimportant.
const auto next_line = std::upper_bound(
    source.line_starts.begin(),
    source.line_starts.end(),
    byte_offset
);

// Good: the numeric type and its meaning matter.
const std::size_t line_index = static_cast<std::size_t>(
    std::distance(source.line_starts.begin(), line_start_iterator)
);

// Good: SourceLocation is an important domain concept.
const SourceLocation location = sources.Locate(source_id, byte_offset);

// Good: the reference relationship and domain type are useful to see.
const Source &source = _sources.at(source_id._index);
```

## Comments

Use clean, concise comments wherever they improve comprehension, visual structure, or the readability of a multi-step operation.

Comments are not required mechanically, and straightforward descriptive comments are acceptable when they help a reader scan the code.

```cpp
// Load the customer.
Customer customer = customers.Load(customer_id);

// Apply the outstanding changes.
customer.ApplyChanges(changes);

// Advance to the next record.
++offset;
```

## Tests

Production behaviour must be covered by tests. Test code is held to the same readability standard as production code.
