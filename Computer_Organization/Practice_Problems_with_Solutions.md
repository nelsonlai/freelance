# PRACTICE PROBLEMS WITH SOLUTIONS
## Introduction to Computer Organization (CCIT4026)

---

## TABLE OF CONTENTS

1. [Chapter 1: Introduction](#chapter-1-introduction)
2. [Chapter 2: Basic Instructions](#chapter-2-basic-instructions)
3. [Chapter 3: Control Flow](#chapter-3-control-flow)
4. [Chapter 4: Functions](#chapter-4-functions)
5. [Chapter 5: I/O and Strings](#chapter-5-io-and-strings)
6. [Comprehensive Problems](#comprehensive-problems)

---

## CHAPTER 1: INTRODUCTION

### Problem 1.1: Number System Conversions

**Question:**
Convert the following numbers:
1. Decimal 157 to binary
2. Binary 11010110 to decimal
3. Hexadecimal 0x2F to binary
4. Decimal 255 to hexadecimal

**Solution:**

1. **Decimal 157 to binary:**
   ```
   157 ÷ 2 = 78 remainder 1
   78 ÷ 2 = 39 remainder 0
   39 ÷ 2 = 19 remainder 1
   19 ÷ 2 = 9 remainder 1
   9 ÷ 2 = 4 remainder 1
   4 ÷ 2 = 2 remainder 0
   2 ÷ 2 = 1 remainder 0
   1 ÷ 2 = 0 remainder 1
   
   Reading from bottom to top: 10011101
   ```
   **Answer: 10011101**

2. **Binary 11010110 to decimal:**
   ```
   1×2^7 + 1×2^6 + 0×2^5 + 1×2^4 + 0×2^3 + 1×2^2 + 1×2^1 + 0×2^0
   = 128 + 64 + 0 + 16 + 0 + 4 + 2 + 0
   = 214
   ```
   **Answer: 214**

3. **Hexadecimal 0x2F to binary:**
   ```
   2 = 0010
   F = 1111
   Combined: 00101111
   ```
   **Answer: 00101111 or 101111**

4. **Decimal 255 to hexadecimal:**
   ```
   255 ÷ 16 = 15 remainder 15
   15 ÷ 16 = 0 remainder 15
   
   15 = F in hex
   ```
   **Answer: 0xFF**

---

### Problem 1.2: Two's Complement

**Question:**
Using 8-bit two's complement representation:
1. Represent -42
2. What decimal value does 10110011 represent?
3. Calculate: 25 + (-15)

**Solution:**

1. **Represent -42:**
   ```
   Step 1: +42 in binary = 00101010
   Step 2: Invert bits    = 11010101
   Step 3: Add 1          = 11010110
   ```
   **Answer: 11010110**

2. **10110011 to decimal:**
   ```
   MSB is 1, so it's negative
   
   Invert: 01001100
   Add 1:  01001101 = 77
   
   Therefore: -77
   ```
   **Answer: -77**

3. **25 + (-15):**
   ```
   25 in binary:  00011001
   -15: +15 =     00001111
        Invert:   11110000
        Add 1:    11110001
   
   Add them:      00011001
                + 11110001
                -----------
                  00001010 = 10
   ```
   **Answer: 10**

---

### Problem 1.3: Performance Calculation

**Question:**
A processor executes a program with the following characteristics:
- 2,000,000 instructions
- Average CPI (Cycles Per Instruction) = 3
- Clock frequency = 2.5 GHz

Calculate:
1. Total number of clock cycles
2. Execution time in milliseconds

**Solution:**

1. **Total clock cycles:**
   ```
   Cycles = Instruction Count × CPI
          = 2,000,000 × 3
          = 6,000,000 cycles
   ```
   **Answer: 6,000,000 cycles**

2. **Execution time:**
   ```
   Clock period = 1 / Frequency
                = 1 / 2,500,000,000
                = 0.4 nanoseconds
   
   Execution time = Cycles × Clock period
                  = 6,000,000 × 0.4 ns
                  = 2,400,000 ns
                  = 2.4 milliseconds
   ```
   **Answer: 2.4 ms**

---

## CHAPTER 2: BASIC INSTRUCTIONS

### Problem 2.1: Simple Arithmetic

**Question:**
Translate the following C code to MIPS assembly:
```c
int a = 5;
int b = 10;
int c = 15;
int result = (a + b) * 2 - c;
```
Assume: $s0=a, $s1=b, $s2=c, $s3=result

**Solution:**
```assembly
# Initialize variables
li   $s0, 5            # a = 5
li   $s1, 10           # b = 10
li   $s2, 15           # c = 15

# Calculate (a + b)
add  $t0, $s0, $s1     # $t0 = a + b = 15

# Multiply by 2 (shift left 1)
sll  $t0, $t0, 1       # $t0 = (a + b) * 2 = 30

# Subtract c
sub  $s3, $t0, $s2     # result = 30 - 15 = 15
```

**Answer: Final result is 15 in $s3**

---

### Problem 2.2: Array Access

**Question:**
Given an integer array A starting at address 0x10010000:
1. Write MIPS code to store value 42 in A[5]
2. Write MIPS code to load A[3] into register $t1

**Solution:**

1. **Store 42 in A[5]:**
```assembly
lui  $t0, 0x1001       # Load upper 16 bits of address
ori  $t0, $t0, 0x0000  # Complete address (0x10010000)
li   $t1, 42           # Value to store
sw   $t1, 20($t0)      # Store at offset 20 (5 × 4 bytes)
```

**Alternative (using pseudo-instruction):**
```assembly
la   $t0, A            # Load address of A
li   $t1, 42
sw   $t1, 20($t0)      # A[5] = 42
```

2. **Load A[3] into $t1:**
```assembly
la   $t0, A            # Load base address
lw   $t1, 12($t0)      # Load from offset 12 (3 × 4 bytes)
```

---

### Problem 2.3: Bit Manipulation

**Question:**
Given value in $t0:
1. Check if bit 3 is set (write code that sets $t1 to 1 if set, 0 if not)
2. Set bit 5
3. Clear bit 7

**Solution:**

1. **Check if bit 3 is set:**
```assembly
andi $t1, $t0, 0x8     # Mask bit 3 (0x8 = 0b1000)
srl  $t1, $t1, 3       # Shift to LSB position
# $t1 is now 1 if bit 3 was set, 0 otherwise
```

**Alternative:**
```assembly
andi $t1, $t0, 0x8     # Mask bit 3
sne  $t1, $t1, $zero   # Set $t1 = 1 if not zero (pseudo-instruction)
```

2. **Set bit 5:**
```assembly
ori  $t0, $t0, 0x20    # OR with 0b100000
```

3. **Clear bit 7:**
```assembly
andi $t0, $t0, 0xFF7F  # AND with 0b11111111011111111
```

---

### Problem 2.4: Register Usage

**Question:**
What's wrong with this code? Fix it.
```assembly
li   $s0, 10
li   $s1, 20
jal  calculate
# Expect $s0 still contains 10 here
# ...

calculate:
    add  $s0, $s0, $s1   # $s0 = $s0 + $s1
    jr   $ra
```

**Solution:**

**Problem:** The function modifies $s0, which is a saved register and should be preserved.

**Fixed version:**
```assembly
calculate:
    # Prologue: Save registers
    addi $sp, $sp, -8
    sw   $s0, 4($sp)
    sw   $ra, 0($sp)
    
    # Function body
    add  $s0, $s0, $s1   # $s0 = $s0 + $s1
    
    # Epilogue: Restore registers
    lw   $ra, 0($sp)
    lw   $s0, 4($sp)
    addi $sp, $sp, 8
    
    jr   $ra
```

**Better solution (use temporary register):**
```assembly
calculate:
    add  $t0, $s0, $s1   # Use temporary register
    # Store result somewhere or return in $v0
    move $v0, $t0
    jr   $ra
```

---

## CHAPTER 3: CONTROL FLOW

### Problem 3.1: If-Else Statement

**Question:**
Translate to MIPS:
```c
if (x >= y) {
    z = x - y;
} else {
    z = y - x;
}
```
Assume: $s0=x, $s1=y, $s2=z

**Solution:**
```assembly
        slt  $t0, $s0, $s1     # $t0 = (x < y)
        bne  $t0, $zero, else  # if (x < y) goto else
        
then:   sub  $s2, $s0, $s1     # z = x - y
        j    endif
        
else:   sub  $s2, $s1, $s0     # z = y - x

endif:  # continue here
```

**Alternative (using pseudo-instructions):**
```assembly
        blt  $s0, $s1, else    # if (x < y) goto else
        sub  $s2, $s0, $s1     # z = x - y
        j    endif
else:   sub  $s2, $s1, $s0     # z = y - x
endif:
```

---

### Problem 3.2: Nested If Statements

**Question:**
Implement:
```c
if (a > 0) {
    if (b > 0) {
        result = 1;
    } else {
        result = 2;
    }
} else {
    result = 3;
}
```
Assume: $s0=a, $s1=b, $s2=result

**Solution:**
```assembly
        # Check if a > 0
        slt  $t0, $zero, $s0   # $t0 = (0 < a)
        beq  $t0, $zero, else1 # if (a <= 0) goto else1
        
        # a > 0, now check b
        slt  $t1, $zero, $s1   # $t1 = (0 < b)
        beq  $t1, $zero, else2 # if (b <= 0) goto else2
        
        # Both a > 0 and b > 0
        li   $s2, 1            # result = 1
        j    endif
        
else2:  # a > 0 but b <= 0
        li   $s2, 2            # result = 2
        j    endif
        
else1:  # a <= 0
        li   $s2, 3            # result = 3
        
endif:  # continue
```

---

### Problem 3.3: Sum of N Numbers

**Question:**
Write MIPS code to calculate the sum of numbers from 1 to N.
```c
int sum = 0;
for (int i = 1; i <= N; i++) {
    sum = sum + i;
}
```
Assume: $s0=N, $s1=sum

**Solution:**
```assembly
        li   $s1, 0            # sum = 0
        li   $t0, 1            # i = 1
        
loop:   slt  $t1, $s0, $t0     # $t1 = (N < i)
        bne  $t1, $zero, done  # if (i > N) exit loop
        
        add  $s1, $s1, $t0     # sum += i
        addi $t0, $t0, 1       # i++
        j    loop
        
done:   # sum now contains result
```

**Alternative (more efficient comparison):**
```assembly
        li   $s1, 0            # sum = 0
        li   $t0, 1            # i = 1
        
loop:   bgt  $t0, $s0, done    # if (i > N) exit
        add  $s1, $s1, $t0     # sum += i
        addi $t0, $t0, 1       # i++
        j    loop
        
done:
```

---

### Problem 3.4: Find Maximum in Array

**Question:**
Write MIPS code to find the maximum value in an array of 10 integers.
```c
int max = A[0];
for (int i = 1; i < 10; i++) {
    if (A[i] > max) {
        max = A[i];
    }
}
```

**Solution:**
```assembly
.data
A:      .word 5, 12, 3, 8, 15, 7, 20, 4, 9, 11

.text
        la   $t0, A            # Base address of array
        lw   $s0, 0($t0)       # max = A[0]
        li   $t1, 1            # i = 1
        li   $t2, 10           # array length
        
loop:   bge  $t1, $t2, done    # if (i >= 10) exit
        
        # Calculate address of A[i]
        sll  $t3, $t1, 2       # $t3 = i × 4
        add  $t3, $t3, $t0     # $t3 = address of A[i]
        lw   $t4, 0($t3)       # $t4 = A[i]
        
        # Compare with max
        slt  $t5, $s0, $t4     # $t5 = (max < A[i])
        beq  $t5, $zero, skip  # if not, skip update
        move $s0, $t4          # max = A[i]
        
skip:   addi $t1, $t1, 1       # i++
        j    loop
        
done:   # $s0 now contains maximum value
```

---

### Problem 3.5: Factorial (Loop)

**Question:**
Calculate factorial of N using a loop.
```c
int factorial = 1;
for (int i = 1; i <= N; i++) {
    factorial = factorial * i;
}
```

**Solution:**
```assembly
        # Assume N in $s0, result in $s1
        li   $s1, 1            # factorial = 1
        li   $t0, 1            # i = 1
        
        # Handle N = 0 case
        beq  $s0, $zero, done  # if N == 0, done (result = 1)
        
loop:   bgt  $t0, $s0, done    # if (i > N) exit
        mul  $s1, $s1, $t0     # factorial *= i
        addi $t0, $t0, 1       # i++
        j    loop
        
done:   # $s1 contains factorial(N)
```

---

## CHAPTER 4: FUNCTIONS

### Problem 4.1: Simple Function

**Question:**
Write a MIPS function to calculate the absolute value of an integer.
```c
int abs(int x) {
    if (x < 0)
        return -x;
    else
        return x;
}
```

**Solution:**
```assembly
# Function: abs
# Input: $a0 = integer
# Output: $v0 = |$a0|

abs:
        slt  $t0, $a0, $zero   # $t0 = (x < 0)
        beq  $t0, $zero, pos   # if x >= 0, goto pos
        
        # x is negative, negate it
        sub  $v0, $zero, $a0   # $v0 = 0 - x = -x
        jr   $ra
        
pos:    # x is positive or zero
        move $v0, $a0          # $v0 = x
        jr   $ra
```

**Test code:**
```assembly
main:
        li   $a0, -15          # Test with -15
        jal  abs
        # $v0 should now contain 15
        
        li   $a0, 20           # Test with 20
        jal  abs
        # $v0 should now contain 20
```

---

### Problem 4.2: Function with Multiple Parameters

**Question:**
Write a function to calculate the average of three integers.
```c
int average(int a, int b, int c) {
    return (a + b + c) / 3;
}
```

**Solution:**
```assembly
# Function: average
# Inputs: $a0 = a, $a1 = b, $a2 = c
# Output: $v0 = (a + b + c) / 3

average:
        add  $t0, $a0, $a1     # $t0 = a + b
        add  $t0, $t0, $a2     # $t0 = a + b + c
        li   $t1, 3            # divisor
        div  $t0, $t1          # divide by 3
        mflo $v0               # get quotient
        jr   $ra

# Alternative (if remainder matters):
average_with_rounding:
        add  $t0, $a0, $a1
        add  $t0, $t0, $a2     # sum
        li   $t1, 3
        div  $t0, $t1
        mflo $v0               # quotient
        mfhi $t2               # remainder
        
        # Round up if remainder >= 2
        slti $t3, $t2, 2       # $t3 = (remainder < 2)
        bne  $t3, $zero, done  # if remainder < 2, done
        addi $v0, $v0, 1       # else round up
        
done:   jr   $ra
```

---

### Problem 4.3: Recursive Factorial

**Question:**
Implement factorial recursively.
```c
int factorial(int n) {
    if (n <= 1)
        return 1;
    else
        return n * factorial(n - 1);
}
```

**Solution:**
```assembly
# Function: factorial (recursive)
# Input: $a0 = n
# Output: $v0 = n!

factorial:
        # Prologue
        addi $sp, $sp, -8      # Allocate stack
        sw   $ra, 4($sp)       # Save return address
        sw   $a0, 0($sp)       # Save n
        
        # Base case: if (n <= 1) return 1
        slti $t0, $a0, 2       # $t0 = (n < 2)
        beq  $t0, $zero, recur # if n >= 2, recurse
        
        # Base case: return 1
        li   $v0, 1
        addi $sp, $sp, 8       # Deallocate (no need to restore)
        jr   $ra
        
recur:  # Recursive case
        addi $a0, $a0, -1      # n - 1
        jal  factorial         # factorial(n - 1)
        
        # Multiply n * factorial(n-1)
        lw   $a0, 0($sp)       # Restore n
        lw   $ra, 4($sp)       # Restore return address
        addi $sp, $sp, 8       # Deallocate
        
        mul  $v0, $a0, $v0     # n * factorial(n-1)
        jr   $ra
```

**Test code:**
```assembly
main:
        li   $a0, 5            # Calculate 5!
        jal  factorial
        # $v0 should contain 120
        
        move $a0, $v0          # Print result
        li   $v0, 1
        syscall
        
        li   $v0, 10           # Exit
        syscall
```

---

### Problem 4.4: Greatest Common Divisor (GCD)

**Question:**
Implement GCD using Euclidean algorithm (recursive).
```c
int gcd(int a, int b) {
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}
```

**Solution:**
```assembly
# Function: gcd (recursive)
# Inputs: $a0 = a, $a1 = b
# Output: $v0 = gcd(a, b)

gcd:
        # Prologue
        addi $sp, $sp, -4
        sw   $ra, 0($sp)
        
        # Base case: if (b == 0) return a
        bne  $a1, $zero, recur # if b != 0, recurse
        
        move $v0, $a0          # return a
        lw   $ra, 0($sp)
        addi $sp, $sp, 4
        jr   $ra
        
recur:  # Recursive case: gcd(b, a % b)
        # Calculate a % b
        div  $a0, $a1          # a / b
        mfhi $t0               # $t0 = a % b
        
        # Set up arguments for next call
        move $a0, $a1          # First arg = b
        move $a1, $t0          # Second arg = a % b
        
        jal  gcd               # Recursive call
        
        # Result already in $v0
        lw   $ra, 0($sp)
        addi $sp, $sp, 4
        jr   $ra
```

---

### Problem 4.5: Fibonacci (Iterative)

**Question:**
Calculate the nth Fibonacci number iteratively.
```c
int fib(int n) {
    if (n <= 1) return n;
    int a = 0, b = 1;
    for (int i = 2; i <= n; i++) {
        int temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}
```

**Solution:**
```assembly
# Function: fibonacci (iterative)
# Input: $a0 = n
# Output: $v0 = fib(n)

fibonacci:
        # Base cases
        slti $t0, $a0, 2       # n < 2?
        beq  $t0, $zero, loop_init
        move $v0, $a0          # return n (0 or 1)
        jr   $ra
        
loop_init:
        li   $t1, 0            # a = 0
        li   $t2, 1            # b = 1
        li   $t3, 2            # i = 2
        
loop:   bgt  $t3, $a0, done    # if i > n, done
        
        add  $t4, $t1, $t2     # temp = a + b
        move $t1, $t2          # a = b
        move $t2, $t4          # b = temp
        
        addi $t3, $t3, 1       # i++
        j    loop
        
done:   move $v0, $t2          # return b
        jr   $ra
```

---

## CHAPTER 5: I/O AND STRINGS

### Problem 5.1: Read and Sum Integers

**Question:**
Write a program that:
1. Asks how many numbers to read
2. Reads N integers from user
3. Displays the sum

**Solution:**
```assembly
.data
prompt_n:   .asciiz "How many numbers? "
prompt_num: .asciiz "Enter number: "
result_msg: .asciiz "Sum: "
newline:    .asciiz "\n"

.text
.globl main

main:
        # Ask for count
        li   $v0, 4
        la   $a0, prompt_n
        syscall
        
        li   $v0, 5            # Read count
        syscall
        move $s0, $v0          # $s0 = N
        
        li   $s1, 0            # sum = 0
        li   $t0, 0            # counter = 0
        
loop:   bge  $t0, $s0, done    # if counter >= N, done
        
        # Prompt for number
        li   $v0, 4
        la   $a0, prompt_num
        syscall
        
        # Read number
        li   $v0, 5
        syscall
        
        add  $s1, $s1, $v0     # sum += number
        addi $t0, $t0, 1       # counter++
        j    loop
        
done:   # Display result
        li   $v0, 4
        la   $a0, result_msg
        syscall
        
        li   $v0, 1
        move $a0, $s1
        syscall
        
        # Exit
        li   $v0, 10
        syscall
```

---

### Problem 5.2: String Length

**Question:**
Write a function to calculate the length of a null-terminated string.
```c
int strlen(char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}
```

**Solution:**
```assembly
# Function: strlen
# Input: $a0 = address of string
# Output: $v0 = length

strlen:
        li   $v0, 0            # length = 0
        move $t0, $a0          # current position
        
loop:   lb   $t1, 0($t0)       # Load byte
        beq  $t1, $zero, done  # if null, done
        
        addi $v0, $v0, 1       # length++
        addi $t0, $t0, 1       # next character
        j    loop
        
done:   jr   $ra

# Test program
.data
test_str: .asciiz "Hello"

.text
main:
        la   $a0, test_str
        jal  strlen
        # $v0 should contain 5
        
        move $a0, $v0
        li   $v0, 1
        syscall                # Print length
        
        li   $v0, 10
        syscall
```

---

### Problem 5.3: String Copy

**Question:**
Implement strcpy function.
```c
void strcpy(char *dest, char *src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}
```

**Solution:**
```assembly
# Function: strcpy
# Inputs: $a0 = destination, $a1 = source

strcpy:
        move $t0, $a0          # dest pointer
        move $t1, $a1          # src pointer
        
loop:   lb   $t2, 0($t1)       # Load from source
        sb   $t2, 0($t0)       # Store to destination
        beq  $t2, $zero, done  # If null, done
        
        addi $t0, $t0, 1       # Next dest
        addi $t1, $t1, 1       # Next src
        j    loop
        
done:   jr   $ra

# Test program
.data
source:     .asciiz "Hello"
dest:       .space 50

.text
main:
        la   $a0, dest
        la   $a1, source
        jal  strcpy
        
        # Print copied string
        li   $v0, 4
        la   $a0, dest
        syscall
        
        li   $v0, 10
        syscall
```

---

### Problem 5.4: Count Vowels

**Question:**
Count the number of vowels (a, e, i, o, u) in a string (case-insensitive).

**Solution:**
```assembly
# Function: count_vowels
# Input: $a0 = address of string
# Output: $v0 = number of vowels

count_vowels:
        li   $v0, 0            # count = 0
        move $t0, $a0          # current position
        
loop:   lb   $t1, 0($t0)       # Load character
        beq  $t1, $zero, done  # If null, done
        
        # Convert to lowercase if uppercase
        blt  $t1, 65, check    # If < 'A', skip
        bgt  $t1, 90, check    # If > 'Z', skip
        addi $t1, $t1, 32      # Convert to lowercase
        
check:  # Check if vowel
        li   $t2, 'a'
        beq  $t1, $t2, is_vowel
        li   $t2, 'e'
        beq  $t1, $t2, is_vowel
        li   $t2, 'i'
        beq  $t1, $t2, is_vowel
        li   $t2, 'o'
        beq  $t1, $t2, is_vowel
        li   $t2, 'u'
        beq  $t1, $t2, is_vowel
        j    next
        
is_vowel:
        addi $v0, $v0, 1       # count++
        
next:   addi $t0, $t0, 1       # Next character
        j    loop
        
done:   jr   $ra

# Test program
.data
prompt:     .asciiz "Enter string: "
result:     .asciiz "Vowel count: "
buffer:     .space 100

.text
main:
        # Read string
        li   $v0, 4
        la   $a0, prompt
        syscall
        
        li   $v0, 8
        la   $a0, buffer
        li   $a1, 100
        syscall
        
        # Count vowels
        la   $a0, buffer
        jal  count_vowels
        
        # Display result
        move $s0, $v0
        li   $v0, 4
        la   $a0, result
        syscall
        
        li   $v0, 1
        move $a0, $s0
        syscall
        
        li   $v0, 10
        syscall
```

---

### Problem 5.5: Palindrome Check

**Question:**
Check if a string is a palindrome.

**Solution:**
```assembly
# Function: is_palindrome
# Input: $a0 = address of string
# Output: $v0 = 1 if palindrome, 0 otherwise

is_palindrome:
        # Save registers
        addi $sp, $sp, -4
        sw   $ra, 0($sp)
        
        # Find length
        move $t8, $a0          # Save string address
        jal  strlen            # Returns length in $v0
        move $t0, $v0          # $t0 = length
        
        # Setup pointers
        move $t1, $t8          # Left pointer (start)
        add  $t2, $t8, $t0     # Right pointer (end)
        addi $t2, $t2, -1      # Back one from null
        
        # Empty string is palindrome
        beq  $t0, $zero, true
        
loop:   bge  $t1, $t2, true    # If pointers meet, palindrome
        
        lb   $t3, 0($t1)       # Left character
        lb   $t4, 0($t2)       # Right character
        
        bne  $t3, $t4, false   # If different, not palindrome
        
        addi $t1, $t1, 1       # Move left pointer right
        addi $t2, $t2, -1      # Move right pointer left
        j    loop
        
true:   li   $v0, 1
        j    exit
        
false:  li   $v0, 0
        
exit:   lw   $ra, 0($sp)
        addi $sp, $sp, 4
        jr   $ra

# strlen function (from Problem 5.2)
strlen:
        li   $v0, 0
        move $t0, $a0
strlen_loop:
        lb   $t1, 0($t0)
        beq  $t1, $zero, strlen_done
        addi $v0, $v0, 1
        addi $t0, $t0, 1
        j    strlen_loop
strlen_done:
        jr   $ra

# Test program
.data
prompt:     .asciiz "Enter string: "
yes_msg:    .asciiz "Is palindrome!\n"
no_msg:     .asciiz "Not palindrome.\n"
buffer:     .space 100

.text
main:
        # Read string
        li   $v0, 4
        la   $a0, prompt
        syscall
        
        li   $v0, 8
        la   $a0, buffer
        li   $a1, 100
        syscall
        
        # Remove newline if present
        la   $t0, buffer
remove_nl:
        lb   $t1, 0($t0)
        beq  $t1, $zero, check_palin
        beq  $t1, 10, found_nl
        addi $t0, $t0, 1
        j    remove_nl
found_nl:
        sb   $zero, 0($t0)
        
check_palin:
        # Check palindrome
        la   $a0, buffer
        jal  is_palindrome
        
        # Display result
        beq  $v0, $zero, not_pal
        li   $v0, 4
        la   $a0, yes_msg
        syscall
        j    exit
        
not_pal:
        li   $v0, 4
        la   $a0, no_msg
        syscall
        
exit:   li   $v0, 10
        syscall
```

---

## COMPREHENSIVE PROBLEMS

### Problem 6.1: Bubble Sort

**Question:**
Implement bubble sort for an array of integers.

**Solution:**
```assembly
.data
array:      .word 64, 34, 25, 12, 22, 11, 90
size:       .word 7
msg_before: .asciiz "Before sorting: "
msg_after:  .asciiz "\nAfter sorting: "
space:      .asciiz " "
newline:    .asciiz "\n"

.text
.globl main

main:
        # Print before
        li   $v0, 4
        la   $a0, msg_before
        syscall
        jal  print_array
        
        # Sort
        jal  bubble_sort
        
        # Print after
        li   $v0, 4
        la   $a0, msg_after
        syscall
        jal  print_array
        
        # Exit
        li   $v0, 10
        syscall

# Function: bubble_sort
bubble_sort:
        la   $t0, array        # Base address
        lw   $t1, size         # n
        
outer:  li   $t2, 0            # i = 0
        addi $t3, $t1, -1      # n - 1
        bge  $t2, $t3, done    # if i >= n-1, done
        
inner:  li   $t4, 0            # j = 0
        sub  $t5, $t3, $t2     # n - 1 - i
        bge  $t4, $t5, next_i  # if j >= n-1-i, next i
        
        # Compare array[j] and array[j+1]
        sll  $t6, $t4, 2       # j × 4
        add  $t6, $t6, $t0     # address of array[j]
        lw   $t7, 0($t6)       # array[j]
        lw   $t8, 4($t6)       # array[j+1]
        
        ble  $t7, $t8, no_swap # if array[j] <= array[j+1], no swap
        
        # Swap
        sw   $t8, 0($t6)       # array[j] = array[j+1]
        sw   $t7, 4($t6)       # array[j+1] = array[j]
        
no_swap:
        addi $t4, $t4, 1       # j++
        j    inner
        
next_i: addi $t2, $t2, 1       # i++
        j    outer
        
done:   jr   $ra

# Function: print_array
print_array:
        la   $t0, array
        lw   $t1, size
        li   $t2, 0
        
print_loop:
        bge  $t2, $t1, print_done
        
        lw   $a0, 0($t0)
        li   $v0, 1
        syscall
        
        li   $v0, 4
        la   $a0, space
        syscall
        
        addi $t0, $t0, 4
        addi $t2, $t2, 1
        j    print_loop
        
print_done:
        li   $v0, 4
        la   $a0, newline
        syscall
        jr   $ra
```

---

### Problem 6.2: Binary Search

**Question:**
Implement binary search on a sorted array.

**Solution:**
```assembly
# Function: binary_search
# Inputs: $a0 = array address, $a1 = size, $a2 = target
# Output: $v0 = index if found, -1 if not found

binary_search:
        li   $t0, 0            # left = 0
        addi $t1, $a1, -1      # right = size - 1
        
search_loop:
        bgt  $t0, $t1, not_found  # if left > right, not found
        
        # Calculate mid = (left + right) / 2
        add  $t2, $t0, $t1     # left + right
        srl  $t2, $t2, 1       # divide by 2 (shift right)
        
        # Get array[mid]
        sll  $t3, $t2, 2       # mid × 4
        add  $t3, $t3, $a0     # address of array[mid]
        lw   $t4, 0($t3)       # array[mid]
        
        # Compare with target
        beq  $t4, $a2, found   # if array[mid] == target, found
        blt  $t4, $a2, search_right  # if array[mid] < target, search right
        
        # Search left half
        addi $t1, $t2, -1      # right = mid - 1
        j    search_loop
        
search_right:
        addi $t0, $t2, 1       # left = mid + 1
        j    search_loop
        
found:  move $v0, $t2          # return index
        jr   $ra
        
not_found:
        li   $v0, -1           # return -1
        jr   $ra

# Test program
.data
sorted_array: .word 2, 5, 8, 12, 16, 23, 38, 45, 56, 67, 78
size:         .word 11
search_msg:   .asciiz "Searching for: "
found_msg:    .asciiz "\nFound at index: "
notfound_msg: .asciiz "\nNot found"
newline:      .asciiz "\n"

.text
main:
        # Search for 23
        la   $a0, sorted_array
        lw   $a1, size
        li   $a2, 23
        
        # Print what we're searching for
        li   $v0, 4
        la   $a0, search_msg
        syscall
        li   $v0, 1
        li   $a0, 23
        syscall
        
        # Do search
        la   $a0, sorted_array
        lw   $a1, size
        li   $a2, 23
        jal  binary_search
        
        # Print result
        blt  $v0, $zero, not_found
        li   $v0, 4
        la   $a0, found_msg
        syscall
        move $a0, $v0
        li   $v0, 1
        syscall
        j    exit
        
not_found:
        li   $v0, 4
        la   $a0, notfound_msg
        syscall
        
exit:   li   $v0, 10
        syscall
```

---

### Problem 6.3: Calculator Program

**Question:**
Create a simple calculator that performs +, -, *, / operations.

**Solution:**
```assembly
.data
prompt1:    .asciiz "Enter first number: "
prompt2:    .asciiz "Enter second number: "
prompt_op:  .asciiz "Enter operation (+, -, *, /): "
result_msg: .asciiz "Result: "
error_msg:  .asciiz "Invalid operation or division by zero!\n"
newline:    .asciiz "\n"
op_buffer:  .space 2

.text
.globl main

main:
        # Read first number
        li   $v0, 4
        la   $a0, prompt1
        syscall
        li   $v0, 5
        syscall
        move $s0, $v0          # $s0 = first number
        
        # Read second number
        li   $v0, 4
        la   $a0, prompt2
        syscall
        li   $v0, 5
        syscall
        move $s1, $v0          # $s1 = second number
        
        # Read operation
        li   $v0, 4
        la   $a0, prompt_op
        syscall
        li   $v0, 8
        la   $a0, op_buffer
        li   $a1, 2
        syscall
        
        # Load operation character
        lb   $t0, op_buffer
        
        # Check operation
        li   $t1, '+'
        beq  $t0, $t1, do_add
        li   $t1, '-'
        beq  $t0, $t1, do_sub
        li   $t1, '*'
        beq  $t0, $t1, do_mul
        li   $t1, '/'
        beq  $t0, $t1, do_div
        
        # Invalid operation
        j    error
        
do_add: add  $s2, $s0, $s1
        j    display
        
do_sub: sub  $s2, $s0, $s1
        j    display
        
do_mul: mul  $s2, $s0, $s1
        j    display
        
do_div: # Check for division by zero
        beq  $s1, $zero, error
        div  $s0, $s1
        mflo $s2               # Get quotient
        j    display
        
display:
        li   $v0, 4
        la   $a0, result_msg
        syscall
        li   $v0, 1
        move $a0, $s2
        syscall
        li   $v0, 4
        la   $a0, newline
        syscall
        j    exit
        
error:  li   $v0, 4
        la   $a0, error_msg
        syscall
        
exit:   li   $v0, 10
        syscall
```

---

### Problem 6.4: Matrix Addition

**Question:**
Add two 3×3 matrices.

**Solution:**
```assembly
.data
matrixA:    .word 1, 2, 3, 4, 5, 6, 7, 8, 9
matrixB:    .word 9, 8, 7, 6, 5, 4, 3, 2, 1
result:     .space 36          # 9 integers × 4 bytes
msg_result: .asciiz "Result matrix:\n"
space:      .asciiz " "
newline:    .asciiz "\n"

.text
.globl main

main:
        # Add matrices
        la   $a0, matrixA
        la   $a1, matrixB
        la   $a2, result
        jal  matrix_add_3x3
        
        # Print result
        li   $v0, 4
        la   $a0, msg_result
        syscall
        
        la   $a0, result
        jal  print_matrix_3x3
        
        # Exit
        li   $v0, 10
        syscall

# Function: matrix_add_3x3
# Inputs: $a0 = matrixA, $a1 = matrixB, $a2 = result
matrix_add_3x3:
        li   $t0, 0            # index = 0
        li   $t1, 9            # total elements
        
add_loop:
        bge  $t0, $t1, add_done
        
        # Calculate byte offset
        sll  $t2, $t0, 2       # offset = index × 4
        
        # Load elements
        add  $t3, $a0, $t2
        lw   $t4, 0($t3)       # matrixA[i]
        
        add  $t3, $a1, $t2
        lw   $t5, 0($t3)       # matrixB[i]
        
        # Add
        add  $t6, $t4, $t5     # sum
        
        # Store result
        add  $t3, $a2, $t2
        sw   $t6, 0($t3)       # result[i] = sum
        
        addi $t0, $t0, 1       # index++
        j    add_loop
        
add_done:
        jr   $ra

# Function: print_matrix_3x3
# Input: $a0 = matrix address
print_matrix_3x3:
        move $t0, $a0          # Base address
        li   $t1, 0            # row
        li   $t2, 3            # rows/cols
        
print_row:
        bge  $t1, $t2, print_done
        
        li   $t3, 0            # col
        
print_col:
        bge  $t3, $t2, next_row
        
        # Calculate index = row * 3 + col
        mul  $t4, $t1, $t2     # row × 3
        add  $t4, $t4, $t3     # + col
        sll  $t4, $t4, 2       # × 4 bytes
        add  $t4, $t4, $t0     # + base address
        lw   $a0, 0($t4)       # Load element
        
        li   $v0, 1
        syscall
        
        li   $v0, 4
        la   $a0, space
        syscall
        
        addi $t3, $t3, 1       # col++
        j    print_col
        
next_row:
        li   $v0, 4
        la   $a0, newline
        syscall
        
        addi $t1, $t1, 1       # row++
        j    print_row
        
print_done:
        jr   $ra
```

---

## ANSWER KEY SUMMARY

### Chapter 1
1.1: Binary conversions and hex
1.2: Two's complement operations
1.3: Performance calculations

### Chapter 2
2.1: Basic arithmetic translation
2.2: Array access patterns
2.3: Bit manipulation techniques
2.4: Register preservation

### Chapter 3
3.1: If-else implementation
3.2: Nested conditionals
3.3: Loop with accumulation
3.4: Array traversal
3.5: Iterative factorial

### Chapter 4
4.1: Simple function (abs)
4.2: Multiple parameters (average)
4.3: Recursive factorial
4.4: GCD algorithm
4.5: Iterative Fibonacci

### Chapter 5
5.1: Integer input/output
5.2: String length calculation
5.3: String copy operation
5.4: Character counting (vowels)
5.5: Palindrome verification

### Chapter 6
6.1: Bubble sort implementation
6.2: Binary search algorithm
6.3: Interactive calculator
6.4: Matrix operations

---

*Use these problems to practice and prepare for examinations. Work through them systematically and verify your solutions by testing in MARS.*

**END OF PRACTICE PROBLEMS**
