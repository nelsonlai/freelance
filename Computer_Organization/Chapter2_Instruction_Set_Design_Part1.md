# CHAPTER 2: INSTRUCTION SET DESIGN (PART 1)
## Introduction to Computer Organization (CCIT4026)
### HKU SPACE Community College

---

## TABLE OF CONTENTS

1. [Introduction to MIPS Architecture](#21-introduction-to-mips-architecture)
2. [MIPS Registers](#22-mips-registers)
3. [MIPS Memory Organization](#23-mips-memory-organization)
4. [Basic MIPS Instructions](#24-basic-mips-instructions)
5. [Data Transfer Instructions](#25-data-transfer-instructions)
6. [Instruction Formats](#26-instruction-formats)
7. [Practice Problems](#27-practice-problems---chapter-2)

---

## 2.1 Introduction to MIPS Architecture

### Why MIPS?

MIPS (Microprocessor without Interlocked Pipeline Stages) is ideal for learning computer organization:

- **Reduced Instruction Set Computer (RISC)** architecture
- Simple, elegant instruction set
- Regular instruction formats
- Educational and industrial use
- Easy to understand and teach
- Still used in embedded systems

### MIPS Design Philosophy

The MIPS architecture follows four key design principles:

#### 1. Simplicity Favors Regularity
- Uniform instruction format
- Makes hardware simpler
- Easier to decode and execute

#### 2. Smaller is Faster
- Limited number of registers (32)
- Fast register access
- Trade-off: flexibility vs. speed

#### 3. Good Design Demands Good Compromises
- Three instruction formats (not one or many)
- Balance between simplicity and functionality

#### 4. Make the Common Case Fast
- Optimize frequent operations
- Accept slower rare operations

### RISC vs. CISC

| Feature | RISC (MIPS) | CISC (x86) |
|---------|-------------|------------|
| Instruction size | Fixed (32 bits) | Variable |
| Instruction complexity | Simple | Complex |
| Number of instructions | Fewer | Many more |
| Addressing modes | Few | Many |
| Execution time | One cycle (ideally) | Multiple cycles |
| Code density | Lower | Higher |
| Hardware complexity | Simpler | More complex |

---

## 2.2 MIPS Registers

### Register Organization

MIPS has **32 general-purpose registers**, each **32 bits** (4 bytes) wide.

**Why 32 registers?**
- Enough for most programs
- Simpler hardware (smaller is faster)
- Can be encoded in 5 bits (2^5 = 32)

### Register Naming Conventions

| Register | Number | Name | Usage | Preserved on Call? |
|----------|--------|------|-------|-------------------|
| `$zero` | 0 | Zero | Constant 0 | N/A |
| `$at` | 1 | Assembler Temporary | Reserved for assembler | No |
| `$v0-$v1` | 2-3 | Values | Function return values | No |
| `$a0-$a3` | 4-7 | Arguments | Function arguments | No |
| `$t0-$t7` | 8-15 | Temporaries | Temporary variables | No |
| `$s0-$s7` | 16-23 | Saved | Saved across calls | **Yes** |
| `$t8-$t9` | 24-25 | Temporaries | More temporaries | No |
| `$k0-$k1` | 26-27 | Kernel | OS kernel use | N/A |
| `$gp` | 28 | Global Pointer | Points to static data | Yes |
| `$sp` | 29 | Stack Pointer | Points to stack top | **Yes** |
| `$fp` | 30 | Frame Pointer | Points to stack frame | Yes |
| `$ra` | 31 | Return Address | Function return address | **Yes** |

### Special Purpose Registers

**Not directly accessible as general registers:**

- **PC (Program Counter)**: Holds address of current instruction
- **HI**: Stores high 32 bits of multiplication or division remainder
- **LO**: Stores low 32 bits of multiplication or division quotient

### Register Usage Guidelines

**Temporary Registers (`$t0-$t9`):**
- Use for short-lived values
- Not preserved across function calls
- Caller must save if needed

**Saved Registers (`$s0-$s7`):**
- Use for values needed across function calls
- Callee must save and restore
- More reliable but slower (stack operations)

**Example:**
```assembly
# Using temporary register
li   $t0, 42        # Temporary value
add  $t1, $t0, $t0  # Use immediately

# Using saved register
li   $s0, 42        # Value needed later
jal  some_function  # $s0 preserved
add  $t1, $s0, $s0  # $s0 still contains 42
```

### Teaching Tip:
Create a visual poster showing register names and uses for classroom reference. Use colors to distinguish register types.

---

## 2.3 MIPS Memory Organization

### Memory Layout (32-bit addresses)

```
0xFFFFFFFF  ┌─────────────────────┐
            │   Kernel Space      │  Reserved for OS
0x80000000  ├─────────────────────┤
            │   Stack             │  ← $sp (grows downward ↓)
            │         ↓           │  Function calls, local vars
            ├─────────────────────┤
            │    (unused)         │  Gap between stack and heap
            ├─────────────────────┤
            │         ↑           │  Dynamic allocation
            │   Heap (Dynamic)    │  (grows upward ↑)
0x10010000  ├─────────────────────┤
            │   Static Data       │  ← .data segment
            │   (.data)           │  Global variables, strings
0x10000000  ├─────────────────────┤
            │   Text (Code)       │  ← .text segment
            │   (.text)           │  Program instructions
0x00400000  ├─────────────────────┤
            │   Reserved          │  Exception handlers
0x00000000  └─────────────────────┘
```

### Memory Segments

#### 1. Text Segment (0x00400000)
- Contains program instructions
- Read-only (prevents self-modifying code)
- Starts at address 0x00400000

#### 2. Data Segment (0x10000000)
- Static data (global variables)
- Initialized at program start
- Read-write access

#### 3. Heap (grows upward from ~0x10010000)
- Dynamically allocated memory
- Managed by programmer (malloc/free)
- Grows toward higher addresses

#### 4. Stack (grows downward from ~0x7FFFFFFC)
- Function call frames
- Local variables
- Return addresses
- Grows toward lower addresses

### Memory Addressing

**Key Concepts:**
- Memory is **byte-addressable** (each byte has unique address)
- Words are 4 bytes (32 bits)
- Word addresses are multiples of 4 (0, 4, 8, 12...)
- **Alignment**: Data must be stored at addresses divisible by size
  - Words at addresses divisible by 4
  - Halfwords at addresses divisible by 2

**Example:**
```
Address    Data
0x10000000  [Byte 0][Byte 1][Byte 2][Byte 3]  ← Word 0
0x10000004  [Byte 4][Byte 5][Byte 6][Byte 7]  ← Word 1
0x10000008  [Byte 8][Byte 9][Byte A][Byte B]  ← Word 2
```

### Endianness

**MIPS supports both, but typically uses Big-Endian:**

- **Big-Endian**: Most significant byte at lowest address
- **Little-Endian**: Least significant byte at lowest address

**Example: Storing 0x12345678**

```
Big-Endian (MIPS typical):
Address: 0x1000  0x1001  0x1002  0x1003
Value:     12      34      56      78

Little-Endian:
Address: 0x1000  0x1001  0x1002  0x1003
Value:     78      56      34      12
```

---

## 2.4 Basic MIPS Instructions

### Arithmetic Instructions

#### Addition

**Signed Addition:**
```assembly
add  $t0, $t1, $t2    # $t0 = $t1 + $t2
addi $t0, $t1, 100    # $t0 = $t1 + 100 (immediate)
```

**Unsigned Addition (no overflow exception):**
```assembly
addu  $t0, $t1, $t2   # $t0 = $t1 + $t2 (unsigned)
addiu $t0, $t1, 100   # $t0 = $t1 + 100 (unsigned immediate)
```

**Important Notes:**
- `add` generates exception on overflow
- `addu` does not check overflow
- `addiu` is commonly used (even with signed values)
- Immediate value is **16-bit signed** (-32768 to 32767)

#### Subtraction

```assembly
sub  $t0, $t1, $t2    # $t0 = $t1 - $t2
subu $t0, $t1, $t2    # $t0 = $t1 - $t2 (unsigned)
```

**Note:** No immediate subtract instruction
```assembly
# To subtract immediate, use negative:
addi $t0, $t1, -100   # $t0 = $t1 - 100
```

#### Examples

**Example 1: Simple arithmetic**
```assembly
# Calculate: result = (a + b) - c
# Assume: $s0=a, $s1=b, $s2=c, $s3=result

add  $t0, $s0, $s1    # $t0 = a + b
sub  $s3, $t0, $s2    # result = (a+b) - c
```

**Example 2: Multiply by constant**
```assembly
# Multiply by 5: x * 5 = x * 4 + x
# Assume: $s0=x, $s1=result

sll  $t0, $s0, 2      # $t0 = x * 4 (shift left 2)
add  $s1, $t0, $s0    # result = x*4 + x = x*5
```

### Logical Instructions

#### AND (Bitwise AND)

```assembly
and  $t0, $t1, $t2    # $t0 = $t1 & $t2
andi $t0, $t1, 0xFF   # $t0 = $t1 & 0xFF
```

**Uses:**
- Masking bits (extracting specific bits)
- Clearing bits

**Example: Extract lower 8 bits**
```assembly
li   $t0, 0x12345678
andi $t1, $t0, 0xFF   # $t1 = 0x00000078
```

#### OR (Bitwise OR)

```assembly
or   $t0, $t1, $t2    # $t0 = $t1 | $t2
ori  $t0, $t1, 0xFF   # $t0 = $t1 | 0xFF
```

**Uses:**
- Setting bits
- Combining bit patterns

**Example: Set lower 8 bits to 1**
```assembly
li   $t0, 0x12345600
ori  $t1, $t0, 0xFF   # $t1 = 0x123456FF
```

#### NOR (Bitwise NOR - NOT OR)

```assembly
nor  $t0, $t1, $t2    # $t0 = ~($t1 | $t2)
```

**Uses:**
- Bitwise NOT: `nor $t0, $t1, $zero` (NOT $t1)
- Inverting all bits

**Example: Bitwise NOT**
```assembly
li   $t1, 0x0000FFFF
nor  $t0, $t1, $zero  # $t0 = 0xFFFF0000
```

#### XOR (Bitwise Exclusive OR)

```assembly
xor  $t0, $t1, $t2    # $t0 = $t1 ^ $t2
xori $t0, $t1, 0xFF   # $t0 = $t1 ^ 0xFF
```

**Uses:**
- Toggling bits
- Checking for equality: if (a XOR b) == 0, then a == b

**Example: Toggle bits**
```assembly
li   $t0, 0b10101010
xori $t1, $t0, 0xFF   # $t1 = 0b01010101 (toggled)
```

### Shift Instructions

#### Shift Left Logical (SLL)

```assembly
sll  $t0, $t1, 4      # $t0 = $t1 << 4
```

**Effect:** Multiplies by 2^n
```
Original: 0000 0101 (5)
sll by 2: 0001 0100 (20 = 5 × 4)
```

**Uses:**
- Multiply by powers of 2
- Bit manipulation

#### Shift Right Logical (SRL)

```assembly
srl  $t0, $t1, 4      # $t0 = $t1 >> 4 (unsigned)
```

**Effect:** Divides by 2^n (unsigned)
- Fills left bits with 0

```
Original: 1010 1000 (168)
srl by 2: 0010 1010 (42 = 168 / 4)
```

#### Shift Right Arithmetic (SRA)

```assembly
sra  $t0, $t1, 4      # $t0 = $t1 >> 4 (signed)
```

**Effect:** Divides by 2^n (signed)
- Fills left bits with sign bit (preserves sign)

```
Positive:
Original: 0010 1000 (40)
sra by 2: 0000 1010 (10 = 40 / 4)

Negative:
Original: 1010 1000 (-88 in two's complement)
sra by 2: 1110 1010 (-22)
```

**Use Cases:**

```assembly
# Multiply by 2
sll  $t0, $t1, 1      # $t0 = $t1 × 2

# Multiply by 4
sll  $t0, $t1, 2      # $t0 = $t1 × 4

# Divide by 8 (unsigned)
srl  $t0, $t1, 3      # $t0 = $t1 / 8

# Divide by 8 (signed)
sra  $t0, $t1, 3      # $t0 = $t1 / 8 (preserves sign)
```

---

## 2.5 Data Transfer Instructions

### Load Instructions

#### Load Word (lw)

```assembly
lw   $t0, offset($t1)  # $t0 = Memory[$t1 + offset]
```

**Example:**
```assembly
.data
value: .word 42

.text
la   $t1, value       # Load address of value
lw   $t0, 0($t1)      # Load word at address
                      # $t0 now contains 42
```

#### Load Halfword (lh/lhu)

```assembly
lh   $t0, offset($t1)  # Load 16 bits, sign-extend
lhu  $t0, offset($t1)  # Load 16 bits, zero-extend
```

**Difference:**
```
Memory: 0xFFFF (at address $t1)

lh  $t0, 0($t1)  → $t0 = 0xFFFFFFFF (sign-extended)
lhu $t0, 0($t1)  → $t0 = 0x0000FFFF (zero-extended)
```

#### Load Byte (lb/lbu)

```assembly
lb   $t0, offset($t1)  # Load 8 bits, sign-extend
lbu  $t0, offset($t1)  # Load 8 bits, zero-extend
```

**Example:**
```
Memory: 0x80 (at address $t1)

lb  $t0, 0($t1)  → $t0 = 0xFFFFFF80 (sign-extended, -128)
lbu $t0, 0($t1)  → $t0 = 0x00000080 (zero-extended, 128)
```

### Store Instructions

#### Store Word (sw)

```assembly
sw   $t0, offset($t1)  # Memory[$t1 + offset] = $t0
```

**Example:**
```assembly
li   $t0, 42          # Value to store
la   $t1, location    # Address to store at
sw   $t0, 0($t1)      # Store word
```

#### Store Halfword (sh)

```assembly
sh   $t0, offset($t1)  # Store lower 16 bits
```

#### Store Byte (sb)

```assembly
sb   $t0, offset($t1)  # Store lower 8 bits
```

### Array Access Examples

#### Accessing Array Elements

**C Code:**
```c
int A[10];
A[0] = 5;
A[3] = 12;
int x = A[3];
```

**MIPS Assembly:**
```assembly
.data
A:      .space 40      # 10 integers × 4 bytes

.text
        la   $t0, A        # Base address of A
        
        # A[0] = 5
        li   $t1, 5
        sw   $t1, 0($t0)   # Offset = 0 × 4 = 0
        
        # A[3] = 12
        li   $t1, 12
        sw   $t1, 12($t0)  # Offset = 3 × 4 = 12
        
        # x = A[3]
        lw   $s0, 12($t0)  # $s0 = A[3]
```

#### Array Traversal

**C Code:**
```c
for (int i = 0; i < 5; i++) {
    A[i] = i * 2;
}
```

**MIPS Assembly:**
```assembly
        la   $t0, A        # Base address
        li   $t1, 0        # i = 0
        li   $t2, 5        # limit
        
loop:   bge  $t1, $t2, done
        
        # Calculate offset
        sll  $t3, $t1, 2   # offset = i × 4
        add  $t4, $t0, $t3 # address = base + offset
        
        # Calculate value
        sll  $t5, $t1, 1   # value = i × 2
        
        # Store
        sw   $t5, 0($t4)   # A[i] = i × 2
        
        addi $t1, $t1, 1   # i++
        j    loop
done:
```

### Load Upper Immediate (lui)

```assembly
lui  $t0, 0x1234      # $t0 = 0x12340000
```

**Use:** Load 16-bit constant into upper 16 bits
- Lower 16 bits become 0
- Combined with `ori` to load 32-bit constant

**Example: Load 32-bit constant**
```assembly
# Load 0x12345678 into $t0
lui  $t0, 0x1234      # $t0 = 0x12340000
ori  $t0, $t0, 0x5678 # $t0 = 0x12345678
```

---

## 2.6 Instruction Formats

MIPS instructions are **always 32 bits** long and come in **three formats**:

### R-Type (Register) Format

Used for arithmetic and logical operations with three register operands.

```
┌─────────┬─────┬─────┬─────┬───────┬────────┐
│   op    │ rs  │ rt  │ rd  │ shamt │  funct │
│ 6 bits  │5bits│5bits│5bits│5 bits │ 6 bits │
└─────────┴─────┴─────┴─────┴───────┴────────┘
```

**Fields:**
- **op (opcode)**: Operation type (always 0 for R-type)
- **rs**: First source register
- **rt**: Second source register  
- **rd**: Destination register
- **shamt**: Shift amount (for shift operations)
- **funct**: Function code (specifies exact operation)

**Example: `add $t0, $t1, $t2`**

```
┌─────────┬─────┬─────┬─────┬───────┬────────┐
│ 000000  │01001│01010│01000│ 00000 │ 100000 │
│   (0)   │ ($t1)│($t2)│($t0)│  (0)  │ (add)  │
└─────────┴─────┴─────┴─────┴───────┴────────┘

Binary: 000000 01001 01010 01000 00000 100000
Hex: 0x012A4020
```

**Common R-Type Instructions:**
- `add, addu, sub, subu`
- `and, or, nor, xor`
- `slt, sltu`
- `sll, srl, sra`

### I-Type (Immediate) Format

Used for operations with immediate values, load/store, and branches.

```
┌─────────┬─────┬─────┬───────────────────────┐
│   op    │ rs  │ rt  │      immediate        │
│ 6 bits  │5bits│5bits│      16 bits          │
└─────────┴─────┴─────┴───────────────────────┘
```

**Fields:**
- **op**: Operation code (specifies instruction)
- **rs**: Source register
- **rt**: Target/destination register
- **immediate**: 16-bit constant or address offset

**Example: `addi $t0, $t1, 100`**

```
┌─────────┬─────┬─────┬───────────────────────┐
│ 001000  │01001│01000│ 0000000001100100      │
│ (addi)  │($t1)│($t0)│       (100)           │
└─────────┴─────┴─────┴───────────────────────┘

Binary: 001000 01001 01000 0000000001100100
Hex: 0x21280064
```

**Common I-Type Instructions:**
- Arithmetic: `addi, addiu`
- Logical: `andi, ori, xori`
- Load/Store: `lw, sw, lh, sh, lb, sb`
- Branch: `beq, bne`
- Compare: `slti, sltiu`

### J-Type (Jump) Format

Used for jump instructions.

```
┌─────────┬─────────────────────────────────────┐
│   op    │            address                  │
│ 6 bits  │           26 bits                   │
└─────────┴─────────────────────────────────────┘
```

**Fields:**
- **op**: Operation code (2 for `j`, 3 for `jal`)
- **address**: 26-bit jump target address

**Example: `j label`**

```
┌─────────┬─────────────────────────────────────┐
│ 000010  │     (target address / 4)            │
│   (j)   │          26 bits                    │
└─────────┴─────────────────────────────────────┘
```

**Address Calculation:**
```
Target Address = (PC+4)[31:28] | (address field << 2)
```

**Common J-Type Instructions:**
- `j` (jump)
- `jal` (jump and link)

### Format Summary Table

| Format | Instructions | Example |
|--------|-------------|---------|
| R-Type | Arithmetic, Logical, Shifts | `add $t0, $t1, $t2` |
| I-Type | Immediate ops, Load/Store, Branch | `addi $t0, $t1, 100` |
| J-Type | Jumps | `j label` |

---

## 2.7 Practice Problems - Chapter 2

### Problem 1: Basic Arithmetic

**Task:** Write MIPS code to compute: `f = (g + h) - (i + j)`

**Given:** $s0=f, $s1=g, $s2=h, $s3=i, $s4=j

**Solution:**
```assembly
add  $t0, $s1, $s2    # $t0 = g + h
add  $t1, $s3, $s4    # $t1 = i + j
sub  $s0, $t0, $t1    # f = (g+h) - (i+j)
```

### Problem 2: Array Access

**Task:** Load value from array A[8] into register $t1

**Given:** Base address of A in $t0

**Solution:**
```assembly
lw   $t1, 32($t0)     # $t1 = A[8]
                      # Offset = 8 × 4 = 32 bytes
```

### Problem 3: Bit Manipulation

**Task:** Extract bits 8-15 from $t0 and store in $t1

**Solution:**
```assembly
srl  $t1, $t0, 8      # Shift right 8 positions
andi $t1, $t1, 0xFF   # Mask to get 8 bits
```

### Problem 4: Constant Loading

**Task:** Load the 32-bit constant 0xABCD1234 into $t0

**Solution:**
```assembly
lui  $t0, 0xABCD      # Upper 16 bits
ori  $t0, $t0, 0x1234 # Lower 16 bits
```

### Problem 5: Array Sum

**Task:** Calculate sum of array A with 5 elements

**Solution:**
```assembly
.data
A:      .word 10, 20, 30, 40, 50

.text
        la   $t0, A        # Base address
        li   $t1, 0        # sum = 0
        li   $t2, 5        # count
        li   $t3, 0        # i = 0
        
loop:   bge  $t3, $t2, done
        sll  $t4, $t3, 2   # offset = i × 4
        add  $t5, $t0, $t4 # address
        lw   $t6, 0($t5)   # load A[i]
        add  $t1, $t1, $t6 # sum += A[i]
        addi $t3, $t3, 1   # i++
        j    loop
done:   # $t1 contains sum = 150
```

---

## KEY TAKEAWAYS

1. **MIPS is a RISC architecture** with simple, regular instructions

2. **32 general-purpose registers**, each 32 bits wide

3. **Register conventions:**
   - `$t` registers: temporaries (not preserved)
   - `$s` registers: saved (preserved across calls)
   - `$a` registers: function arguments
   - `$v` registers: return values

4. **Memory is byte-addressable**, words are 4 bytes

5. **Three instruction formats:** R-type, I-type, J-type

6. **All instructions are 32 bits** long

---

## NEXT CHAPTER

**[Chapter 3: Instruction Set Design (Part 2)](Chapter3_Instruction_Set_Design_Part2.md)**
- Control Flow Instructions
- Implementing High-Level Constructs
- Multiplication and Division
- Addressing Modes
- Pseudo-instructions

---

*This material is part of CCIT4026: Introduction to Computer Organization*  
*HKU SPACE Community College*  
*Chapter 2 of 5*
