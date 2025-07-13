### ✅ `README.md` — `JMVLang`

# JMVLang 🛠️

**JMVLang** is a minimal compiled programming language designed and built by **Jeeva S**.  
It takes a custom `.my` source file and compiles it **directly to x86-64 assembly**, producing a native executable — no intermediate C required.

> From simple source to full binary with your own compiler. Powered by C, made for learning and hacking.

---

## ✨ Features

- ✅ Custom language syntax (inspired by C)
- ✅ Lexer, parser, AST generation
- ✅ Semantic checks (e.g., undeclared or duplicate variables)
- ✅ x86-64 Assembly generation (AT&T/GAS syntax)
- ✅ Object file and executable creation
- ✅ Built fully in **C**

---

## 🔤 Language Syntax (JMVLang)

Supported features:

```my
int a = 5 + 3;
int b = a - 2;
print(b);

* `int` declarations
* Arithmetic: `+`, `-`
* Print integer expressions via `print()`
```
---

## 📁 Project Structure

```
jmvlang/
├── source.my          # Your input program (written in JMVLang)
├── main.c             # Entry point
├── lexer.c/.h         # Tokenizer
├── parser.c/.h        # AST + semantic analysis
├── asmgen.c/.h        # Direct x86-64 Assembly code generation
├── token.h            # Token structure
├── ast.h              # AST node types
├── symbol_table.c/.h  # Symbol table management
├── output.s           # Generated assembly
├── output             # Final binary
```

---

## ⚙️ Build & Run

### 🧱 1. Compile the JMVLang compiler

```bash
gcc main.c lexer.c parser.c symbol_table.c asmgen.c -o jmvlang
```

### 🧾 2. Write your source in `source.my`

Example:

```my
int x = 10 + 5;
print(x);
```

### 🧪 3. Compile your program with JMVLang

```bash
./jmvlang
```

This will:

* Tokenize and parse `source.my`
* Generate `output.s` (assembly)
* Assemble to `output.o`
* Link to create the `output` executable

---

## ▶️ Run Your Program

```bash
./output
```

✅ You’ll see the result printed (e.g., `15`)

---

## 🐳 Optional: Run in Docker (macOS/Windows)

If you're on macOS or Windows and want to use Linux assembly support:

```bash
docker run --rm -v "$PWD":/src -w /src gcc bash -c "gcc -no-pie output.s -o output && ./output"
```

---

## 📚 Learning Focus

This repo is perfect for anyone learning:

* Compiler theory (from scratch)
* Lexical analysis and parsing
* AST construction
* Semantic analysis
* x86-64 assembly generation
* Symbol management and codegen

---

## 🧠 Next Steps (Roadmap)

* [ ] Add support for `*` and `/` operators
* [ ] Implement control flow: `if`, `while`
* [ ] Add `string` and `char` support
* [ ] Generate LLVM IR backend
* [ ] Build an interactive REPL for `JMVLang`

---

## 📄 License

MIT License — use, learn, and modify freely.

---