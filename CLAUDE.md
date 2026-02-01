## Style

- 2-spaces for indentation
- `PascalCase` class names, file names
- `CamelCase` method names and variable names
- `snake_case` for type aliases
- Split classes into header and implementation files when possible

## Language

- C++20
- Be as const-correct as possible
- Prefer trailing return types and braces on same line for functions `constexpr auto function() -> type {`

## Code Generation

- Use C++ standard library types over any implementation-defined types unless the implementation-defined offers necessary features
- Templates are found in `/templates`
  - Use them as reference when asked 
  - For example: When asked "Create logging subsystem" then `/templates/subsystem` will be your starting point for class and file structure
- `#include "SourceHeader.h"` for headers in this codebase, `#include <VendorHeader.h>` for external and system header files
- Comments should not state the obvious, or refer to historical fixes

## Scripts

- Use `./scripts/update-cmake-sources.sh` whenever you need to add/remove source files from CMakeLists.txt