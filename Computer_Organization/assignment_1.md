# Assignment 1 Answers — Introduction to Computer Organization (CCIT 4026)

**Student Number:** 20285660  
**HKU SPACE Community College — AY2526 S2**

---

## Digit Extraction from Student Number 20285660

From **20285660**:

| Position | Digit | Usage |
|----------|-------|-------|
| 1st (rightmost) | 0 | Starting address of data segment (Q2) → 0x000000A0 |
| 2nd (second-rightmost) | 6 | Instruction pair selection (Q3) |
| Last 5 digits (d4 d3 d2 d1 d0) | 8, 5, 6, 6, 0 | Q2 values |
| 5th–8th digits (a0, a1, b0, b1) | 5, 6, 6, 0 | Q4 array values |

---

## Q1. [30 marks] Memory Map of Data Segment

### Important Note

The assignment PDF states “Given the following data segment definition” but the specific `.data` segment code was not visible in the extracted text (it may appear in an image or formatted block). **Use the exact data segment provided in your assignment handout** and apply the method below.

### Method: Building the Memory Map

Given:
- **Base address:** 0x2000
- **Endianness:** Little Endian (least significant byte at lowest address)
- **Initial state:** All memory = 0 before data is loaded
- **Convention:** Mark reserved (unused) bytes with **X**

#### MIPS Data Directives and Sizes

| Directive | Size | Example |
|-----------|------|---------|
| `.space n` | n bytes | `.space 2` → 2 bytes |
| `.byte` | 1 byte | `.byte 0x12` → 1 byte |
| `.half` | 2 bytes | `.half 0x3456` → 2 bytes |
| `.word` | 4 bytes | `.word 0x12345678` → 4 bytes |
| `.asciiz "str"` | strlen + 1 bytes | `"Hi"` → 3 bytes |

#### Little Endian Layout

For multi-byte values, the **least significant byte** is stored at the **lowest address**:

- Example: `0x12345678`
  - 0x2000: `0x78` (LSB)
  - 0x2001: `0x56`
  - 0x2002: `0x34`
  - 0x2003: `0x12` (MSB)

#### Given Data Segment (from assignment)

```
.data
.space 3
Str1: .ascii "abc"
.align 2
Str2: .asciiz "DEFG"
Hf:   .half 18
W:    .word -1, 3
B:    .byte 4
Str3: .asciiz "\n"
```

**Layout:**

| Byte Address | Label | Content | Explanation |
|--------------|-------|---------|-------------|
| 0x2000 | X | X | `.space 3` first byte |
| 0x2001 | X | X | `.space 3` second byte |
| 0x2002 | X | X | `.space 3` third byte |
| 0x2003 | Str1 | 0x61 | 'a' |
| 0x2004 | Str1 | 0x62 | 'b' |
| 0x2005 | Str1 | 0x63 | 'c' |
| 0x2006 | Str2 | 0x44 | 'D' |
| 0x2007 | Str2 | 0x45 | 'E' |
| 0x2008 | Str2 | 0x46 | 'F' |
| 0x2009 | Str2 | 0x47 | 'G' |
| 0x200A | Str2 | 0x00 | null |
| 0x200B | Hf | 0x12 | 18 LSB |
| 0x200C | Hf | 0x00 | 18 MSB |
| 0x200D | W | 0xFF | -1 byte 0 |
| 0x200E | W | 0xFF | -1 byte 1 |
| 0x200F | W | 0xFF | -1 byte 2 |
| 0x2010 | W | 0xFF | -1 byte 3 |
| 0x2011 | W | 0x03 | 3 byte 0 |
| 0x2012 | W | 0x00 | 3 byte 1 |
| 0x2013 | W | 0x00 | 3 byte 2 |
| 0x2014 | W | 0x00 | 3 byte 3 |
| 0x2015 | B | 0x04 | 4 |
| 0x2016 | Str3 | 0x0A | newline |
| 0x2017 | Str3 | 0x00 | null |
| 0x2018 | — | 0x00 | (beyond data) |
| 0x2019 | — | 0x00 | (beyond data) |
| 0x201A | — | 0x00 | (beyond data) |
| 0x201B | — | 0x00 | (beyond data) |

Place **X** for reserved bytes (0x2000–0x2002). Addresses 0x2018–0x201B are beyond the defined data; content remains 0 per the initialization assumption.

---

## Q2. [20 marks] Register Values After Program Execution

### Student-Specific Values (20285660)

- **1st student number:** 0 → data segment base = **0x000000A0**
- **d4 d3 d2 d1 d0** = 8, 5, 6, 6, 0

### Data Segment Layout

```asm
.data
sid: .word d2 d1 d0    # Three consecutive words
.word d4               # One more word
s:   .word d3          # One word
```

| Address | Content | Label |
|---------|---------|-------|
| 0xA0 (sid+0) | d2 = 6 | sid |
| 0xA4 (sid+4) | d1 = 6 | |
| 0xA8 (sid+8) | d0 = 0 | |
| 0xAC (sid+12) | d4 = 8 | |
| 0xB0 (s) | d3 = 5 | s |

### Step-by-Step Trace

| Instruction | Operation | Register Values |
|-------------|-----------|-----------------|
| `la $t0, sid` | Load address of `sid` | $t0 = 0xA0 |
| `lw $t1, 8($t0)` | Load word at sid+8 | $t1 = mem[0xA8] = **d0 = 0** | # $t1 = 0
| `la $t2, s` | Load address of `s` | $t2 = 0xB0 = **160** |
| `lw $t3, -4($t2)` | Load word at s−4 = 0xAC | $t3 = mem[0xAC] = **d4 = 8** | # $t3 = 8
| `li $t4, 0x20` | Load immediate 0x20 | $t4 = 32 | # $t4 = 32
| `add $t4, $t4, $t1` | $t4 = 32 + 0 | $t4 = **32** |
| `sub $t5, $t4, $t3` | $t5 = 32 − 8 | $t5 = **24** |

