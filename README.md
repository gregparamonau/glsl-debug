# glsl-debug

A CPU-based GLSL fragment shader emulator written in C++. Runs shaders on the CPU instead of the GPU — slowly, but with full access to every intermediate value during execution.

The point is numerical debugging. Instead of encoding a value into a color channel to see what's happening, you can read the actual float values of any variable at any pixel mid-execution.

---

## Architecture

```
GLSL source
    |
  Lexer        -- tokenizes source into a flat token stream
    |
  Parser       -- recursive descent, produces an AST
    |
  Interpreter  -- walks the AST, maintains a scope stack
    |
  Output       -- per-pixel color buffer + debug state
```

**Lexer** -- single left-to-right pass. Length-bucketed token table for greedy operator matching. Handles keywords, identifiers, float/hex literals, operators, punctuation. Comments stripped during tokenization.

**Parser** -- recursive descent. Operator precedence handled via a chain of functions, one per precedence level.

**Interpreter** -- walks the AST recursively. Scope stack pushed/popped on block entry/exit. Function calls save and restore the stack so functions can't access caller variables. Built-in functions (sin, cos, dot, normalize, mix, etc.) implemented in `builtin.cpp`, dispatched by name from a hash map.

---

## Building

Requires C++17.

```bash
make
make run
make clean
```

---

## Status

- [x] Lexer
- [ ] Parser (in progress)
- [ ] Interpreter
- [ ] Built-ins
- [ ] Per-pixel execution loop
- [ ] Debug output