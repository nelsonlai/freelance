# COMPREHENSIVE TEACHING MATERIAL
## Introduction to Computer Organization (CCIT4026)
### HKU SPACE Community College

---

## TABLE OF CONTENTS

1. [Course Overview](#course-overview)
2. [Chapter 1: Introduction](#chapter-1-introduction)
3. [Chapter 2: Instruction Set Design (Part 1)](#chapter-2-instruction-set-design-part-1)
4. [Chapter 3: Instruction Set Design (Part 2)](#chapter-3-instruction-set-design-part-2)
5. [Chapter 4: Instruction Set Design (Part 3)](#chapter-4-instruction-set-design-part-3)
6. [Chapter 5: Instruction Set Design (Part 4)](#chapter-5-instruction-set-design-part-4)
7. [Laboratory Work](#laboratory-work)
8. [Teaching Strategies](#teaching-strategies)
9. [Assessment Methods](#assessment-methods)
10. [Additional Resources](#additional-resources)

---

## COURSE OVERVIEW

### Learning Objectives
By the end of this course, students will be able to:

1. **Understand Computer Architecture Fundamentals**
   - Explain the basic components of computer systems
   - Describe the von Neumann architecture
   - Understand the relationship between hardware and software

2. **Master MIPS Assembly Programming**
   - Write, assemble, and debug MIPS assembly programs
   - Understand instruction formats (R-type, I-type, J-type)
   - Implement control structures and data manipulations

3. **Comprehend Instruction Set Architecture (ISA)**
   - Analyze instruction encoding and decoding
   - Understand addressing modes
   - Evaluate design trade-offs in ISA

4. **Apply Practical Skills**
   - Use MARS simulator for assembly programming
   - Debug and optimize assembly code
   - Translate high-level constructs to assembly

### Prerequisites
- Basic programming knowledge (C, Python, or Java)
- Understanding of binary and hexadecimal number systems
- Fundamental logic operations

### Course Tools
- **MARS (MIPS Assembler and Runtime Simulator)**: Primary development environment
- Text editor with syntax highlighting
- Documentation and reference materials

---

## CHAPTER 1: INTRODUCTION

### 1.1 What is Computer Organization?

#### Teaching Points:
**Computer Organization** refers to the operational units and their interconnections that realize the architectural specifications. It deals with how components are implemented and connected.

**Key Concepts:**
- **Computer Architecture vs. Computer Organization**
  - Architecture: What the system does (programmer's view)
  - Organization: How the system does it (implementer's view)

**Example for Students:**
```
Think of a car:
- Architecture = Steering wheel, pedals, gear shift (user interface)
- Organization = Engine, transmission, drive shaft (internal implementation)
```

### 1.2 The von Neumann Architecture

#### Essential Components:

1. **Central Processing Unit (CPU)**
   - Control Unit (CU): Directs operations
   - Arithmetic Logic Unit (ALU): Performs computations
   - Registers: High-speed temporary storage

2. **Memory**
   - Primary Memory (RAM): Volatile, fast access
   - Secondary Memory: Non-volatile, larger capacity
   - Memory Hierarchy: Registers → Cache → RAM → Disk

3. **Input/Output (I/O) Devices**
   - Input: Keyboard, mouse, sensors
   - Output: Monitor, printer, actuators

4. **System Bus**
   - Data Bus: Transfers data
   - Address Bus: Specifies memory locations
   - Control Bus: Carries control signals

#### Teaching Activity:
Draw the von Neumann architecture diagram on the board and trace the execution of a simple instruction (e.g., ADD operation).

### 1.3 Number Systems and Data Representation

#### Binary Number System
```
Decimal: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
Binary:  0, 1

Examples:
Decimal 13 = 1101 (binary) = 1×2³ + 1×2² + 0×2¹ + 1×2⁰
```

#### Hexadecimal Number System
```
0-9, A(10), B(11), C(12), D(13), E(14), F(15)

Examples:
0xFF = 255 (decimal)
0x10 = 16 (decimal)
```

#### Signed Number Representations

1. **Sign-Magnitude**
   - First bit is sign (0=positive, 1=negative)
   - Remaining bits are magnitude
   - Example: +5 = 0101, -5 = 1101

2. **Two's Complement** (Most Common)
   - Positive numbers: Same as unsigned
   - Negative numbers: Invert bits and add 1
   ```
   +5 = 0101
   -5: Invert → 1010, Add 1 → 1011
   ```

#### Practice Problems:
1. Convert decimal 42 to binary
2. Convert binary 11010110 to hexadecimal
3. Find two's complement of -15 (8-bit)

### 1.4 Performance Metrics

#### CPU Performance
```
Execution Time = (Instruction Count × CPI × Clock Cycle Time)

Where:
- CPI = Cycles Per Instruction
- Clock Cycle Time = 1 / Clock Frequency
```

#### Example Calculation:
```
Program with:
- 1,000,000 instructions
- Average CPI = 2.5
- Clock frequency = 2 GHz

Execution Time = 1,000,000 × 2.5 × (1/2,000,000,000)
               = 1.25 milliseconds
```

### 1.5 Levels of Programming Languages

```
High Level:     Python, Java, C
                    ↓ (Compiler)
Assembly:       MIPS, x86, ARM
                    ↓ (Assembler)
Machine Code:   Binary (010101...)
                    ↓ (Execution)
Hardware:       Physical circuits
```

---

## CHAPTER 2: INSTRUCTION SET DESIGN (PART 1)

### 2.1 Introduction to MIPS Architecture

#### Why MIPS?
- **Reduced Instruction Set Computer (RISC)** architecture
- Simple, elegant instruction set
- Educational and industrial use
- Easy to understand and teach

#### MIPS Philosophy:
1. Simplicity favors regularity
2. Smaller is faster
3. Good design demands good compromises
4. Make the common case fast

### 2.2 MIPS Registers

#### Register Organization
MIPS has **32 general-purpose registers**, each 32 bits wide.

**Register Naming Conventions:**

| Register | Number | Usage                           | Preserved on Call? |
|----------|--------|----------------------------------|-------------------|
| `$zero`  | 0      | Constant 0                      | N/A               |
| `$at`    | 1      | Assembler temporary             | No                |
| `$v0-$v1`| 2-3    | Function return values          | No                |
| `$a0-$a3`| 4-7    | Function arguments              | No                |
| `$t0-$t7`| 8-15   | Temporary variables             | No                |
| `$s0-$s7`| 16-23  | Saved variables                 | Yes               |
| `$t8-$t9`| 24-25  | More temporaries                | No                |
| `$k0-$k1`| 26-27  | Kernel (OS) reserved            | N/A               |
| `$gp`    | 28     | Global pointer                  | Yes               |
| `$sp`    | 29     | Stack pointer                   | Yes               |
| `$fp`    | 30     | Frame pointer                   | Yes               |
| `$ra`    | 31     | Return address                  | Yes               |

**Special Registers:**
- **PC (Program Counter)**: Not directly accessible, holds address of current instruction
- **HI/LO**: Store results of multiplication and division

#### Teaching Tip:
Create a visual poster showing register names and uses for classroom reference.

### 2.3 MIPS Memory Organization

```
Memory Layout (32-bit addresses):

0xFFFFFFFF  ┌─────────────────────┐
            │   Kernel Space      │
0x80000000  ├─────────────────────┤
            │   Stack             │ ← $sp (grows downward)
            │         ↓           │
            ├─────────────────────┤
            │    (unused)         │
            ├─────────────────────┤
            │         ↑           │
            │   Heap (Dynamic)    │ (grows upward)
0x10010000  ├─────────────────────┤
            │   Static Data       │ ← .data segment
0x10000000  ├─────────────────────┤
            │   Text (Code)       │ ← .text segment
0x00400000  ├─────────────────────┤
            │   Reserved          │
0x00000000  └─────────────────────┘
```

### 2.4 Basic MIPS Instructions

#### Arithmetic Instructions

**Addition:**
```assembly
add  $t0, $t1, $t2    # $t0 = $t1 + $t2
addi $t0, $t1, 100    # $t0 = $t1 + 100 (immediate)
```

**Subtraction:**
```assembly
sub  $t0, $t1, $t2    # $t0 = $t1 - $t2
```

**Important Note:**
- `add` and `sub` generate overflow exceptions
- `addu` and `subu` are unsigned versions (no overflow checking)

#### Logical Instructions

**AND:**
```assembly
and  $t0, $t1, $t2    # $t0 = $t1 & $t2
andi $t0, $t1, 0xFF   # $t0 = $t1 & 0xFF
```

**OR:**
```assembly
or   $t0, $t1, $t2    # $t0 = $t1 | $t2
ori  $t0, $t1, 0xFF   # $t0 = $t1 | 0xFF
```

**NOR (NOT OR):**
```assembly
nor  $t0, $t1, $t2    # $t0 = ~($t1 | $t2)
```

**XOR:**
```assembly
xor  $t0, $t1, $t2    # $t0 = $t1 ^ $t2
```

#### Shift Instructions

```assembly
sll  $t0, $t1, 4      # Shift left logical: $t0 = $t1 << 4
srl  $t0, $t1, 4      # Shift right logical: $t0 = $t1 >> 4
sra  $t0, $t1, 4      # Shift right arithmetic (sign-extended)
```

**Use Cases:**
- Multiply by 2: `sll $t0, $t1, 1`
- Divide by 4: `srl $t0, $t1, 2`

### 2.5 Data Transfer Instructions

#### Load Instructions

**Load Word (lw):**
```assembly
lw   $t0, 0($t1)      # $t0 = Memory[$t1 + 0]
lw   $t0, 100($t1)    # $t0 = Memory[$t1 + 100]
```

**Load Halfword:**
```assembly
lh   $t0, 0($t1)      # Load 16 bits (sign-extended)
lhu  $t0, 0($t1)      # Load 16 bits (zero-extended)
```

**Load Byte:**
```assembly
lb   $t0, 0($t1)      # Load 8 bits (sign-extended)
lbu  $t0, 0($t1)      # Load 8 bits (zero-extended)
```

#### Store Instructions

**Store Word (sw):**
```assembly
sw   $t0, 0($t1)      # Memory[$t1 + 0] = $t0
sw   $t0, 100($t1)    # Memory[$t1 + 100] = $t0
```

**Store Halfword and Byte:**
```assembly
sh   $t0, 0($t1)      # Store lower 16 bits
sb   $t0, 0($t1)      # Store lower 8 bits
```

#### Memory Addressing Example
```assembly
# Accessing array element: A[3]
# Assuming $t0 has base address of A, each element is 4 bytes

lw   $t1, 12($t0)     # Load A[3] (offset = 3 × 4 = 12)
```

### 2.6 Instruction Formats

MIPS instructions are **32 bits** long and come in three formats:

#### R-Type (Register) Format
```
|  op   |  rs  |  rt  |  rd  | shamt | funct |
| 6 bits| 5 bits| 5 bits| 5 bits| 5 bits| 6 bits|
```

- **op**: Opcode (operation code)
- **rs**: First source register
- **rt**: Second source register
- **rd**: Destination register
- **shamt**: Shift amount
- **funct**: Function code (specifies exact operation)

**Example: `add $t0, $t1, $t2`**
```
| 000000 | 01001 | 01010 | 01000 | 00000 | 100000 |
   (op)    ($t1)  ($t2)  ($t0)  (shamt)  (add)
```

#### I-Type (Immediate) Format
```
|  op   |  rs  |  rt  |    immediate    |
| 6 bits| 5 bits| 5 bits|    16 bits     |
```

**Example: `addi $t0, $t1, 100`**
```
| 001000 | 01001 | 01000 | 0000000001100100 |
  (addi)   ($t1)  ($t0)        (100)
```

#### J-Type (Jump) Format
```
|  op   |        address          |
| 6 bits|       26 bits           |
```

**Example: `j label`**
```
| 000010 |    target address       |
   (j)
```

### 2.7 Practice Problems - Chapter 2

**Problem 1:** Write MIPS code to compute: `f = (g + h) - (i + j)`
```assembly
# Assume: $s0=f, $s1=g, $s2=h, $s3=i, $s4=j

add  $t0, $s1, $s2    # $t0 = g + h
add  $t1, $s3, $s4    # $t1 = i + j
sub  $s0, $t0, $t1    # f = $t0 - $t1
```

**Problem 2:** Load value from array A[8] into register
```assembly
# Base address of A in $t0

lw   $t1, 32($t0)     # $t1 = A[8] (offset = 8 × 4)
```

---

## CHAPTER 3: INSTRUCTION SET DESIGN (PART 2)

### 3.1 Control Flow Instructions

#### Conditional Branches

**Branch if Equal (beq):**
```assembly
beq  $t0, $t1, label   # if ($t0 == $t1) goto label
```

**Branch if Not Equal (bne):**
```assembly
bne  $t0, $t1, label   # if ($t0 != $t1) goto label
```

**Set on Less Than (slt):**
```assembly
slt  $t0, $t1, $t2     # $t0 = ($t1 < $t2) ? 1 : 0
slti $t0, $t1, 100     # $t0 = ($t1 < 100) ? 1 : 0
```

**Combined with Branch:**
```assembly
slt  $t0, $t1, $t2     # Set $t0 if $t1 < $t2
bne  $t0, $zero, label # Branch if $t0 != 0
```

#### Unconditional Jumps

**Jump (j):**
```assembly
j    label             # Unconditional jump to label
```

**Jump and Link (jal):**
```assembly
jal  function          # Jump to function, save return address in $ra
```

**Jump Register (jr):**
```assembly
jr   $ra               # Jump to address in $ra (return from function)
```

### 3.2 Implementing High-Level Constructs

#### If-Then-Else Statement

**C Code:**
```c
if (a == b)
    c = d + e;
else
    c = d - e;
```

**MIPS Assembly:**
```assembly
# Assume: $s0=a, $s1=b, $s2=c, $s3=d, $s4=e

        bne  $s0, $s1, else    # if (a != b) goto else
        add  $s2, $s3, $s4     # c = d + e
        j    endif             # skip else part
else:   sub  $s2, $s3, $s4     # c = d - e
endif:  # continue here
```

#### While Loop

**C Code:**
```c
while (i < n) {
    sum = sum + i;
    i = i + 1;
}
```

**MIPS Assembly:**
```assembly
# Assume: $s0=i, $s1=n, $s2=sum

while:  slt  $t0, $s0, $s1     # $t0 = (i < n)
        beq  $t0, $zero, endw  # if !(i < n) exit loop
        add  $s2, $s2, $s0     # sum = sum + i
        addi $s0, $s0, 1       # i = i + 1
        j    while             # repeat
endw:   # continue here
```

#### For Loop

**C Code:**
```c
for (i = 0; i < 10; i++) {
    sum = sum + i;
}
```

**MIPS Assembly:**
```assembly
# Assume: $s0=i, $s1=sum

        li   $s0, 0            # i = 0
        li   $t0, 10           # loop limit
for:    slt  $t1, $s0, $t0     # i < 10?
        beq  $t1, $zero, endf  # exit if false
        add  $s1, $s1, $s0     # sum = sum + i
        addi $s0, $s0, 1       # i++
        j    for               # repeat
endf:   # continue here
```

### 3.3 Multiplication and Division

#### Multiplication

**Multiply:**
```assembly
mult  $t0, $t1         # HI:LO = $t0 × $t1 (64-bit result)
mflo  $t2              # Move from LO to $t2 (lower 32 bits)
mfhi  $t3              # Move from HI to $t3 (upper 32 bits)
```

**Multiply Unsigned:**
```assembly
multu $t0, $t1         # HI:LO = $t0 × $t1 (unsigned)
```

**Pseudo-instruction (MARS):**
```assembly
mul   $t0, $t1, $t2    # $t0 = $t1 × $t2 (simplified)
```

#### Division

**Divide:**
```assembly
div   $t0, $t1         # LO = $t0 / $t1 (quotient)
                       # HI = $t0 % $t1 (remainder)
mflo  $t2              # Get quotient
mfhi  $t3              # Get remainder
```

**Example: Divide by 10**
```assembly
li    $t0, 157         # dividend
li    $t1, 10          # divisor
div   $t0, $t1         # 157 / 10
mflo  $t2              # $t2 = 15 (quotient)
mfhi  $t3              # $t3 = 7 (remainder)
```

### 3.4 Addressing Modes

#### 1. Register Addressing
```assembly
add  $t0, $t1, $t2     # All operands are registers
```

#### 2. Immediate Addressing
```assembly
addi $t0, $t1, 100     # 100 is an immediate value
```

#### 3. Base (Displacement) Addressing
```assembly
lw   $t0, 100($t1)     # Address = $t1 + 100
```

#### 4. PC-Relative Addressing
```assembly
beq  $t0, $t1, label   # Address = PC + 4 + offset
```

#### 5. Pseudo-Direct Addressing
```assembly
j    label             # Address = (PC+4)[31:28] | address[25:0] << 2
```

### 3.5 Pseudo-instructions

MARS supports pseudo-instructions that are translated into real MIPS instructions.

**Load Immediate:**
```assembly
li   $t0, 100          # Translates to: addi $t0, $zero, 100
li   $t0, 0x12345678   # Translates to: lui and ori
```

**Load Address:**
```assembly
la   $t0, label        # Load address of label into $t0
```

**Move:**
```assembly
move $t0, $t1          # Translates to: add $t0, $t1, $zero
```

**Branch Comparisons:**
```assembly
blt  $t0, $t1, label   # Branch if less than
bgt  $t0, $t1, label   # Branch if greater than
ble  $t0, $t1, label   # Branch if less than or equal
bge  $t0, $t1, label   # Branch if greater than or equal
```

### 3.6 Practice Problems - Chapter 3

**Problem 1:** Implement if statement
```c
if (x > y)
    z = x;
else
    z = y;
```

**Solution:**
```assembly
# $s0=x, $s1=y, $s2=z

        slt  $t0, $s1, $s0     # $t0 = (y < x)
        bne  $t0, $zero, then  # if (x > y) goto then
        move $s2, $s1          # z = y
        j    endif
then:   move $s2, $s0          # z = x
endif:
```

**Problem 2:** Array sum
```c
int sum = 0;
for (int i = 0; i < 10; i++) {
    sum += A[i];
}
```

**Solution:**
```assembly
# $s0=sum, $s1=base address of A

        li   $s0, 0            # sum = 0
        li   $t0, 0            # i = 0
        li   $t1, 10           # limit
loop:   slt  $t2, $t0, $t1     # i < 10?
        beq  $t2, $zero, end   # exit if false
        
        sll  $t3, $t0, 2       # $t3 = i × 4
        add  $t3, $t3, $s1     # $t3 = address of A[i]
        lw   $t4, 0($t3)       # $t4 = A[i]
        add  $s0, $s0, $t4     # sum += A[i]
        
        addi $t0, $t0, 1       # i++
        j    loop
end:
```

---

## CHAPTER 4: INSTRUCTION SET DESIGN (PART 3)

### 4.1 Function Calls and Stack

#### Function Call Convention

**Steps in Function Call:**
1. Caller places arguments in `$a0-$a3`
2. Caller executes `jal function`
3. Function saves registers if needed
4. Function executes
5. Function places results in `$v0-$v1`
6. Function restores saved registers
7. Function returns using `jr $ra`

#### The Stack

**Stack Operations:**
```assembly
# Push (save) register to stack
addi $sp, $sp, -4      # Allocate space
sw   $t0, 0($sp)       # Save $t0

# Pop (restore) register from stack
lw   $t0, 0($sp)       # Restore $t0
addi $sp, $sp, 4       # Deallocate space
```

**Stack Grows Downward:**
```
High Address
    │
    ├────────────┐
    │   old data │
    ├────────────┤ ← $sp (before)
    │   new data │
    ├────────────┤ ← $sp (after push)
    │            │
    ↓
Low Address
```

### 4.2 Simple Function Example

**C Code:**
```c
int add(int a, int b) {
    return a + b;
}

int main() {
    int x = add(3, 5);
}
```

**MIPS Assembly:**
```assembly
# Function: add
add_func:
        add  $v0, $a0, $a1     # $v0 = a + b
        jr   $ra               # return

# Main program
main:
        li   $a0, 3            # First argument
        li   $a1, 5            # Second argument
        jal  add_func          # Call function
        move $s0, $v0          # x = result
```

### 4.3 Function with Local Variables

**C Code:**
```c
int sum(int a, int b, int c) {
    int temp = a + b;
    return temp + c;
}
```

**MIPS Assembly:**
```assembly
sum:
        # Prologue: Save registers
        addi $sp, $sp, -8      # Allocate stack space
        sw   $s0, 4($sp)       # Save $s0
        sw   $ra, 0($sp)       # Save return address
        
        # Function body
        add  $s0, $a0, $a1     # temp = a + b
        add  $v0, $s0, $a2     # result = temp + c
        
        # Epilogue: Restore registers
        lw   $ra, 0($sp)       # Restore $ra
        lw   $s0, 4($sp)       # Restore $s0
        addi $sp, $sp, 8       # Deallocate stack
        
        jr   $ra               # return
```

### 4.4 Recursive Functions

**C Code: Factorial**
```c
int factorial(int n) {
    if (n <= 1)
        return 1;
    else
        return n * factorial(n - 1);
}
```

**MIPS Assembly:**
```assembly
factorial:
        # Prologue
        addi $sp, $sp, -8      # Allocate stack
        sw   $ra, 4($sp)       # Save return address
        sw   $a0, 0($sp)       # Save argument n
        
        # Base case: if (n <= 1)
        slti $t0, $a0, 2       # $t0 = (n < 2)
        beq  $t0, $zero, recur # if n >= 2, recurse
        
        li   $v0, 1            # return 1
        addi $sp, $sp, 8       # Deallocate (no restoration needed)
        jr   $ra               # return
        
recur:  # Recursive case
        addi $a0, $a0, -1      # n - 1
        jal  factorial         # factorial(n - 1)
        
        lw   $a0, 0($sp)       # Restore n
        lw   $ra, 4($sp)       # Restore return address
        addi $sp, $sp, 8       # Deallocate
        
        mul  $v0, $a0, $v0     # n * factorial(n-1)
        jr   $ra               # return
```

### 4.5 Nested Function Calls

**C Code:**
```c
int f(int x) {
    return g(x + 1) + g(x + 2);
}
```

**MIPS Assembly:**
```assembly
f:
        # Prologue
        addi $sp, $sp, -12     # Allocate stack
        sw   $ra, 8($sp)       # Save $ra
        sw   $s0, 4($sp)       # Save $s0 (for x)
        sw   $s1, 0($sp)       # Save $s1 (for temp)
        
        move $s0, $a0          # Save x
        
        # First call: g(x + 1)
        addi $a0, $s0, 1       # argument = x + 1
        jal  g                 # call g
        move $s1, $v0          # save result
        
        # Second call: g(x + 2)
        addi $a0, $s0, 2       # argument = x + 2
        jal  g                 # call g
        
        # Combine results
        add  $v0, $s1, $v0     # result = g(x+1) + g(x+2)
        
        # Epilogue
        lw   $s1, 0($sp)       # Restore $s1
        lw   $s0, 4($sp)       # Restore $s0
        lw   $ra, 8($sp)       # Restore $ra
        addi $sp, $sp, 12      # Deallocate
        
        jr   $ra               # return
```

### 4.6 Arrays and Pointers

#### Array Access

**C Code:**
```c
int A[10];
A[3] = 42;
```

**MIPS Assembly:**
```assembly
.data
A:      .space 40              # 10 integers × 4 bytes

.text
        la   $t0, A            # $t0 = base address
        li   $t1, 42           # value to store
        sw   $t1, 12($t0)      # A[3] = 42 (offset = 3×4)
```

#### Array Traversal

**C Code:**
```c
for (int i = 0; i < n; i++) {
    A[i] = i * 2;
}
```

**MIPS Assembly:**
```assembly
# Assume: $s0=n, $s1=base address of A

        li   $t0, 0            # i = 0
loop:   slt  $t1, $t0, $s0     # i < n?
        beq  $t1, $zero, done  # exit if false
        
        sll  $t2, $t0, 1       # $t2 = i × 2
        sll  $t3, $t0, 2       # $t3 = i × 4 (offset)
        add  $t3, $t3, $s1     # $t3 = address of A[i]
        sw   $t2, 0($t3)       # A[i] = i × 2
        
        addi $t0, $t0, 1       # i++
        j    loop
done:
```

### 4.7 Structures in MIPS

**C Code:**
```c
struct Point {
    int x;      // offset 0
    int y;      // offset 4
};

struct Point p;
p.x = 10;
p.y = 20;
```

**MIPS Assembly:**
```assembly
.data
p:      .space 8               # Structure size = 8 bytes

.text
        la   $t0, p            # $t0 = address of structure
        li   $t1, 10
        sw   $t1, 0($t0)       # p.x = 10
        li   $t1, 20
        sw   $t1, 4($t0)       # p.y = 20
```

### 4.8 Practice Problems - Chapter 4

**Problem 1:** Write a function to find maximum of two numbers

**Solution:**
```assembly
max:
        # Arguments: $a0, $a1
        # Return: $v0
        
        slt  $t0, $a0, $a1     # $t0 = ($a0 < $a1)
        bne  $t0, $zero, else  # if $a0 < $a1, goto else
        move $v0, $a0          # return $a0
        jr   $ra
else:   move $v0, $a1          # return $a1
        jr   $ra
```

**Problem 2:** Fibonacci sequence (recursive)

**Solution:**
```assembly
# int fib(int n)
fibonacci:
        # Base cases
        slti $t0, $a0, 2       # n < 2?
        beq  $t0, $zero, recur
        move $v0, $a0          # return n (0 or 1)
        jr   $ra
        
recur:  # Recursive case
        addi $sp, $sp, -12     # Allocate stack
        sw   $ra, 8($sp)
        sw   $s0, 4($sp)       # Save n
        sw   $s1, 0($sp)       # Save fib(n-1)
        
        move $s0, $a0          # Save n
        
        # fib(n-1)
        addi $a0, $s0, -1
        jal  fibonacci
        move $s1, $v0          # Save fib(n-1)
        
        # fib(n-2)
        addi $a0, $s0, -2
        jal  fibonacci
        
        add  $v0, $s1, $v0     # fib(n-1) + fib(n-2)
        
        # Restore and return
        lw   $s1, 0($sp)
        lw   $s0, 4($sp)
        lw   $ra, 8($sp)
        addi $sp, $sp, 12
        jr   $ra
```

---

## CHAPTER 5: INSTRUCTION SET DESIGN (PART 4)

### 5.1 System Calls in MARS

MARS provides system calls (syscalls) for I/O operations and other OS services.

**System Call Mechanism:**
```assembly
li   $v0, service_code     # Load service code
# Set up arguments in $a0, $a1, etc.
syscall                     # Make system call
# Result (if any) returned in $v0
```

#### Common System Call Codes

| Service | Code | Arguments | Result |
|---------|------|-----------|--------|
| Print integer | 1 | `$a0` = integer | None |
| Print float | 2 | `$f12` = float | None |
| Print double | 3 | `$f12` = double | None |
| Print string | 4 | `$a0` = string address | None |
| Read integer | 5 | None | `$v0` = integer |
| Read float | 6 | None | `$f0` = float |
| Read double | 7 | None | `$f0` = double |
| Read string | 8 | `$a0` = buffer, `$a1` = length | None |
| Allocate heap | 9 | `$a0` = bytes | `$v0` = address |
| Exit program | 10 | None | None |
| Print character | 11 | `$a0` = character | None |
| Read character | 12 | None | `$v0` = character |

### 5.2 Input/Output Examples

#### Print Integer
```assembly
li   $v0, 1                # Service code for print_int
li   $a0, 42               # Integer to print
syscall                    # Print 42
```

#### Read Integer
```assembly
li   $v0, 5                # Service code for read_int
syscall                    # Read from user
move $t0, $v0              # Store input in $t0
```

#### Print String
```assembly
.data
msg:    .asciiz "Hello, World!\n"

.text
        li   $v0, 4        # Service code for print_string
        la   $a0, msg      # Address of string
        syscall            # Print string
```

#### Read String
```assembly
.data
buffer: .space 100         # Allocate 100 bytes

.text
        li   $v0, 8        # Service code for read_string
        la   $a0, buffer   # Buffer address
        li   $a1, 100      # Maximum length
        syscall            # Read string
```

### 5.3 Complete Program Example

**Program: Ask for name and age, then greet user**

```assembly
# NAME: [Your Name]
# Student ID: [Your ID]
# CCIT4026 Computer Organization
# Lab2 - User Input and Output

#----- Data Segment -----------------
.data
prompt_name:    .asciiz "Please enter your name: "
prompt_age:     .asciiz "Please enter your age: "
greeting:       .asciiz "\nHello, "
msg_age:        .asciiz "! You are "
msg_years:      .asciiz " years old.\n"
author:         .asciiz "\nProgram by: [Your Name] ([Student ID])\n"
name_buffer:    .space 100

#----- Text Segment -----------------
.text
.globl __start

__start:
        # Print prompt for name
        li   $v0, 4                # print_string
        la   $a0, prompt_name
        syscall
        
        # Read name
        li   $v0, 8                # read_string
        la   $a0, name_buffer
        li   $a1, 100
        syscall
        
        # Print prompt for age
        li   $v0, 4                # print_string
        la   $a0, prompt_age
        syscall
        
        # Read age
        li   $v0, 5                # read_int
        syscall
        move $s0, $v0              # Save age in $s0
        
        # Print greeting
        li   $v0, 4
        la   $a0, greeting
        syscall
        
        # Print name
        li   $v0, 4
        la   $a0, name_buffer
        syscall
        
        # Print age message
        li   $v0, 4
        la   $a0, msg_age
        syscall
        
        # Print age value
        li   $v0, 1                # print_int
        move $a0, $s0
        syscall
        
        # Print " years old"
        li   $v0, 4
        la   $a0, msg_years
        syscall
        
        # Print author information
        li   $v0, 4
        la   $a0, author
        syscall
        
        # Exit program
        li   $v0, 10               # exit
        syscall
```

**Sample Output:**
```
Please enter your name: John Smith
Please enter your age: 20

Hello, John Smith
! You are 20 years old.

Program by: [Your Name] ([Student ID])

-- program is finished running --
```

### 5.4 String Processing

#### String Length
```assembly
# Calculate length of null-terminated string
# Input: $a0 = address of string
# Output: $v0 = length

strlen:
        move $v0, $zero            # length = 0
        move $t0, $a0              # $t0 = current position
loop:   lb   $t1, 0($t0)           # Load byte
        beq  $t1, $zero, done      # If null, done
        addi $v0, $v0, 1           # length++
        addi $t0, $t0, 1           # Next character
        j    loop
done:   jr   $ra
```

#### String Copy
```assembly
# Copy string from source to destination
# $a0 = destination address
# $a1 = source address

strcpy:
        move $t0, $a0              # Destination pointer
        move $t1, $a1              # Source pointer
loop:   lb   $t2, 0($t1)           # Load source byte
        sb   $t2, 0($t0)           # Store to destination
        beq  $t2, $zero, done      # If null, done
        addi $t0, $t0, 1           # Next destination
        addi $t1, $t1, 1           # Next source
        j    loop
done:   jr   $ra
```

#### String Comparison
```assembly
# Compare two strings
# $a0 = first string address
# $a1 = second string address
# Return: $v0 = 0 if equal, non-zero otherwise

strcmp:
        move $t0, $a0              # First string
        move $t1, $a1              # Second string
loop:   lb   $t2, 0($t0)           # Load byte from first
        lb   $t3, 0($t1)           # Load byte from second
        bne  $t2, $t3, noteq       # If different, not equal
        beq  $t2, $zero, equal     # If both null, equal
        addi $t0, $t0, 1           # Next character
        addi $t1, $t1, 1
        j    loop
equal:  li   $v0, 0                # Strings are equal
        jr   $ra
noteq:  sub  $v0, $t2, $t3         # Return difference
        jr   $ra
```

### 5.5 Floating-Point Operations

MIPS has separate floating-point registers: `$f0-$f31`

#### Basic Floating-Point Instructions

**Load/Store:**
```assembly
lwc1 $f0, 0($t0)           # Load word to $f0
swc1 $f0, 0($t0)           # Store word from $f0
```

**Arithmetic:**
```assembly
add.s $f0, $f1, $f2        # $f0 = $f1 + $f2 (single precision)
add.d $f0, $f2, $f4        # $f0 = $f2 + $f4 (double precision)
sub.s $f0, $f1, $f2        # Subtract
mul.s $f0, $f1, $f2        # Multiply
div.s $f0, $f1, $f2        # Divide
```

**Conversions:**
```assembly
cvt.s.w $f0, $f1           # Convert integer to float
cvt.w.s $f0, $f1           # Convert float to integer
```

**Example: Calculate average**
```assembly
.data
values: .float 10.5, 20.3, 15.7
result: .float 0.0

.text
        lwc1 $f0, values       # Load first value
        lwc1 $f1, values+4     # Load second
        lwc1 $f2, values+8     # Load third
        
        add.s $f3, $f0, $f1    # Sum first two
        add.s $f3, $f3, $f2    # Add third
        
        li   $t0, 3
        mtc1 $t0, $f4          # Move 3 to FP register
        cvt.s.w $f4, $f4       # Convert to float
        
        div.s $f3, $f3, $f4    # Divide by 3
        swc1 $f3, result       # Store result
```

### 5.6 Memory-Mapped I/O

MARS provides memory-mapped I/O for keyboard and display.

**Keyboard Control:**
- Address: `0xFFFF0000` (control)
- Address: `0xFFFF0004` (data)

**Display Control:**
- Address: `0xFFFF0008` (control)
- Address: `0xFFFF000C` (data)

**Example: Poll for keyboard input**
```assembly
        lui  $t0, 0xFFFF           # Upper 16 bits
poll:   lw   $t1, 0($t0)           # Read control
        andi $t1, $t1, 1           # Check ready bit
        beq  $t1, $zero, poll      # If not ready, poll again
        lw   $a0, 4($t0)           # Read character
        # Process character...
```

### 5.7 Advanced Topics

#### Bitwise Operations Application

**Check if number is even:**
```assembly
andi $t0, $t1, 1           # $t0 = $t1 & 1
beq  $t0, $zero, even      # If bit 0 is 0, even
```

**Extract bits 8-15:**
```assembly
srl  $t0, $t1, 8           # Shift right 8 positions
andi $t0, $t0, 0xFF        # Mask to get 8 bits
```

**Set bit 5:**
```assembly
ori  $t0, $t1, 0x20        # Set bit 5 (0x20 = 0b100000)
```

**Clear bit 3:**
```assembly
andi $t0, $t1, 0xFFFFFFF7  # Clear bit 3
```

#### Dynamic Memory Allocation

```assembly
# Allocate memory on heap
li   $v0, 9                # sbrk (allocate heap)
li   $a0, 400              # Request 400 bytes (100 ints)
syscall                    # $v0 = address of allocated memory
move $s0, $v0              # Save address

# Use the memory
li   $t0, 42
sw   $t0, 0($s0)           # Store value at beginning
```

### 5.8 Debugging Techniques

#### Using MARS Debugger

1. **Set Breakpoints**: Click on line number or use breakpoint tool
2. **Single-Step Execution**: Use Step (F7) or Step Over
3. **Inspect Registers**: Watch register window during execution
4. **Inspect Memory**: Monitor data segment changes
5. **Use Console**: Check Run I/O window for output

#### Common Debugging Strategies

**Add Debug Print Statements:**
```assembly
# Print register value for debugging
li   $v0, 1
move $a0, $t0
syscall

# Print newline
li   $v0, 11
li   $a0, 10               # ASCII newline
syscall
```

**Check Assumptions:**
```assembly
# Verify array index in bounds
blt  $t0, $zero, error     # Check < 0
bge  $t0, $s1, error       # Check >= length
# ... proceed with array access
```

### 5.9 Practice Problems - Chapter 5

**Problem 1:** Write a program to find sum and average of N integers

**Solution:**
```assembly
.data
prompt_n:   .asciiz "How many numbers? "
prompt_num: .asciiz "Enter number: "
sum_msg:    .asciiz "\nSum: "
avg_msg:    .asciiz "\nAverage: "

.text
        # Read N
        li   $v0, 4
        la   $a0, prompt_n
        syscall
        li   $v0, 5
        syscall
        move $s0, $v0              # $s0 = N
        
        li   $s1, 0                # $s1 = sum
        li   $t0, 0                # $t0 = counter
        
loop:   beq  $t0, $s0, done        # If counter == N, done
        
        # Read number
        li   $v0, 4
        la   $a0, prompt_num
        syscall
        li   $v0, 5
        syscall
        
        add  $s1, $s1, $v0         # sum += number
        addi $t0, $t0, 1           # counter++
        j    loop
        
done:   # Print sum
        li   $v0, 4
        la   $a0, sum_msg
        syscall
        li   $v0, 1
        move $a0, $s1
        syscall
        
        # Calculate and print average
        li   $v0, 4
        la   $a0, avg_msg
        syscall
        
        div  $s1, $s0              # sum / N
        mflo $a0                   # Get quotient
        li   $v0, 1
        syscall
        
        # Exit
        li   $v0, 10
        syscall
```

**Problem 2:** Reverse a string

**Solution:**
```assembly
.data
prompt:    .asciiz "Enter string: "
result:    .asciiz "Reversed: "
buffer:    .space 100
reversed:  .space 100

.text
        # Read string
        li   $v0, 4
        la   $a0, prompt
        syscall
        li   $v0, 8
        la   $a0, buffer
        li   $a1, 100
        syscall
        
        # Find length
        la   $t0, buffer           # Source pointer
        li   $t1, 0                # Length counter
len_loop:
        lb   $t2, 0($t0)
        beq  $t2, 10, len_done     # Newline = end
        beq  $t2, $zero, len_done  # Null = end
        addi $t1, $t1, 1
        addi $t0, $t0, 1
        j    len_loop
len_done:
        
        # Reverse string
        la   $t0, buffer           # Source
        la   $t3, reversed         # Destination
        add  $t0, $t0, $t1         # Point to end
        addi $t0, $t0, -1          # Back one
        
rev_loop:
        blt  $t1, $zero, rev_done
        lb   $t2, 0($t0)           # Load from end
        sb   $t2, 0($t3)           # Store at beginning
        addi $t0, $t0, -1          # Move backward
        addi $t3, $t3, 1           # Move forward
        addi $t1, $t1, -1          # Decrement counter
        j    rev_loop
rev_done:
        sb   $zero, 0($t3)         # Null terminate
        
        # Print result
        li   $v0, 4
        la   $a0, result
        syscall
        la   $a0, reversed
        syscall
        
        # Exit
        li   $v0, 10
        syscall
```

---

## LABORATORY WORK

### Lab Setup and Environment

#### Installing MARS
1. Download MARS from official website
2. Java Runtime Environment (JRE) required
3. Run: `java -jar Mars.jar`

#### MARS Interface Components

**Main Windows:**
1. **Edit Tab**: Code editor with syntax highlighting
2. **Execute Tab**: Runtime view with:
   - Text Segment: Machine code display
   - Data Segment: Memory contents
   - Registers: CPU register values
   - Run I/O: Console for program input/output

**Toolbar Functions:**
- **New**: Create new file
- **Open**: Load existing .asm file
- **Save**: Save current file
- **Assemble** (F3): Convert assembly to machine code
- **Go** (F5): Run program
- **Step** (F7): Execute one instruction
- **Reset**: Clear memory and registers

### Lab 2: User Input and Output

#### Objectives
1. Understand MIPS program structure
2. Use data and text segments
3. Implement string and integer I/O
4. Use syscall service for user interaction

#### Requirements

**Program Specifications:**
1. Ask user for name (string input)
2. Ask user for age (integer input)
3. Display personalized greeting
4. Show author information

**Submission Requirements:**
1. Assembly source code (.asm file)
2. Lab report (PDF) containing:
   - Student information and ID photo
   - Source code screenshot (with colors)
   - Assembled machine code screenshot
   - Program output screenshot (with termination message)

#### Sample Implementation

```assembly
# NAME: Chan Tai Man
# Student ID: 1234567
# CCIT4026 Computer Organization
# CCIT4026-CL01
# Lab2 - User Input and Output

#----- Data Segment -----------------
.data
prompt_name:    .asciiz "What is your name? "
prompt_age:     .asciiz "How old are you? "
greeting:       .asciiz "\n==== User Information ====\n"
msg_name:       .asciiz "Name: "
msg_age:        .asciiz "Age: "
msg_footer:     .asciiz "\n==========================\n"
author_info:    .asciiz "\n*** Program created by Chan Tai Man (1234567) ***\n"
name_buffer:    .space 50

#----- Text Segment -----------------
.text
.globl __start

__start:
        # Prompt and read name
        li   $v0, 4                # print_string service
        la   $a0, prompt_name      # load prompt address
        syscall                    # display prompt
        
        li   $v0, 8                # read_string service
        la   $a0, name_buffer      # buffer address
        li   $a1, 50               # maximum length
        syscall                    # read user input
        
        # Prompt and read age
        li   $v0, 4                # print_string service
        la   $a0, prompt_age       # load prompt address
        syscall                    # display prompt
        
        li   $v0, 5                # read_int service
        syscall                    # read integer
        move $s0, $v0              # save age in $s0
        
        # Display greeting header
        li   $v0, 4
        la   $a0, greeting
        syscall
        
        # Display name label
        li   $v0, 4
        la   $a0, msg_name
        syscall
        
        # Display name value
        li   $v0, 4
        la   $a0, name_buffer
        syscall
        
        # Display age label
        li   $v0, 4
        la   $a0, msg_age
        syscall
        
        # Display age value
        li   $v0, 1                # print_int service
        move $a0, $s0              # load age
        syscall
        
        # Display footer
        li   $v0, 4
        la   $a0, msg_footer
        syscall
        
        # Display author information
        li   $v0, 4
        la   $a0, author_info
        syscall
        
        # Terminate program
        li   $v0, 10               # exit service
        syscall

# End of program
```

#### Expected Output
```
What is your name? Alice Wong
How old are you? 19

==== User Information ====
Name: Alice Wong
Age: 19
==========================

*** Program created by Chan Tai Man (1234567) ***

-- program is finished running --
```

### Additional Lab Exercises

#### Exercise 1: Simple Calculator
Create a calculator that:
- Reads two integers
- Performs addition, subtraction, multiplication
- Displays all results

#### Exercise 2: Temperature Converter
Convert Celsius to Fahrenheit:
- Formula: F = (C × 9/5) + 32
- Use integer arithmetic
- Display result

#### Exercise 3: Array Operations
- Define array of 5 integers in data segment
- Calculate sum and maximum value
- Display results

#### Exercise 4: String Manipulation
- Read a string from user
- Count vowels (a, e, i, o, u)
- Display count

---

## TEACHING STRATEGIES

### 1. Lecture Delivery Methods

#### Introduction Session (Week 1)
**Objectives:**
- Motivate computer organization study
- Overview of course structure
- Setup development environment

**Activities:**
- Live demo of MARS simulator
- Execute simple "Hello World" program
- Show relationship between C code and assembly

#### Conceptual Learning (Theory Classes)
**Approach:**
- Start with high-level concepts
- Use analogies and real-world examples
- Gradually introduce technical details

**Example Progression:**
1. House analogy: Rooms = Memory, Blueprint = Instructions
2. Introduction to registers: Post-it notes vs. file cabinets
3. Detailed register specifications and constraints

#### Practical Sessions (Lab Classes)
**Structure:**
1. **Mini-lecture** (15 min): Introduce new concepts
2. **Live coding** (20 min): Demonstrate techniques
3. **Guided practice** (30 min): Students follow along
4. **Independent work** (45 min): Complete lab exercises
5. **Q&A and debug** (20 min): Address common issues

### 2. Active Learning Techniques

#### Think-Pair-Share
**Example Question:**
"How would you implement this C if-statement in MIPS assembly?"
```c
if (x > 10 && y < 5) {
    z = 1;
}
```

**Process:**
1. Think (2 min): Individual solution
2. Pair (3 min): Discuss with neighbor
3. Share (5 min): Groups present approaches

#### Code Tracing Exercises
Provide assembly code and ask students to:
- Predict register values after each instruction
- Trace program flow through branches
- Identify bugs or inefficiencies

#### Peer Programming
- Students work in pairs on lab exercises
- One "driver" types, one "navigator" guides
- Switch roles every 15 minutes

### 3. Visual Aids and Demonstrations

#### Register Usage Diagrams
Create large wall posters showing:
- Register names and numbers
- Usage conventions
- Preservation rules

#### Instruction Format Cards
Physical cards showing:
- R-type, I-type, J-type layouts
- Bit field positions
- Example encodings

#### Memory Map Visualization
Draw memory layout on board for each program:
- Show stack growth
- Trace variable allocations
- Demonstrate pointer operations

### 4. Progressive Difficulty

#### Week-by-Week Complexity
**Weeks 1-2:** Simple arithmetic and data movement
**Weeks 3-4:** Control flow and loops
**Weeks 5-6:** Functions and stack operations
**Weeks 7-8:** Advanced topics and optimization

#### Scaffold Learning
- Provide code templates initially
- Gradually reduce scaffolding
- Final projects: Complete programs from scratch

### 5. Common Misconceptions to Address

#### Misconception 1: "Registers are like variables"
**Reality:** Registers are limited resource requiring careful management

**Teaching Strategy:**
- Demonstrate register allocation conflicts
- Show need for stack storage
- Practice register spilling

#### Misconception 2: "Assembly is just programming"
**Reality:** Must understand hardware constraints

**Teaching Strategy:**
- Explain physical limitations
- Discuss timing and performance
- Show impact of memory hierarchy

#### Misconception 3: "Each C line = one assembly instruction"
**Reality:** High-level constructs expand significantly

**Teaching Strategy:**
- Show compiler output for real C programs
- Count instruction ratios
- Discuss optimization strategies

---

## ASSESSMENT METHODS

### 1. Laboratory Assignments (40%)

#### Grading Rubric for Lab 2

| Component | Points | Criteria |
|-----------|--------|----------|
| **Functionality** | 50 | Program works correctly |
| - Accepts string input | 10 | Name read properly |
| - Accepts integer input | 10 | Age read properly |
| - Displays greeting | 15 | Correct output format |
| - Shows author info | 5 | Pre-defined message shown |
| - Terminates properly | 10 | Clean exit with message |
| **Code Quality** | 20 | Professional standards |
| - Comments | 10 | Clear, descriptive comments |
| - Formatting | 5 | Consistent indentation |
| - Register usage | 5 | Appropriate register choices |
| **Documentation** | 30 | Lab report completeness |
| - Student info | 5 | Name, ID, photo present |
| - Source code screenshot | 10 | Clear, colored, complete |
| - Assembly output | 5 | Machine code visible |
| - Execution output | 10 | Full console capture |

#### Late Submission Policy
- **Deadline**: Specified in SOUL
- **Late submissions**: NOT accepted (0 marks)
- **Missing files**: Either .asm OR .pdf missing = 0 marks

### 2. Quizzes (20%)

#### Sample Quiz Questions

**Question 1 (Multiple Choice):**
What is the value in `$t0` after executing?
```assembly
li   $t0, 8
sll  $t0, $t0, 2
```
- A) 10
- B) 16
- C) 32
- D) 64

**Answer: C) 32** (8 << 2 = 8 × 4 = 32)

**Question 2 (Fill in the blank):**
```assembly
li   $t0, 10
li   $t1, 3
div  $t0, $t1
mflo $t2
mfhi $t3
```
After execution: `$t2 = ___`, `$t3 = ___`

**Answer:** `$t2 = 3` (quotient), `$t3 = 1` (remainder)

**Question 3 (Code completion):**
Write MIPS code for: `if (a != b) goto label;`
```assembly
# $s0 = a, $s1 = b
_____________________  # Fill in this line
```

**Answer:** `bne $s0, $s1, label`

### 3. Midterm Examination (20%)

#### Topics Covered
- Chapters 1-3
- Number systems
- MIPS instructions (arithmetic, logical, data transfer)
- Basic control flow

#### Sample Midterm Questions

**Question 1 (10 points):** Convert decimal 156 to:
- Binary: ____________
- Hexadecimal: ____________

**Question 2 (15 points):** Translate C code to MIPS:
```c
int x = 5;
int y = 10;
int z = (x + y) * 2;
```

**Question 3 (20 points):** Write MIPS function:
```assembly
# Function: absolute value
# Input: $a0 = integer
# Output: $v0 = |$a0|
abs_val:
    # Your code here
```

### 4. Final Examination (20%)

#### Comprehensive Coverage
- All chapters (1-5)
- Emphasis on later material (functions, I/O, syscalls)
- Integration of concepts

#### Sample Final Questions

**Question 1 (25 points):** Write complete MIPS program:
- Read N integers from user
- Find minimum value
- Display result

**Question 2 (20 points):** Implement recursive function:
```c
int power(int base, int exp) {
    if (exp == 0) return 1;
    return base * power(base, exp - 1);
}
```

**Question 3 (15 points):** Debug this code:
```assembly
# Supposed to add array elements
# Bug: produces wrong result
    la   $t0, array
    li   $t1, 0
    li   $t2, 10
loop:
    lw   $t3, 0($t0)
    add  $t1, $t1, $t3
    addi $t2, $t2, -1
    bne  $t2, $zero, loop
```

**Answer:** Missing `addi $t0, $t0, 4` to advance array pointer

---

## ADDITIONAL RESOURCES

### Recommended Textbooks

1. **"Computer Organization and Design: The Hardware/Software Interface"**
   - Authors: Patterson & Hennessy
   - Focus: MIPS architecture, detailed explanations

2. **"Computer Systems: A Programmer's Perspective"**
   - Authors: Bryant & O'Hallaron
   - Focus: System-level programming, practical approach

3. **"MIPS Assembly Language Programming"**
   - Author: Robert Britton
   - Focus: Practical MIPS programming

### Online Resources

#### Official Documentation
- **MIPS Reference Card**: Quick instruction reference
- **MARS Documentation**: User guide and tutorials
- **SPIM Manual**: Alternative MIPS simulator

#### Video Tutorials
- YouTube channels for computer architecture
- MIT OpenCourseWare: Computer System Architecture
- Coursera: Computer Architecture specialization

#### Practice Platforms
- **LeetCode**: Algorithm challenges (translate to assembly)
- **MIPS Tutor**: Interactive exercises
- **Assembly Language Challenges**: Online problems

### MARS Simulator Tips

#### Useful Settings
```
Settings → Memory Configuration → Compact, Data at Address 0
Settings → Editor → Auto Indent
Settings → Assembler → Permit extended (pseudo) instructions
```

#### Keyboard Shortcuts
- **F3**: Assemble
- **F5**: Run
- **F7**: Step Into
- **F8**: Step Over
- **F9**: Toggle Breakpoint
- **F10**: Reset

#### Common Errors and Solutions

**Error:** "Runtime exception at 0x00400000"
- **Cause:** Accessing invalid memory
- **Solution:** Check array bounds and pointer arithmetic

**Error:** "Instruction can only be used in kernel mode"
- **Cause:** Trying to use restricted instruction
- **Solution:** Remove privileged instruction

**Error:** "Branch out of range"
- **Cause:** Branch target too far (>32KB)
- **Solution:** Use jump instruction or reorganize code

### Programming Best Practices

#### Code Organization
```assembly
# 1. Header comments
# NAME, ID, COURSE, DATE

# 2. Data segment
.data
# Constants first
# Variables next
# Buffers last

# 3. Text segment
.text
.globl main

# 4. Main program
main:
    # Program logic

# 5. Functions
function1:
    # Function code

# 6. Helper functions
helper1:
    # Helper code
```

#### Commenting Guidelines
```assembly
# Good: Explains intent
add  $t0, $t1, $t2    # Calculate total price

# Bad: Restates code
add  $t0, $t1, $t2    # Add $t1 and $t2

# Good: Documents assumptions
# Assumes: $s0 contains array base address
#          $s1 contains array length

# Good: Marks sections
#----- INPUT VALIDATION -----
```

#### Register Usage Guidelines
- Use `$t` registers for temporary calculations
- Use `$s` registers for values needed across function calls
- Save and restore `$s` and `$ra` in functions
- Use `$a` for function arguments
- Use `$v` for return values

### Practice Problems Collection

#### Problem Set 1: Basics
1. Write program to convert Fahrenheit to Celsius
2. Calculate factorial using loop
3. Find GCD of two numbers
4. Check if number is prime

#### Problem Set 2: Arrays
1. Find maximum element in array
2. Reverse array in-place
3. Bubble sort implementation
4. Binary search in sorted array

#### Problem Set 3: Strings
1. Count occurrences of character
2. Check if string is palindrome
3. Convert lowercase to uppercase
4. Find substring in string

#### Problem Set 4: Functions
1. Matrix addition (2D arrays)
2. Linked list traversal
3. Tower of Hanoi (recursive)
4. Quicksort implementation

---

## COURSE SCHEDULE SUGGESTION

### Week-by-Week Breakdown

#### Week 1: Introduction
- **Lecture:** Chapter 1 - Computer Organization basics
- **Lab:** MARS setup and "Hello World"
- **Homework:** Number system conversions

#### Week 2: MIPS Fundamentals
- **Lecture:** Chapter 2 (Part 1) - Registers and arithmetic
- **Lab:** Basic arithmetic programs
- **Homework:** Write calculator program

#### Week 3: Data Transfer and Logic
- **Lecture:** Chapter 2 (Part 2) - Memory and logical operations
- **Lab:** Array manipulation
- **Homework:** Bitwise operation exercises

#### Week 4: Control Flow
- **Lecture:** Chapter 3 (Part 1) - Branches and jumps
- **Lab:** If-else and loop implementations
- **Homework:** Loop problems

#### Week 5: Advanced Control
- **Lecture:** Chapter 3 (Part 2) - Complex loops and patterns
- **Lab:** Nested loops and pattern printing
- **Quiz:** Chapters 1-3

#### Week 6: Functions Basics
- **Lecture:** Chapter 4 (Part 1) - Function calls and stack
- **Lab:** Simple function implementations
- **Homework:** Function practice problems

#### Week 7: Advanced Functions
- **Lecture:** Chapter 4 (Part 2) - Recursion and nested calls
- **Lab:** Recursive algorithms
- **Midterm Exam:** Chapters 1-4

#### Week 8: System Calls
- **Lecture:** Chapter 5 (Part 1) - I/O operations
- **Lab:** Lab 2 - User interaction program
- **Homework:** Complete Lab 2

#### Week 9: String Processing
- **Lecture:** Chapter 5 (Part 2) - String manipulation
- **Lab:** String algorithm implementations
- **Homework:** String problems

#### Week 10: Floating-Point
- **Lecture:** Chapter 5 (Part 3) - FP operations
- **Lab:** Scientific calculator
- **Homework:** FP arithmetic problems

#### Week 11: Advanced Topics
- **Lecture:** Optimization and debugging techniques
- **Lab:** Optimize previous programs
- **Project:** Start final project

#### Week 12: Review and Projects
- **Lecture:** Course review and Q&A
- **Lab:** Project work time
- **Quiz:** Chapter 5

#### Week 13: Final Preparations
- **Lecture:** Exam preparation workshop
- **Lab:** Practice problems
- **Project:** Submit final project

#### Week 14: Final Examination
- **Comprehensive final exam**

---

## FINAL NOTES FOR INSTRUCTORS

### Creating Engaging Lectures

1. **Start with motivation**: Show real-world applications
2. **Use incremental examples**: Build complexity gradually
3. **Interactive polling**: Ask questions frequently
4. **Live coding**: Write code during lecture, make deliberate mistakes
5. **Student presentations**: Have students explain solutions

### Handling Common Student Difficulties

#### Difficulty 1: Register Management
**Solution:** Create "register allocation worksheet" for planning before coding

#### Difficulty 2: Understanding Stack
**Solution:** Physical demonstration with stack of papers/books

#### Difficulty 3: Debugging
**Solution:** Teach systematic debugging checklist:
- Check register values
- Verify memory addresses
- Trace branch targets
- Validate loop conditions

### Adapting for Different Learning Styles

- **Visual learners**: Diagrams, flowcharts, memory maps
- **Auditory learners**: Verbal explanations, discussions
- **Kinesthetic learners**: Hands-on coding, physical models
- **Reading/writing learners**: Detailed notes, written exercises

### Assessment Fairness

- Provide sample problems before exams
- Allow reference card during tests (MIPS instruction list)
- Offer partial credit for partially correct solutions
- Consider coding style in grading (not just functionality)

### Continuous Improvement

- Collect anonymous feedback mid-semester
- Track which topics cause most confusion
- Adjust pace based on student progress
- Update examples to remain relevant

---

## APPENDICES

### Appendix A: Complete MIPS Instruction Reference

#### Arithmetic Instructions
| Instruction | Format | Operation | Example |
|-------------|--------|-----------|---------|
| add | R | rd = rs + rt | add $t0, $t1, $t2 |
| addi | I | rt = rs + imm | addi $t0, $t1, 100 |
| addu | R | rd = rs + rt (unsigned) | addu $t0, $t1, $t2 |
| addiu | I | rt = rs + imm (unsigned) | addiu $t0, $t1, 100 |
| sub | R | rd = rs - rt | sub $t0, $t1, $t2 |
| subu | R | rd = rs - rt (unsigned) | subu $t0, $t1, $t2 |
| mult | R | HI:LO = rs * rt | mult $t0, $t1 |
| multu | R | HI:LO = rs * rt (unsigned) | multu $t0, $t1 |
| div | R | LO = rs / rt, HI = rs % rt | div $t0, $t1 |
| divu | R | Unsigned division | divu $t0, $t1 |
| mfhi | R | rd = HI | mfhi $t0 |
| mflo | R | rd = LO | mflo $t0 |

#### Logical Instructions
| Instruction | Format | Operation | Example |
|-------------|--------|-----------|---------|
| and | R | rd = rs & rt | and $t0, $t1, $t2 |
| andi | I | rt = rs & imm | andi $t0, $t1, 0xFF |
| or | R | rd = rs | rt | or $t0, $t1, $t2 |
| ori | I | rt = rs | imm | ori $t0, $t1, 0xFF |
| xor | R | rd = rs ^ rt | xor $t0, $t1, $t2 |
| xori | I | rt = rs ^ imm | xori $t0, $t1, 0xFF |
| nor | R | rd = ~(rs | rt) | nor $t0, $t1, $t2 |
| sll | R | rd = rt << shamt | sll $t0, $t1, 4 |
| srl | R | rd = rt >> shamt | srl $t0, $t1, 4 |
| sra | R | rd = rt >> shamt (arithmetic) | sra $t0, $t1, 4 |

### Appendix B: MARS Syscall Complete Reference

| Service | Code | Arguments | Returns | Description |
|---------|------|-----------|---------|-------------|
| print_int | 1 | $a0 = integer | - | Print integer |
| print_float | 2 | $f12 = float | - | Print float |
| print_double | 3 | $f12 = double | - | Print double |
| print_string | 4 | $a0 = address | - | Print null-terminated string |
| read_int | 5 | - | $v0 = integer | Read integer |
| read_float | 6 | - | $f0 = float | Read float |
| read_double | 7 | - | $f0 = double | Read double |
| read_string | 8 | $a0 = buffer, $a1 = length | - | Read string |
| sbrk | 9 | $a0 = bytes | $v0 = address | Allocate heap memory |
| exit | 10 | - | - | Exit program |
| print_character | 11 | $a0 = char | - | Print ASCII character |
| read_character | 12 | - | $v0 = char | Read ASCII character |
| open | 13 | $a0 = filename, $a1 = flags, $a2 = mode | $v0 = descriptor | Open file |
| read | 14 | $a0 = descriptor, $a1 = buffer, $a2 = length | $v0 = bytes read | Read from file |
| write | 15 | $a0 = descriptor, $a1 = buffer, $a2 = length | $v0 = bytes written | Write to file |
| close | 16 | $a0 = descriptor | - | Close file |
| exit2 | 17 | $a0 = result | - | Exit with value |

### Appendix C: ASCII Table (Partial)

| Dec | Hex | Char | Description |
|-----|-----|------|-------------|
| 0 | 0x00 | NUL | Null |
| 10 | 0x0A | LF | Line feed (newline) |
| 13 | 0x0D | CR | Carriage return |
| 32 | 0x20 | SP | Space |
| 48-57 | 0x30-0x39 | 0-9 | Digits |
| 65-90 | 0x41-0x5A | A-Z | Uppercase letters |
| 97-122 | 0x61-0x7A | a-z | Lowercase letters |

### Appendix D: Common Error Messages

| Error | Meaning | Solution |
|-------|---------|----------|
| "Runtime exception at 0x..." | Memory access violation | Check array bounds, pointer validity |
| "Address out of range" | Invalid memory address | Verify address calculations |
| "Branch out of range" | Branch target too far | Use jump instead of branch |
| "Invalid instruction" | Unknown opcode | Check instruction spelling |
| "Instruction not permitted" | Kernel-mode instruction | Remove privileged instruction |

---

## CONCLUSION

This comprehensive teaching material provides a complete foundation for teaching **Introduction to Computer Organization (CCIT4026)**. The material progresses logically from basic computer organization concepts through increasingly sophisticated MIPS assembly programming techniques.

**Key Strengths of This Material:**
1. **Progressive complexity**: Builds from fundamentals to advanced topics
2. **Practical examples**: Every concept illustrated with working code
3. **Multiple learning modalities**: Theory, examples, practice problems
4. **Real-world connection**: Links assembly to high-level languages
5. **Assessment aligned**: Teaching materials match evaluation criteria

**Recommended Teaching Philosophy:**
- Emphasize understanding over memorization
- Encourage experimentation and debugging
- Connect low-level details to high-level concepts
- Foster problem-solving skills, not just coding
- Build confidence through incremental success

**For Students:**
This material serves as both textbook and reference. Work through examples systematically, complete all practice problems, and don't hesitate to experiment with variations. Computer organization is learned by doing!

**For Instructors:**
Adapt this material to your teaching style and student needs. The structure is flexible—rearrange, expand, or condense based on your course requirements. Most importantly, maintain enthusiasm for the subject; computer organization is fundamental to understanding how computers really work!

---

### Document Information
- **Course**: CCIT4026 - Introduction to Computer Organization
- **Institution**: HKU SPACE Community College
- **Version**: 1.0
- **Date Created**: February 2026
- **Chapters Covered**: 1-5 plus Laboratory Work
- **Total Pages**: Comprehensive teaching guide

---

**END OF COMPREHENSIVE TEACHING MATERIAL**
