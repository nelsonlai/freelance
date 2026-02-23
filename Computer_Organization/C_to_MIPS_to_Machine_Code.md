# From C Code to MIPS Assembly to Machine Code

This document explains the full pipeline: **writing C code → compiling to MIPS assembly → assembling to machine code**, with binary and hexadecimal representation. We use a C program that **prompts the user to enter a temperature in Fahrenheit, converts it to Celsius, and prints the result**.

---

## Table of Contents

1. [Overview of the Pipeline](#1-overview-of-the-pipeline)
2. [Step 1: Write C Code](#2-step-1-write-c-code)
3. [Step 2: Compile C to MIPS Assembly](#3-step-2-compile-c-to-mips-assembly)
4. [Step 3: Understand the Generated Assembly](#4-step-3-understand-the-generated-assembly)
5. [Step 4: Assemble to Machine Code](#5-step-4-assemble-to-machine-code)
6. [Step 5: Binary and Hex for Key Instructions](#6-step-5-binary-and-hex-for-key-instructions)
7. [Summary](#7-summary)

---

## 1. Overview of the Pipeline

High-level languages like C must be translated into something the CPU can execute:

```
   C source code          MIPS assembly           Machine code (binary/hex)
   (.c file)       →      (.s file)         →    (object file / executable)
        │                        │                            │
   [Compiler]              [Assembler]                  [Linker optional]
   (e.g. gcc -S)           (e.g. as, MARS)               Produces final
   or MIPS                  encodes each                 bytes CPU runs
   cross-compiler           instruction
```

- **Compiler:** Translates C into **assembly language** for the target CPU (MIPS). For our program, that means turning the Fahrenheit prompt, `scanf`, the formula \( (F-32)\times 5/9 \), and the "Celsius is ..." print into a sequence of MIPS instructions and syscalls.
- **Assembler:** Translates **assembly** into **machine code** (32-bit instructions). Each line of assembly (e.g. `addi $t0, $t0, -32`) becomes one or more 32-bit words.
- **Machine code** is what the CPU executes; it is often shown in **hex** (e.g. `0x2108FFE0`) or **binary** (32 bits per instruction).

---

## 2. Step 1: Write C Code

**File: `fahrenheit_to_celsius.c`**

```c
#include <stdio.h>

int main() {
    int fahrenheit;
    int celsius;

    // 1) Prompt user to input Fahrenheit
    printf("Enter temperature in Fahrenheit: ");
    scanf("%d", &fahrenheit);

    // 2) Convert Fahrenheit to Celsius
    // Formula: C = (F - 32) * 5 / 9
    celsius = (fahrenheit - 32) * 5 / 9;

    // 3) Print the Celsius result
    printf("Celsius is %d\n", celsius);

    return 0;
}
```

**What this program does (in detail):**

| Part of the program | Purpose |
|---------------------|--------|
| `int fahrenheit; int celsius;` | Declares two integer variables: one for the user's input (Fahrenheit) and one for the computed result (Celsius). |
| `printf("Enter temperature in Fahrenheit: ");` | Prints a prompt string so the user knows what to type. |
| `scanf("%d", &fahrenheit);` | Reads a single integer from standard input and stores it at the address of `fahrenheit`. The `%d` means "decimal integer"; `&fahrenheit` passes the memory address so `scanf` can write the value there. |
| `celsius = (fahrenheit - 32) * 5 / 9;` | **Conversion formula:** Subtract 32 from Fahrenheit, multiply by 5, then integer-divide by 9. This is the standard formula \( C = \frac{5}{9}(F - 32) \). Integer division truncates toward zero (e.g. 10/9 = 1). |
| `printf("Celsius is %d\n", celsius);` | Prints the literal text `Celsius is `, then the value of `celsius`, then a newline. So the output looks like: `Celsius is 25`. |
| `return 0;` | Returns 0 from `main`, which by convention means "success" to the operating system. |

**Why the formula works:** The Fahrenheit and Celsius scales agree at -40° and relate linearly. The formula \( C = \frac{5}{9}(F - 32) \) comes from the fact that 0°C = 32°F and a 1°C change equals a \( \frac{9}{5} \)°F change. So we subtract 32 (shift the origin) then scale by \( \frac{5}{9} \).

The compiler must generate code that: calls library routines for `printf` and `scanf`, passes format strings and addresses, performs subtraction, multiplication, and division, and returns 0. Below we use an **equivalent** MIPS program that does the same I/O and conversion using **MARS syscalls**, so the logic stays clear and we can show machine-code encoding.

---

## 3. Step 2: Compile C to MIPS Assembly

### What the compiler does

1. **Parsing:** Builds a syntax tree from your C code (e.g. the assignment `celsius = (fahrenheit - 32) * 5 / 9` is parsed as an expression with subtraction, multiplication, and division).
2. **Semantic analysis:** Resolves types and checks correctness (e.g. `scanf` needs the address of `fahrenheit`; the operands of `*` and `/` are integers).
3. **Code generation:** Produces MIPS assembly: code to call the C library for `printf` and `scanf`, and a sequence of arithmetic instructions (subtract 32, multiply by 5, divide by 9) and stores for the result.

For a program that uses `printf` and `scanf`, the generated assembly is long (library call setup, stack frames, etc.). So for this document we use a **hand-written MIPS equivalent** that behaves the same way but uses MARS syscalls. The pipeline (C → assembly → machine code) and the way instructions are encoded are unchanged.

### How to get MIPS assembly from this C program

**Using a MIPS cross-compiler (e.g. on Linux):**

```bash
mips-linux-gnu-gcc -S -o fahrenheit_to_celsius.s fahrenheit_to_celsius.c -fno-pic -march=mips32r2
```

**Using MARS:** You can type (or paste) the MIPS assembly from the next section into MARS, assemble it, and run it. MARS will show the generated machine code in the Text Segment.

---

## 4. Step 3: Understand the Generated Assembly

Below is a **MIPS program equivalent** to the C program: it (1) prompts the user to enter Fahrenheit, (2) reads the integer, (3) converts Fahrenheit to Celsius using \( C = (F - 32) \times 5 / 9 \), and (4) prints `Celsius is {result}`. It uses MARS syscalls:

- **Syscall 4:** Print string (address in `$a0`).
- **Syscall 5:** Read integer (result in `$v0`).
- **Syscall 1:** Print integer (value in `$a0`).

Variables `fahrenheit` and `celsius` are stored in the `.data` segment.

### MIPS assembly equivalent to the C program

```asm
        .data
prompt:     .asciiz "Enter temperature in Fahrenheit: "
result_msg: .asciiz "Celsius is "
newline:    .asciiz "\n"
fahrenheit: .word 0
celsius:    .word 0

        .text
        .globl main
main:
        # 1) printf("Enter temperature in Fahrenheit: ");
        li      $v0, 4
        la      $a0, prompt
        syscall

        # 2) scanf("%d", &fahrenheit);
        li      $v0, 5
        syscall
        sw      $v0, fahrenheit

        # 3) Convert: celsius = (fahrenheit - 32) * 5 / 9
        lw      $t0, fahrenheit      # $t0 = F
        addi    $t0, $t0, -32        # $t0 = F - 32
        li      $t1, 5               # $t1 = 5
        mul     $t2, $t0, $t1        # $t2 = (F - 32) * 5
        li      $t3, 9               # $t3 = 9
        div     $t2, $t3             # lo = quotient, hi = remainder
        mflo    $t4                  # $t4 = (F-32)*5/9 = Celsius
        sw      $t4, celsius         # store result

        # 4) printf("Celsius is %d\n", celsius);
        li      $v0, 4
        la      $a0, result_msg
        syscall
        li      $v0, 1
        lw      $a0, celsius
        syscall
        li      $v0, 4
        la      $a0, newline
        syscall

        # return 0;
        li      $v0, 0
        jr      $ra
```

### What each part does (detailed)

**Data section (`.data`):**

| Label | Directive | Meaning |
|-------|-----------|--------|
| `prompt` | `.asciiz "Enter temperature in Fahrenheit: "` | Null-terminated string for the input prompt. The assembler stores each character as a byte plus a final `\0`. |
| `result_msg` | `.asciiz "Celsius is "` | The literal text printed before the number. |
| `newline` | `.asciiz "\n"` | A single newline character (ASCII 10) so the output ends with a line break. |
| `fahrenheit` | `.word 0` | Reserves one word (4 bytes) for the user's input. Initial value 0; overwritten by `sw` after syscall 5. |
| `celsius` | `.word 0` | Reserves one word for the computed Celsius value. |

**Text section (`.text`) – main logic:**

| Instruction(s) | C equivalent | Detailed comment |
|----------------|--------------|------------------|
| `li $v0, 4` then `la $a0, prompt` then `syscall` | `printf("Enter temperature in Fahrenheit: ");` | **li** loads the immediate value 4 into `$v0` (syscall 4 = print string). **la** loads the address of the label `prompt` into `$a0` (syscall 4 expects the string address in `$a0`). **syscall** transfers control to the kernel/simulator, which reads `$v0` and `$a0` and prints the string. |
| `li $v0, 5` then `syscall` then `sw $v0, fahrenheit` | `scanf("%d", &fahrenheit);` | Syscall 5 reads one integer from the user and places it in `$v0`. **sw** (store word) writes that value from `$v0` into the memory address of `fahrenheit` so we can use it for the conversion. |
| `lw $t0, fahrenheit` | Load `fahrenheit` | **lw** (load word) reads the 32-bit value at the address of `fahrenheit` into register `$t0`. |
| `addi $t0, $t0, -32` | `fahrenheit - 32` | **addi** adds the 16-bit signed immediate (-32) to `$t0` and writes the result back to `$t0`. So `$t0` now holds \( F - 32 \). MIPS has no “sub immediate”; subtracting 32 is done by adding -32. |
| `li $t1, 5` then `mul $t2, $t0, $t1` | `(F-32) * 5` | **li** sets `$t1 = 5`. **mul** (multiply) computes `$t0 * $t1` and places the low 32 bits of the product in `$t2`. So `$t2 = (F - 32) * 5`. |
| `li $t3, 9` then `div $t2, $t3` | Divide by 9 | **div** divides `$t2` by `$t3`. The **quotient** goes into the special register `lo`, the **remainder** into `hi`. We need the quotient for integer division. |
| `mflo $t4` | Get quotient | **mflo** (move from lo) copies the value in `lo` (the quotient) into `$t4`. So `$t4 = (F-32)*5/9` = Celsius. |
| `sw $t4, celsius` | `celsius = ...` | Store the value in `$t4` into the memory location labeled `celsius`. |
| `li $v0, 4` then `la $a0, result_msg` then `syscall` | `printf("Celsius is ");` | Print the string `"Celsius is "` using syscall 4. |
| `li $v0, 1` then `lw $a0, celsius` then `syscall` | `printf("%d", celsius);` | Syscall 1 prints the integer in `$a0`. We load `celsius` into `$a0` and then invoke the syscall. |
| `li $v0, 4` then `la $a0, newline` then `syscall` | `printf("\n");` | Print a newline so the output ends with a line break. |
| `li $v0, 0` then `jr $ra` | `return 0;` | Set return value to 0 in `$v0` and **jr** (jump register) to the address in `$ra`, i.e. return to the caller (e.g. the runtime startup). |

**Pseudo-instructions and syscalls (detailed):**

- **`li`** (load immediate): The assembler expands it to a single instruction that can put a constant into a register, e.g. **addi** `$rd, $zero, imm` (add immediate: register = 0 + imm). For large immediates it may use **lui** + **ori**.
- **`la`** (load address): Puts the 32-bit address of a label into a register. The assembler typically uses **lui** (load upper immediate) to set the top 16 bits and **ori** (or immediate) to set the lower 16 bits, since MIPS I-type instructions only have a 16-bit immediate field.
- **`syscall`**: Special instruction that raises a trap. The operating system or simulator looks at `$v0` to decide which service to run (4 = print string, 5 = read integer, 1 = print integer). Other arguments are passed in `$a0`, `$a1`, etc., as documented for each syscall.
- **`mul`**: In MIPS32, **mul** is a real instruction (e.g. SPECIAL2 opcode, mul funct). It computes `rd = rs * rt` (low 32 bits of the product). Some assemblers also support it as a pseudo-instruction expanding to **mult** + **mflo**.
- **`div`**: **div** `rs, rt` puts quotient in `lo` and remainder in `hi`. **mflo** / **mfhi** move those values into a general-purpose register.

We will encode several of these instructions into **binary** and **hex** next.

---

## 5. Step 4: Assemble to Machine Code

### What the assembler does

1. **Reads** the assembly source.
2. **Parses** labels, mnemonics, and operands.
3. **Resolves** labels to addresses.
4. **Encodes** each instruction into a **32-bit** word (R-type, I-type, or J-type).
5. **Outputs** object code or a listing with addresses and machine code.

### MIPS instruction formats (brief)

| Format | Used for | Fields |
|--------|----------|--------|
| **R-type** | Register arithmetic (add, sub, …), jr, syscall | op (6) \| rs (5) \| rt (5) \| rd (5) \| shamt (5) \| funct (6) |
| **I-type** | Immediate (addi, li), load/store (lw, sw) | op (6) \| rs (5) \| rt (5) \| immediate (16) |
| **J-type** | Jump (j, jal) | op (6) \| target (26) |

---

## 6. Step 5: Binary and Hex for Key Instructions

We encode a **representative subset** of the instructions from the program above. MIPS is typically shown **big-endian**: leftmost bits are most significant (e.g. opcode at bits 31–26).

### Register numbers used

| Register | Number | 5-bit binary |
|----------|--------|---------------|
| $zero ($0) | 0 | 00000 |
| $v0 ($2) | 2 | 00010 |
| $a0 ($4) | 4 | 00100 |
| $t0 ($8) | 8 | 01000 |
| $t1 ($9) | 9 | 01001 |
| $t2 ($10) | 10 | 01010 |
| $t3 ($11) | 11 | 01011 |
| $t4 ($12) | 12 | 01100 |
| $ra ($31) | 31 | 11111 |

---

### Instruction 1: `li $v0, 4` (pseudo-instruction → `addi $v0, $zero, 4`)

- **Format:** I-type  
- **Meaning:** Load immediate 4 into `$v0` (syscall number for “print string”).

**I-type:** op | rs | rt | immediate

- **op** = 001001 (9) → **addi**
- **rs** = 00000 ($zero)
- **rt** = 00010 ($v0)
- **immediate** = 4 = 0x0004

**Binary:**

```
001001  00000  00010  0000000000000100
  op     rs     rt         immediate
```

**Hex:** 0x20020004

---

### Instruction 2: `lw $t0, fahrenheit`

- **Format:** I-type  
- **Meaning:** Load word at the address of `fahrenheit` into `$t0` (the value the user entered).

- **op** = 100011 (35) → **lw**
- **rs** = base register (e.g. $gp = 28). The assembler resolves the label `fahrenheit` to an address; often it is **lw** `rt, offset(base)` with a small offset from `$gp`.
- **rt** = 01000 ($t0) — destination register.
- **immediate** = 16-bit offset (e.g. 0 if `fahrenheit` is the first data word).

**Binary (example: lw $t0, 0($gp)):**

```
100011  11100  01000  0000000000000000
  lw    $gp    $t0    offset 0
```

**Hex:** 0x8F880000

*Note:* The exact offset depends on where the assembler places `fahrenheit` in the data segment. In MARS you can see the generated encoding in the Text Segment.

---

### Instruction 3: `addi $t0, $t0, -32` (F - 32)

- **Format:** I-type  
- **Meaning:** Subtract 32 from `$t0` by adding -32. After this, `$t0` holds \( F - 32 \), the first part of the Celsius formula.

**I-type:** op | rs | rt | immediate

- **op** = 001001 (9) → **addi**
- **rs** = 01000 ($t0) — first operand (current value of `$t0`).
- **rt** = 01000 ($t0) — destination (result written back to `$t0`).
- **immediate** = -32. In 16-bit two’s complement: -32 = 0xFFE0 (binary: 1111 1111 1110 0000).

**Binary:**

```
001001  01000  01000  1111111111100000
  op     rs     rt     immediate (-32)
```

**Hex:** 0x2108FFE0

**Why add -32 instead of “sub 32”?** MIPS has no “subtract immediate” instruction. The ISA provides **addi** with a **signed** 16-bit immediate, so the compiler/assembler uses **addi** with a negative immediate to implement subtraction of a constant.

---

### Instruction 4: `mul $t2, $t0, $t1` ((F-32) * 5)

- **Format:** R-type (MIPS32 **mul** uses the SPECIAL2 opcode).  
- **Meaning:** Multiply `$t0` by `$t1` and put the low 32 bits of the product in `$t2`. Here `$t0 = F - 32` and `$t1 = 5`, so `$t2 = (F - 32) * 5`.

**R-type (SPECIAL2):** op | rs | rt | rd | shamt | funct

- **op** = 011100 (28) → **SPECIAL2** (MIPS32 Release 2).
- **rs** = 01000 ($t0).
- **rt** = 01001 ($t1).
- **rd** = 01010 ($t2).
- **shamt** = 00000 (not used by mul).
- **funct** = 000010 (2) → **mul**.

**Binary:**

```
011100  01000  01001  01010  00000  000010
  op     rs     rt     rd   shamt   funct
```

**Hex:** 0x71054002

*Note:* Some assemblers implement **mul** as a pseudo-instruction using **mult** (rs, rt) followed by **mflo** rd. Then the machine code would be two instructions. MARS and MIPS32 can emit the single **mul** encoding above.

---

### Instruction 5: `div $t2, $t3` (divide by 9)

- **Format:** R-type  
- **Meaning:** Divide `$t2` by `$t3`. The **quotient** is placed in the special register **lo**, the **remainder** in **hi**. We use the quotient for integer division by 9.

**R-type:** op | rs | rt | rd | shamt | funct

- **op** = 000000 (SPECIAL).
- **rs** = 01010 ($t2) — dividend.
- **rt** = 01011 ($t3) — divisor (9).
- **rd** = 00000 (unused for div).
- **shamt** = 00000.
- **funct** = 011010 (26) → **div**.

**Binary:**

```
000000  01010  01011  00000  00000  011010
  op     rs     rt     (unused)     funct
```

**Hex:** 0x014B001A

---

### Instruction 6: `mflo $t4` (get Celsius quotient)

- **Format:** R-type  
- **Meaning:** Move the value in **lo** (the quotient from the previous **div**) into `$t4`. So `$t4` = (F-32)*5/9 = Celsius.

**R-type:** op | rs | rt | rd | shamt | funct

- **op** = 000000, **rs** = 00000, **rt** = 00000 (unused).
- **rd** = 01100 ($t4) — destination.
- **shamt** = 00000, **funct** = 010010 (18) → **mflo**.

**Binary:**

```
000000  00000  00000  01100  00000  010010
```

**Hex:** 0x00006012

---

### Instruction 7: `sw $t4, celsius`

- **Format:** I-type  
- **Meaning:** Store the word in `$t4` (the computed Celsius value) into the memory address of the label **celsius**.

- **op** = 101011 (43) → **sw**
- **rs** = base (e.g. $gp), **rt** = 01100 ($t4), **immediate** = offset of `celsius` (e.g. 4 if `fahrenheit` is at 0 and `celsius` at 4).

**Binary (example: sw $t4, 4($gp)):**

```
101011  11100  01100  0000000000000100
```

**Hex:** 0xAF8C0004

---

### Instruction 8: `syscall`

- **Format:** R-type (SPECIAL)  
- **Meaning:** Trap to the kernel/simulator. The kernel reads `$v0` to select the service (4 = print string, 5 = read integer, 1 = print integer) and uses `$a0`, etc., as arguments.

- **op** = 000000, **rs** = 00000, **rt** = 00000, **rd** = 00000, **shamt** = 00000, **funct** = 001100 (12) → **syscall**

**Binary:**

```
000000  00000  00000  00000  00000  001100
```

**Hex:** 0x0000000C

---

### Instruction 9: `jr $ra`

- **Format:** R-type  
- **Meaning:** Jump to the address in `$ra` (return address). Used to return from `main` to the caller (e.g. startup code).

- **op** = 000000, **rs** = 11111 ($ra), **rt** = 00000, **rd** = 00000, **shamt** = 00000, **funct** = 001000 (8) → **jr**

**Binary:**

```
000000  11111  00000  00000  00000  001000
```

**Hex:** 0x03E00008

---

### Instruction 10: `li $v0, 0` (return 0)

- **Pseudo-instruction:** → **addi $v0, $zero, 0**.

- **op** = 001001, **rs** = 00000 ($zero), **rt** = 00010 ($v0), **immediate** = 0

**Binary:**

```
001001  00000  00010  0000000000000000
```

**Hex:** 0x20020000

---

### Summary table: binary and hex (Fahrenheit to Celsius program)

| # | Instruction | Binary (32 bits) | Hex |
|---|-------------|------------------|-----|
| 1 | li $v0, 4 (addi $v0, $zero, 4) | 0010 0000 0000 0010 0000 0000 0000 0100 | 0x20020004 |
| 2 | lw $t0, fahrenheit (e.g. 0($gp)) | 1000 1111 1000 1000 0000 0000 0000 0000 | 0x8F880000 |
| 3 | addi $t0, $t0, -32 | 0010 0001 0000 1000 1111 1111 1110 0000 | 0x2108FFE0 |
| 4 | mul $t2, $t0, $t1 | 0111 0001 0000 0101 0100 0000 0000 0010 | 0x71054002 |
| 5 | div $t2, $t3 | 0000 0001 0100 1011 0000 0000 0001 1010 | 0x014B001A |
| 6 | mflo $t4 | 0000 0000 0000 0000 0110 0000 0001 0010 | 0x00006012 |
| 7 | sw $t4, celsius (e.g. 4($gp)) | 1010 1111 1000 1100 0000 0000 0000 0100 | 0xAF8C0004 |
| 8 | syscall | 0000 0000 0000 0000 0000 0000 0000 1100 | 0x0000000C |
| 9 | jr $ra | 0000 0011 1110 0000 0000 0000 0000 1000 | 0x03E00008 |
| 10 | li $v0, 0 | 0010 0000 0000 0010 0000 0000 0000 0000 | 0x20020000 |

*Note:* The exact encoding of `lw`/`sw` for labels `fahrenheit` and `celsius` depends on where the assembler places them (e.g. relative to `$gp` or with `lui`/`ori`). The table assumes `fahrenheit` at offset 0 and `celsius` at offset 4 from the same base. In MARS you can check the generated machine code in the Text Segment after assembling.

---

## 7. Summary

| Step | Input | Output | Tool / Action |
|------|--------|--------|----------------|
| 1 | Algorithm / requirements | C source (`.c`) | You write C: prompt for Fahrenheit, read integer, compute \( C = (F-32)\times 5/9 \), print "Celsius is {result}", return 0. |
| 2 | C source | MIPS assembly (`.s`) | Compiler or hand-written equivalent using syscalls (4 = print string, 5 = read int, 1 = print int). |
| 3 | Assembly | Understanding | Map each instruction to the C step: prompt, scanf, load, addi -32, mul by 5, div by 9, mflo, store, print string, print int, newline, return. |
| 4 | Assembly | Machine code (binary/hex) | Assembler encodes each instruction into 32-bit words (R-type, I-type, or J-type). |
| 5 | Machine code | Execution | CPU (or MARS) fetches, decodes, and executes each instruction. |

**Concepts (detailed):**

- **Compiler:** C → assembly. One C expression like `celsius = (fahrenheit - 32) * 5 / 9` becomes many instructions: load `fahrenheit`, **addi** -32, **li** 5, **mul**, **li** 9, **div**, **mflo**, **sw** to `celsius`.
- **Assembler:** Assembly → machine code. Each instruction becomes one 32-bit word (or two for pseudo-instructions like **la**). The assembler resolves labels to addresses and fills in immediates and offsets.
- **R-type:** op=0 (or 011100 for mul), then rs, rt, rd, shamt, funct. Used for **add**, **sub**, **mul**, **div**, **mflo**, **jr**, **syscall**.
- **I-type:** op, rs, rt, 16-bit signed immediate. Used for **addi** (including negative for subtract-immediate), **li**, **lw**, **sw**.
- **Division:** **div** puts quotient in **lo** and remainder in **hi**; **mflo** moves **lo** into a general-purpose register so we can use the quotient (Celsius) in the rest of the program.

To see the actual machine code for your program: assemble the MIPS source in MARS and view the Text Segment, or compile the C file with a MIPS toolchain and inspect the object file with `objdump -d fahrenheit_to_celsius.o`.

This pipeline—**C → assembly → machine code (binary/hex)**—is the same for any C program; only the instructions, operands, and addresses change. The Fahrenheit-to-Celsius example illustrates how I/O (syscalls), arithmetic (addi, mul, div, mflo), and memory (lw, sw) are all encoded as 32-bit MIPS instructions.
