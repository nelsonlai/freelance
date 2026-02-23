# CHAPTER 1: INTRODUCTION
## Introduction to Computer Organization (CCIT4026)
### HKU SPACE Community College

---

## TABLE OF CONTENTS

1. [What is Computer Organization?](#11-what-is-computer-organization)
2. [The von Neumann Architecture](#12-the-von-neumann-architecture)
3. [Number Systems and Data Representation](#13-number-systems-and-data-representation)
4. [Performance Metrics](#14-performance-metrics)
5. [Levels of Programming Languages](#15-levels-of-programming-languages)

---

## 1.1 What is Computer Organization?

### Teaching Points:
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

---

## 1.2 The von Neumann Architecture

### Essential Components:

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

### Teaching Activity:
Draw the von Neumann architecture diagram on the board and trace the execution of a simple instruction (e.g., ADD operation).

### von Neumann Architecture Diagram

```
┌─────────────────────────────────────────────────────┐
│                  Central Processing Unit (CPU)       │
│  ┌────────────────────┐    ┌──────────────────────┐ │
│  │   Control Unit     │    │  Arithmetic Logic    │ │
│  │     (CU)           │    │    Unit (ALU)        │ │
│  └────────────────────┘    └──────────────────────┘ │
│  ┌────────────────────────────────────────────────┐ │
│  │             Registers                          │ │
│  └────────────────────────────────────────────────┘ │
└──────────────────┬──────────────────────────────────┘
                   │
        ┌──────────┴──────────┐ System Bus
        │                     │
┌───────▼────────┐    ┌──────▼──────────┐
│     Memory     │    │   I/O Devices   │
│     (RAM)      │    │  Input/Output   │
└────────────────┘    └─────────────────┘
```

---

## 1.3 Number Systems and Data Representation

### Binary Number System
```
Decimal: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
Binary:  0, 1

Examples:
Decimal 13 = 1101 (binary) = 1×2³ + 1×2² + 0×2¹ + 1×2⁰
           = 8 + 4 + 0 + 1 = 13
```

### Hexadecimal Number System
```
0-9, A(10), B(11), C(12), D(13), E(14), F(15)

Examples:
0xFF = 255 (decimal)
0x10 = 16 (decimal)
0x2A = 42 (decimal)
```

### Conversion Between Number Systems

#### Binary to Decimal
```
Example: 11010110₂ to decimal

1×2⁷ + 1×2⁶ + 0×2⁵ + 1×2⁴ + 0×2³ + 1×2² + 1×2¹ + 0×2⁰
= 128 + 64 + 0 + 16 + 0 + 4 + 2 + 0
= 214₁₀
```

#### Decimal to Binary
```
Example: 157₁₀ to binary

157 ÷ 2 = 78 remainder 1  (LSB)
78 ÷ 2 = 39 remainder 0
39 ÷ 2 = 19 remainder 1
19 ÷ 2 = 9 remainder 1
9 ÷ 2 = 4 remainder 1
4 ÷ 2 = 2 remainder 0
2 ÷ 2 = 1 remainder 0
1 ÷ 2 = 0 remainder 1  (MSB)

Reading from bottom to top: 10011101₂
```

#### Binary to Hexadecimal
```
Example: 11010110₂ to hexadecimal

Group into 4-bit chunks from right:
1101 0110
  D    6

Answer: 0xD6
```

### Signed Number Representations

#### 1. Sign-Magnitude
- First bit is sign (0=positive, 1=negative)
- Remaining bits are magnitude
- Example: +5 = 0101, -5 = 1101

**Issues:**
- Two representations of zero (+0 and -0)
- Complicated arithmetic operations

#### 2. Two's Complement (Most Common)
- Positive numbers: Same as unsigned
- Negative numbers: Invert bits and add 1

**Example:**
```
+5 = 0101
-5: Step 1: Invert bits → 1010
    Step 2: Add 1       → 1011

Therefore: -5 = 1011
```

**Advantages:**
- Only one representation of zero
- Simple addition/subtraction (same circuit)
- Easy to determine sign (MSB)

#### Two's Complement Range
For n bits:
- Range: -2^(n-1) to 2^(n-1) - 1
- Example (8 bits): -128 to 127

#### Converting Two's Complement to Decimal
```
Example: 10110011₂ (8-bit) to decimal

MSB is 1, so it's negative.

Method 1: Invert and add 1
Invert: 01001100
Add 1:  01001101 = 77
Therefore: -77

Method 2: Use weighted calculation
-1×2⁷ + 0×2⁶ + 1×2⁵ + 1×2⁴ + 0×2³ + 0×2² + 1×2¹ + 1×2⁰
= -128 + 0 + 32 + 16 + 0 + 0 + 2 + 1
= -77
```

### Practice Problems:

**Problem 1:** Convert decimal 42 to binary
```
Solution:
42 ÷ 2 = 21 remainder 0
21 ÷ 2 = 10 remainder 1
10 ÷ 2 = 5 remainder 0
5 ÷ 2 = 2 remainder 1
2 ÷ 2 = 1 remainder 0
1 ÷ 2 = 0 remainder 1

Answer: 101010₂
```

**Problem 2:** Convert binary 11010110 to hexadecimal
```
Solution:
1101 0110
  D    6

Answer: 0xD6
```

**Problem 3:** Find two's complement of -15 (8-bit)
```
Solution:
+15 = 00001111
Invert: 11110000
Add 1:  11110001

Answer: 11110001
```

---

## 1.4 Performance Metrics

### CPU Performance Equation

```
Execution Time = Instruction Count × CPI × Clock Cycle Time

Where:
- Instruction Count: Number of instructions executed
- CPI (Cycles Per Instruction): Average cycles needed per instruction
- Clock Cycle Time = 1 / Clock Frequency
```

### Alternative Formulation

```
CPU Time = (Instruction Count × CPI) / Clock Frequency
```

### Example Calculation:

**Problem:** A program has the following characteristics:
- 1,000,000 instructions
- Average CPI = 2.5
- Clock frequency = 2 GHz

**Calculate execution time:**

```
Step 1: Calculate total cycles
Total Cycles = Instruction Count × CPI
             = 1,000,000 × 2.5
             = 2,500,000 cycles

Step 2: Calculate clock cycle time
Clock Cycle Time = 1 / Frequency
                 = 1 / 2,000,000,000 Hz
                 = 0.5 nanoseconds

Step 3: Calculate execution time
Execution Time = Total Cycles × Clock Cycle Time
               = 2,500,000 × 0.5 ns
               = 1,250,000 ns
               = 1.25 milliseconds
```

### Performance Comparison

**Speedup** measures relative performance improvement:

```
Speedup = Execution Time (old) / Execution Time (new)
        = Performance (new) / Performance (old)
```

**Example:**
If old system takes 10 seconds and new system takes 2 seconds:
```
Speedup = 10 / 2 = 5×
(New system is 5 times faster)
```

### Factors Affecting Performance

1. **Instruction Count**
   - Determined by: Program, compiler, ISA
   - Reduced by: Better algorithms, compiler optimizations

2. **CPI (Cycles Per Instruction)**
   - Determined by: CPU organization, ISA
   - Improved by: Pipelining, cache design

3. **Clock Frequency**
   - Determined by: Technology, organization
   - Increased by: Better manufacturing, architecture

### Amdahl's Law

**Key Insight:** The speedup of a program is limited by the portion that can be parallelized.

```
Speedup Overall = 1 / [(1 - P) + P/S]

Where:
- P = Proportion of program that is parallelizable
- S = Speedup of the parallelized portion
```

**Example:**
If 80% of a program can be parallelized with 4× speedup:
```
Speedup = 1 / [(1 - 0.8) + 0.8/4]
        = 1 / [0.2 + 0.2]
        = 1 / 0.4
        = 2.5×
```

---

## 1.5 Levels of Programming Languages

### The Translation Hierarchy

```
┌─────────────────────────────────────────┐
│   High-Level Languages                  │
│   Python, Java, C, C++                  │
└─────────────────┬───────────────────────┘
                  │ (Compiler/Interpreter)
┌─────────────────▼───────────────────────┐
│   Assembly Language                     │
│   MIPS, x86, ARM                        │
└─────────────────┬───────────────────────┘
                  │ (Assembler)
┌─────────────────▼───────────────────────┐
│   Machine Code (Binary)                 │
│   01010101 10101010...                  │
└─────────────────┬───────────────────────┘
                  │ (Execution)
┌─────────────────▼───────────────────────┐
│   Hardware (Physical Circuits)          │
│   CPU, Memory, I/O                      │
└─────────────────────────────────────────┘
```

### Language Level Characteristics

#### High-Level Languages
**Characteristics:**
- Human-readable syntax
- Portable across platforms
- Rich data structures and abstractions
- Memory management (often automatic)

**Examples:**
```python
# Python
def factorial(n):
    if n <= 1:
        return 1
    return n * factorial(n - 1)
```

```c
// C
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}
```

#### Assembly Language
**Characteristics:**
- Symbolic representation of machine code
- One-to-one correspondence with machine instructions
- Platform-specific
- Direct hardware control

**Example (MIPS):**
```assembly
# Calculate: c = a + b
add $t0, $t1, $t2    # $t0 = $t1 + $t2
```

#### Machine Code
**Characteristics:**
- Binary representation
- Directly executable by CPU
- Platform-specific
- Not human-readable

**Example:**
```
00000001001010100100000000100000
(Binary representation of MIPS add instruction)
```

### Translation Process

#### Compilation
```
High-Level Source Code
        ↓
    Compiler
        ↓
Assembly Code
        ↓
    Assembler
        ↓
Object Code (.o)
        ↓
    Linker
        ↓
Executable (.exe)
```

#### Steps in Detail:

1. **Preprocessing**
   - Handle #include, #define directives
   - Macro expansion

2. **Compilation**
   - Syntax analysis (parsing)
   - Semantic analysis
   - Optimization
   - Code generation (assembly)

3. **Assembly**
   - Convert assembly to machine code
   - Create object file

4. **Linking**
   - Combine multiple object files
   - Resolve external references
   - Create executable

### Why Study Assembly Language?

1. **Understanding Computer Architecture**
   - See how computers really work
   - Understand performance implications

2. **Performance Optimization**
   - Critical sections of code
   - Device drivers
   - Embedded systems

3. **Debugging and Reverse Engineering**
   - Understand compiler output
   - Debug at low level
   - Security analysis

4. **System Programming**
   - Operating systems
   - Compilers
   - Firmware

5. **Educational Value**
   - Foundation for advanced topics
   - Better high-level programmer
   - Appreciate compiler work

---

## PRACTICE EXERCISES

### Exercise 1: Number Conversions

1. Convert decimal 156 to binary
2. Convert binary 10111001 to decimal
3. Convert hexadecimal 0x3F to binary
4. Convert decimal 200 to hexadecimal

### Exercise 2: Two's Complement

1. Find 8-bit two's complement of -25
2. What decimal value does 11001000 represent in 8-bit two's complement?
3. Calculate in 8-bit two's complement: 50 + (-30)

### Exercise 3: Performance Calculations

1. A program runs in 5 seconds on processor A. Processor B runs it in 2 seconds. What is the speedup?

2. Calculate execution time for:
   - 500,000 instructions
   - CPI = 3.0
   - Clock frequency = 1.5 GHz

3. If 60% of a program can be parallelized with 3× speedup, what is the overall speedup?

---

## SOLUTIONS TO PRACTICE EXERCISES

### Exercise 1 Solutions:

1. **156 to binary:**
   ```
   156 ÷ 2 = 78 r 0
   78 ÷ 2 = 39 r 0
   39 ÷ 2 = 19 r 1
   19 ÷ 2 = 9 r 1
   9 ÷ 2 = 4 r 1
   4 ÷ 2 = 2 r 0
   2 ÷ 2 = 1 r 0
   1 ÷ 2 = 0 r 1
   
   Answer: 10011100
   ```

2. **10111001 to decimal:**
   ```
   1×128 + 0×64 + 1×32 + 1×16 + 1×8 + 0×4 + 0×2 + 1×1
   = 128 + 32 + 16 + 8 + 1 = 185
   ```

3. **0x3F to binary:**
   ```
   3 = 0011
   F = 1111
   Answer: 00111111
   ```

4. **200 to hexadecimal:**
   ```
   200 ÷ 16 = 12 r 8
   12 ÷ 16 = 0 r 12 (C)
   Answer: 0xC8
   ```

### Exercise 2 Solutions:

1. **-25 in 8-bit two's complement:**
   ```
   +25 = 00011001
   Invert: 11100110
   Add 1:  11100111
   Answer: 11100111
   ```

2. **11001000 to decimal:**
   ```
   MSB = 1 (negative)
   Invert: 00110111
   Add 1:  00111000 = 56
   Answer: -56
   ```

3. **50 + (-30):**
   ```
   50 = 00110010
   -30: +30 = 00011110
        Invert: 11100001
        Add 1:  11100010
   
   Add: 00110010 + 11100010 = 00010100 = 20
   Answer: 20
   ```

### Exercise 3 Solutions:

1. **Speedup calculation:**
   ```
   Speedup = 5 / 2 = 2.5×
   ```

2. **Execution time:**
   ```
   Cycles = 500,000 × 3.0 = 1,500,000
   Time = 1,500,000 / 1,500,000,000 = 0.001 seconds = 1 ms
   ```

3. **Amdahl's Law:**
   ```
   Speedup = 1 / [(1 - 0.6) + 0.6/3]
           = 1 / [0.4 + 0.2]
           = 1 / 0.6
           = 1.67×
   ```

---

## KEY TAKEAWAYS

1. **Computer Organization** deals with how components are implemented and connected

2. **von Neumann Architecture** includes: CPU (CU + ALU + Registers), Memory, I/O, System Bus

3. **Number Systems:**
   - Binary: Base 2 (0, 1)
   - Decimal: Base 10 (0-9)
   - Hexadecimal: Base 16 (0-9, A-F)

4. **Two's Complement** is the standard for representing signed integers

5. **Performance** depends on: Instruction Count × CPI × Clock Cycle Time

6. **Programming Levels:** High-level → Assembly → Machine Code → Hardware

---

## GLOSSARY

- **ALU**: Arithmetic Logic Unit - performs arithmetic and logical operations
- **Architecture**: The instruction set and organization visible to the programmer
- **Binary**: Base-2 number system using only 0 and 1
- **CPI**: Cycles Per Instruction - average number of clock cycles per instruction
- **CPU**: Central Processing Unit - the "brain" of the computer
- **Hexadecimal**: Base-16 number system (0-9, A-F)
- **ISA**: Instruction Set Architecture - the interface between hardware and software
- **Register**: High-speed storage location within the CPU
- **Two's Complement**: Method for representing signed integers
- **von Neumann Architecture**: Computer design with stored program concept

---

## NEXT CHAPTER

**[Chapter 2: Instruction Set Design (Part 1)](Chapter2_Instruction_Set_Design_Part1.md)**
- Introduction to MIPS Architecture
- MIPS Registers
- Memory Organization
- Basic Instructions
- Instruction Formats

---

*This material is part of CCIT4026: Introduction to Computer Organization*  
*HKU SPACE Community College*  
*Chapter 1 of 5*