### Final Register Values (Decimal)

| Register | Value | Derivation |
|----------|-------|------------|
| **$t1** | **0** | d0 from sid+8 |
| **$t2** | **160** | Address of s (0xB0) |
| **$t3** | **8** | d4 from s−4 |
| **$t4** | **32** | 0x20 + $t1 = 32 + 0 |
| **$t5** | **24** | $t4 − $t3 = 32 − 8 |

---

## Q3. [25 marks] Machine Code Encoding

### Instruction Selection (2nd student number = 6)

From the assignment table, for **2nd student number = 6**:

- **Instruction 1:** `add $s5, $t5, $v1`
- **Instruction 2:** `lw $t1, -12($s1)`

---

### Instruction 1: `add $s5, $t5, $v1`

**Format:** R-type

**Fields:**

| Field | Value | Registers / Meaning |
|-------|-------|---------------------|
| op | 000000 | R-type |
| rs | $t5 (21) | First source |
| rt | $v1 (3) | Second source |
| rd | $s5 (21) | Destination |
| shamt | 00000 | Not used |
| funct | 100000 | `add` |

**Binary:**
```
000000  10101  00011  10101  00000  100000
op      rs     rt     rd     shamt  funct
```

**HEX:** `0x02B5A820`

**Check:** op=0, rs=21, rt=3, rd=21, funct=32.

---

### Instruction 2: `lw $t1, -12($s1)`

**Format:** I-type  
**Layout:** op | rs | rt | immediate

- **op:** 100011 (35) — load word  
- **rs:** $s1 (17) — base register  
- **rt:** $t1 (9) — destination  
- **immediate:** −12 = 0xFFF4 (16-bit two’s complement)

**Two’s complement for −12:**
- 12 in binary: 0000 0000 0000 1100  
- Invert: 1111 1111 1111 0011  
- Add 1: 1111 1111 1111 0100 = 0xFFF4  

**Binary:**
```
100011  10001  01001  1111111111110100
op      rs     rt    immediate
```

**HEX:** `0x8E29FFF4`

**Check:** op=0x23, rs=17, rt=9, imm=0xFFF4.

---

### Q3 Summary

| Instruction | Machine Code (HEX) |
|-------------|--------------------|
| `add $s5, $t5, $v1` | **0x02B5A820** |
| `lw $t1, -12($s1)` | **0x8E29FFF4** |

---

## Q4. [25 marks] Dot Product Program

### Values from Student Number 20285660

For student number 20285660, the 5th–8th digits are: **5, 6, 6, 0**

- **a0 = 5**, **a1 = 6**, **b0 = 6**, **b1 = 0**

### Dot Product Calculation

\[
C = \langle A \cdot B \rangle = \sum_{i=0}^{1} a_i b_i = a_0 b_0 + a_1 b_1
\]

\[
C = 5 * 6 + 6 * 0 = 30 + 0 = 30
\]

### Expected Output

```
The dot product C = 30
```

### MIPS Program

```asm
# Dot Product Program
# Student Number: 20285660
# a0=5, a1=6, b0=6, b1=0
# C = 5*6 + 6*0 = 30

.data
Array_A: .word 5, 6      # a0, a1
Array_B: .word 6, 0      # b0, b1
msg:     .asciiz "The dot product C = "
newline: .asciiz "\n"

.text
.globl main
main:
    # Load array base addresses
    la $t0, Array_A
    la $t1, Array_B

    # Compute a0 * b0
    lw $t2, 0($t0)       # a0
    lw $t3, 0($t1)       # b0
    mul $t4, $t2, $t3    # a0 * b0

    # Compute a1 * b1
    lw $t2, 4($t0)       # a1
    lw $t3, 4($t1)       # b1
    mul $t5, $t2, $t3    # a1 * b1

    # C = a0*b0 + a1*b1
    add $t6, $t4, $t5    # $t6 = C

    # Print "The dot product C = "
    li $v0, 4
    la $a0, msg
    syscall

    # Print C
    li $v0, 1
    move $a0, $t6
    syscall

    # Print newline
    li $v0, 4
    la $a0, newline
    syscall

    # Exit
    li $v0, 10
    syscall
```

### Program Logic

1. **Addresses:** `$t0` → Array_A, `$t1` → Array_B.
2. **a0×b0:** Load A[0], B[0], multiply, store in `$t4`.
3. **a1×b1:** Load A[1], B[1], multiply, store in `$t5`.
4. **C:** Add `$t4` and `$t5` into `$t6`.
5. **Print:** Syscall 4 for the message, syscall 1 for C, then newline.
6. **Exit:** Syscall 10.

**Note:** Run this in MARS and capture the source code and “Run I/O” output for your submission.

---

## Quick Reference Summary

| Question | Key Values | Answer |
|----------|------------|--------|
| **Q1** | Base 0x2000, Little Endian | See complete memory map table above (Str1, Str2, Hf, W, B, Str3) |
| **Q2** | d4=8, d3=5, d2=6, d1=6, d0=0; base 0xA0 | $t1=0, $t2=160, $t3=8, $t4=32, $t5=24 |
| **Q3** | 2nd digit = 6 | Instruction 1: `0x02B5A820`; Instruction 2: `0x8E29FFF4` |
| **Q4** | a0=5, a1=6, b0=6, b1=0 | C = 30 |
