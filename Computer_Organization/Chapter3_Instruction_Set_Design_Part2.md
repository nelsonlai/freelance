# CHAPTER 3: INSTRUCTION SET DESIGN (PART 2)
## Introduction to Computer Organization (CCIT4026)
### HKU SPACE Community College

---

## TABLE OF CONTENTS

1. [Control Flow Instructions](#31-control-flow-instructions)
2. [Implementing High-Level Constructs](#32-implementing-high-level-constructs)
3. [Multiplication and Division](#33-multiplication-and-division)
4. [Addressing Modes](#34-addressing-modes)
5. [Pseudo-instructions](#35-pseudo-instructions)
6. [Practice Problems](#36-practice-problems---chapter-3)

---

## 3.1 Control Flow Instructions

### Conditional Branches

#### Branch if Equal (beq)

```assembly
beq  $t0, $t1, label   # if ($t0 == $t1) goto label
```

**Example:**
```assembly
        li   $t0, 5
        li   $t1, 5
        beq  $t0, $t1, equal    # Branch taken
        # Code if not equal
equal:  # Code if equal
```

#### Branch if Not Equal (bne)

```assembly
bne  $t0, $t1, label   # if ($t0 != $t1) goto label
```

**Example:**
```assembly
        li   $t0, 5
        li   $t1, 10
        bne  $t0, $t1, notequal # Branch taken
        # Code if equal
notequal: # Code if not equal
```

### Comparison Instructions

#### Set on Less Than (slt)

```assembly
slt  $t0, $t1, $t2     # $t0 = ($t1 < $t2) ? 1 : 0
```

**Example:**
```assembly
li   $t1, 5
li   $t2, 10
slt  $t0, $t1, $t2     # $t0 = 1 (since 5 < 10)
```

#### Set on Less Than Immediate (slti)

```assembly
slti $t0, $t1, 100     # $t0 = ($t1 < 100) ? 1 : 0
```

#### Unsigned Comparisons

```assembly
sltu  $t0, $t1, $t2    # Unsigned comparison
sltiu $t0, $t1, 100    # Unsigned immediate
```

### Combined Comparison and Branch

```assembly
# Check if $t1 < $t2, branch if true
slt  $t0, $t1, $t2     # Set $t0 if $t1 < $t2
bne  $t0, $zero, label # Branch if $t0 != 0
```

### Unconditional Jumps

#### Jump (j)

```assembly
j    label             # Unconditional jump to label
```

**Example:**
```assembly
        li   $t0, 1
        j    skip          # Always jump
        li   $t0, 2        # This is skipped
skip:   # $t0 contains 1
```

#### Jump and Link (jal)

```assembly
jal  function          # Jump to function, save return address in $ra
```

**Usage:** Function calls
- Saves PC+4 (next instruction) in $ra
- Jumps to target address

**Example:**
```assembly
main:
        jal  myfunction    # Call function
        # Continue here after return
        
myfunction:
        # Function code
        jr   $ra           # Return to caller
```

#### Jump Register (jr)

```assembly
jr   $ra               # Jump to address in $ra
```

**Usage:** Return from function
- Jumps to address stored in register
- Typically used with $ra for returns

---

## 3.2 Implementing High-Level Constructs

### If-Then Statement

**C Code:**
```c
if (a == b)
    c = 1;
```

**MIPS Assembly:**
```assembly
# Assume: $s0=a, $s1=b, $s2=c

        bne  $s0, $s1, endif   # if (a != b) skip
        li   $s2, 1            # c = 1
endif:  # continue
```

### If-Then-Else Statement

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

### If-Else with Greater Than

**C Code:**
```c
if (x > y)
    z = x;
else
    z = y;
```

**MIPS Assembly:**
```assembly
# $s0=x, $s1=y, $s2=z

        slt  $t0, $s1, $s0     # $t0 = (y < x) i.e., (x > y)
        bne  $t0, $zero, then  # if (x > y) goto then
        move $s2, $s1          # z = y
        j    endif
then:   move $s2, $s0          # z = x
endif:
```

### While Loop

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

### Do-While Loop

**C Code:**
```c
do {
    sum = sum + i;
    i = i + 1;
} while (i < n);
```

**MIPS Assembly:**
```assembly
# Assume: $s0=i, $s1=n, $s2=sum

do:     add  $s2, $s2, $s0     # sum = sum + i
        addi $s0, $s0, 1       # i = i + 1
        slt  $t0, $s0, $s1     # $t0 = (i < n)
        bne  $t0, $zero, do    # if (i < n) repeat
        # continue here
```

### For Loop

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

### Nested Loops

**C Code:**
```c
for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
        sum = sum + i * j;
    }
}
```

**MIPS Assembly:**
```assembly
# $s0=i, $s1=j, $s2=sum

        li   $s0, 0            # i = 0
outer:  li   $t0, 3
        slt  $t1, $s0, $t0     # i < 3?
        beq  $t1, $zero, done
        
        li   $s1, 0            # j = 0
inner:  slt  $t1, $s1, $t0     # j < 3?
        beq  $t1, $zero, next_i
        
        mul  $t2, $s0, $s1     # i * j
        add  $s2, $s2, $t2     # sum += i * j
        
        addi $s1, $s1, 1       # j++
        j    inner
        
next_i: addi $s0, $s0, 1       # i++
        j    outer
done:
```

### Switch/Case Statement

**C Code:**
```c
switch (x) {
    case 0: y = 1; break;
    case 1: y = 2; break;
    case 2: y = 3; break;
    default: y = 0;
}
```

**MIPS Assembly (Jump Table Method):**
```assembly
# $s0=x, $s1=y

.data
jump_table: .word case0, case1, case2

.text
        # Bounds check
        bltz $s0, default      # if x < 0, default
        li   $t0, 3
        bge  $s0, $t0, default # if x >= 3, default
        
        # Jump table lookup
        la   $t0, jump_table
        sll  $t1, $s0, 2       # offset = x * 4
        add  $t0, $t0, $t1     # address of jump_table[x]
        lw   $t2, 0($t0)       # load target address
        jr   $t2               # jump to case
        
case0:  li   $s1, 1
        j    end_switch
case1:  li   $s1, 2
        j    end_switch
case2:  li   $s1, 3
        j    end_switch
default: li  $s1, 0
end_switch:
```

---

## 3.3 Multiplication and Division

### Multiplication

#### Multiply (mult/multu)

```assembly
mult  $t0, $t1         # HI:LO = $t0 × $t1 (signed, 64-bit result)
multu $t0, $t1         # HI:LO = $t0 × $t1 (unsigned)
```

**Result Storage:**
- **LO**: Lower 32 bits
- **HI**: Upper 32 bits

**Accessing Results:**
```assembly
mflo  $t2              # Move from LO to $t2
mfhi  $t3              # Move from HI to $t3
```

**Example: Simple Multiplication**
```assembly
li   $t0, 5
li   $t1, 10
mult $t0, $t1          # HI:LO = 5 × 10 = 50
mflo $t2               # $t2 = 50
# HI = 0 (no overflow)
```

**Example: Large Multiplication**
```assembly
li   $t0, 0x40000000   # 2^30
li   $t1, 8            # 8
mult $t0, $t1          # Result = 2^33
mflo $t2               # $t2 = 0 (lower 32 bits)
mfhi $t3               # $t3 = 2 (upper 32 bits)
                       # Full result: 0x200000000
```

#### Pseudo-instruction (MARS)

```assembly
mul   $t0, $t1, $t2    # $t0 = $t1 × $t2 (simplified)
```

**Note:** Only stores 32-bit result (lower bits)

### Division

#### Divide (div/divu)

```assembly
div   $t0, $t1         # LO = $t0 / $t1 (quotient)
                       # HI = $t0 % $t1 (remainder)
divu  $t0, $t1         # Unsigned division
```

**Example: Divide by 10**
```assembly
li    $t0, 157         # dividend
li    $t1, 10          # divisor
div   $t0, $t1         # 157 / 10
mflo  $t2              # $t2 = 15 (quotient)
mfhi  $t3              # $t3 = 7 (remainder)
```

**Example: Check if Even/Odd**
```assembly
li   $t0, 42
li   $t1, 2
div  $t0, $t1
mfhi $t2               # $t2 = remainder
beq  $t2, $zero, even  # if remainder == 0, even
# odd
j    continue
even:
# even
continue:
```

### Important Notes

1. **No Overflow Detection** in mult/div
2. **Division by Zero** causes exception
3. **Must use mflo/mfhi** to access results
4. **HI/LO modified** by mult/div operations

---

## 3.4 Addressing Modes

### 1. Register Addressing

**Format:** Operands are in registers

```assembly
add  $t0, $t1, $t2     # All operands are registers
```

**Advantages:**
- Fastest (no memory access)
- Most common in RISC

### 2. Immediate Addressing

**Format:** One operand is a constant in the instruction

```assembly
addi $t0, $t1, 100     # 100 is an immediate value
```

**Characteristics:**
- Immediate value: 16 bits (signed)
- Range: -32768 to +32767
- No memory access needed

### 3. Base (Displacement) Addressing

**Format:** `offset(register)`

```assembly
lw   $t0, 100($t1)     # Address = $t1 + 100
```

**Usage:**
- Array access
- Structure member access
- Stack operations

**Example:**
```assembly
# Access A[3] where $t0 has base address
lw   $t1, 12($t0)      # Load A[3] (offset = 3 × 4)
```

### 4. PC-Relative Addressing

**Format:** Branch instructions

```assembly
beq  $t0, $t1, label   # Address = PC + 4 + offset
```

**Characteristics:**
- Offset is 16-bit signed (in words)
- Range: -32KB to +32KB
- Enables position-independent code

**Calculation:**
```
Target Address = (PC + 4) + (offset << 2)
```

### 5. Pseudo-Direct Addressing

**Format:** Jump instructions

```assembly
j    label             # Address = (PC+4)[31:28] | (address << 2)
```

**Characteristics:**
- 26-bit address field
- Combined with upper 4 bits of PC+4
- Range: 256MB region

### Addressing Mode Summary

| Mode | Instructions | Example | Access Speed |
|------|-------------|---------|--------------|
| Register | add, sub | `add $t0, $t1, $t2` | Fastest |
| Immediate | addi, ori | `addi $t0, $t1, 100` | Fast |
| Base | lw, sw | `lw $t0, 8($t1)` | Slower (memory) |
| PC-Relative | beq, bne | `beq $t0, $t1, label` | N/A |
| Pseudo-Direct | j, jal | `j label` | N/A |

---

## 3.5 Pseudo-instructions

Pseudo-instructions are **not real MIPS instructions** but are provided by the assembler for convenience. They are translated into one or more real instructions.

### Load Immediate (li)

**Pseudo-instruction:**
```assembly
li   $t0, 100          # Load immediate value
```

**Translation (small immediate):**
```assembly
addi $t0, $zero, 100   # One instruction
```

**Translation (large immediate):**
```assembly
li   $t0, 0x12345678   
# Translates to:
lui  $t0, 0x1234       # Load upper 16 bits
ori  $t0, $t0, 0x5678  # OR in lower 16 bits
```

### Load Address (la)

**Pseudo-instruction:**
```assembly
la   $t0, label        # Load address of label
```

**Translation:**
```assembly
lui  $t0, upper(label)
ori  $t0, $t0, lower(label)
```

**Example:**
```assembly
.data
msg: .asciiz "Hello"

.text
        la   $a0, msg       # Load address of msg
        li   $v0, 4
        syscall             # Print string
```

### Move (move)

**Pseudo-instruction:**
```assembly
move $t0, $t1          # Copy $t1 to $t0
```

**Translation:**
```assembly
add  $t0, $t1, $zero   # $t0 = $t1 + 0
# or
or   $t0, $t1, $zero   # $t0 = $t1 | 0
```

### Branch Comparisons

**Pseudo-instructions:**
```assembly
blt  $t0, $t1, label   # Branch if less than
bgt  $t0, $t1, label   # Branch if greater than
ble  $t0, $t1, label   # Branch if less than or equal
bge  $t0, $t1, label   # Branch if greater than or equal
```

**Translation of `blt $t0, $t1, label`:**
```assembly
slt  $at, $t0, $t1     # $at = ($t0 < $t1)
bne  $at, $zero, label # if $at != 0, branch
```

**Translation of `bge $t0, $t1, label`:**
```assembly
slt  $at, $t0, $t1     # $at = ($t0 < $t1)
beq  $at, $zero, label # if $at == 0, branch
```

### Not (not)

**Pseudo-instruction:**
```assembly
not  $t0, $t1          # Bitwise NOT
```

**Translation:**
```assembly
nor  $t0, $t1, $zero   # $t0 = ~($t1 | 0)
```

### Negate (neg)

**Pseudo-instruction:**
```assembly
neg  $t0, $t1          # $t0 = -$t1
```

**Translation:**
```assembly
sub  $t0, $zero, $t1   # $t0 = 0 - $t1
```

### Clear (clear)

**Pseudo-instruction:**
```assembly
clear $t0              # Set $t0 to 0
```

**Translation:**
```assembly
add  $t0, $zero, $zero # $t0 = 0 + 0
# or
move $t0, $zero
```

### Why Use Pseudo-instructions?

1. **Readability**: Code is easier to understand
2. **Convenience**: Common operations simplified
3. **Portability**: Assembler handles details

**Example Comparison:**

```assembly
# Without pseudo-instructions
slt  $at, $t0, $t1
bne  $at, $zero, label

# With pseudo-instruction
blt  $t0, $t1, label   # More readable
```

---

## 3.6 Practice Problems - Chapter 3

### Problem 1: Implement If Statement

**C Code:**
```c
if (x > y)
    z = x;
else
    z = y;
```

**Solution:**
```assembly
# $s0=x, $s1=y, $s2=z

        slt  $t0, $s1, $s0     # $t0 = (y < x), i.e., (x > y)
        bne  $t0, $zero, then  # if (x > y) goto then
        move $s2, $s1          # z = y
        j    endif
then:   move $s2, $s0          # z = x
endif:
```

### Problem 2: Array Sum

**C Code:**
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

### Problem 3: Factorial (Loop)

**C Code:**
```c
int factorial = 1;
for (int i = 1; i <= n; i++) {
    factorial *= i;
}
```

**Solution:**
```assembly
# $s0=n, $s1=factorial

        li   $s1, 1            # factorial = 1
        li   $t0, 1            # i = 1
        
loop:   slt  $t1, $s0, $t0     # n < i?
        bne  $t1, $zero, done  # if n < i, done
        
        mul  $s1, $s1, $t0     # factorial *= i
        addi $t0, $t0, 1       # i++
        j    loop
done:   # $s1 contains factorial
```

### Problem 4: Find Maximum

**C Code:**
```c
int max = A[0];
for (int i = 1; i < n; i++) {
    if (A[i] > max)
        max = A[i];
}
```

**Solution:**
```assembly
# $s0=n, $s1=base address of A, $s2=max

        lw   $s2, 0($s1)       # max = A[0]
        li   $t0, 1            # i = 1
        
loop:   slt  $t1, $t0, $s0     # i < n?
        beq  $t1, $zero, done
        
        sll  $t2, $t0, 2       # offset = i × 4
        add  $t3, $s1, $t2     # address of A[i]
        lw   $t4, 0($t3)       # $t4 = A[i]
        
        slt  $t5, $s2, $t4     # max < A[i]?
        beq  $t5, $zero, skip
        move $s2, $t4          # max = A[i]
        
skip:   addi $t0, $t0, 1       # i++
        j    loop
done:
```

### Problem 5: Count Evens

**Task:** Count how many even numbers in array A[10]

**Solution:**
```assembly
.data
A:      .word 1, 2, 3, 4, 5, 6, 7, 8, 9, 10

.text
        la   $t0, A            # Base address
        li   $t1, 0            # count = 0
        li   $t2, 10           # size
        li   $t3, 0            # i = 0
        
loop:   bge  $t3, $t2, done
        
        sll  $t4, $t3, 2       # offset
        add  $t5, $t0, $t4     # address
        lw   $t6, 0($t5)       # A[i]
        
        andi $t7, $t6, 1       # Check LSB
        bne  $t7, $zero, odd   # if odd, skip
        addi $t1, $t1, 1       # count++
        
odd:    addi $t3, $t3, 1       # i++
        j    loop
done:   # $t1 contains count of evens
```

---

## KEY TAKEAWAYS

1. **Conditional branches** use comparison + branch instructions

2. **High-level constructs** (if, while, for) translate to branches and labels

3. **Multiplication/Division** use special HI/LO registers

4. **Five addressing modes** in MIPS:
   - Register
   - Immediate
   - Base/Displacement
   - PC-Relative
   - Pseudo-Direct

5. **Pseudo-instructions** simplify programming but aren't real instructions

---

## NEXT CHAPTER

**[Chapter 4: Instruction Set Design (Part 3)](Chapter4_Instruction_Set_Design_Part3.md)**
- Function Calls and Stack
- Recursion
- Arrays and Pointers
- Structures

---

*This material is part of CCIT4026: Introduction to Computer Organization*  
*HKU SPACE Community College*  
*Chapter 3 of 5*
