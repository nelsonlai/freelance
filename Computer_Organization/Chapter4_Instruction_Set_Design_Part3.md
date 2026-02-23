# CHAPTER 4: INSTRUCTION SET DESIGN (PART 3)
## Introduction to Computer Organization (CCIT4026)
### HKU SPACE Community College

---

## TABLE OF CONTENTS

1. [Function Calls and Stack](#41-function-calls-and-stack)
2. [Simple Function Example](#42-simple-function-example)
3. [Function with Local Variables](#43-function-with-local-variables)
4. [Recursive Functions](#44-recursive-functions)
5. [Nested Function Calls](#45-nested-function-calls)
6. [Arrays and Pointers](#46-arrays-and-pointers)
7. [Structures in MIPS](#47-structures-in-mips)
8. [Practice Problems](#48-practice-problems---chapter-4)

---

## 4.1 Function Calls and Stack

### Function Call Convention

**The MIPS calling convention** defines how functions communicate:

**Steps in Function Call:**
1. **Caller** places arguments in `$a0-$a3`
2. **Caller** executes `jal function`
3. **Function** saves registers if needed (prologue)
4. **Function** executes its body
5. **Function** places results in `$v0-$v1`
6. **Function** restores saved registers (epilogue)
7. **Function** returns using `jr $ra`

### The Stack

**The stack** is a region of memory used for:
- Saving registers
- Storing local variables
- Passing extra arguments (beyond 4)
- Saving return addresses

**Key Characteristics:**
- Grows **downward** (toward lower addresses)
- `$sp` (stack pointer) points to top of stack
- Must be kept **word-aligned** (multiple of 4)

### Stack Operations

#### Push (Save) Register to Stack

```assembly
# Push register to stack
addi $sp, $sp, -4      # Allocate 4 bytes (move sp down)
sw   $t0, 0($sp)       # Save $t0 at top of stack
```

#### Pop (Restore) Register from Stack

```assembly
# Pop register from stack
lw   $t0, 0($sp)       # Restore $t0 from stack
addi $sp, $sp, 4       # Deallocate 4 bytes (move sp up)
```

### Stack Growth Visualization

```
High Address (0x7FFFFFFC)
    │
    ├────────────┐
    │   old data │
    ├────────────┤ ← $sp (before push)
    │   new data │ ← Newly pushed data
    ├────────────┤ ← $sp (after push)
    │            │
    ↓ Stack grows downward
Low Address
```

### Register Preservation Rules

**Caller-Saved (Temporary) Registers:**
- `$t0-$t9`: Caller must save if values needed after call
- `$a0-$a3`: May be modified by callee
- `$v0-$v1`: Overwritten with return values

**Callee-Saved Registers:**
- `$s0-$s7`: Callee must save and restore
- `$ra`: Must be saved if function calls other functions
- `$sp`: Must be restored before return

**Always Preserved:**
- `$sp`: Stack pointer
- `$gp`: Global pointer

### Stack Frame

A **stack frame** (activation record) contains:
- Saved registers
- Local variables
- Return address
- Arguments (if > 4)

```
Stack Frame Layout:

    ├──────────────────┤
    │  Return address  │ $sp + 12
    ├──────────────────┤
    │  Saved $s0       │ $sp + 8
    ├──────────────────┤
    │  Saved $s1       │ $sp + 4
    ├──────────────────┤
    │  Local var       │ $sp + 0  ← $sp
    ├──────────────────┤
```

---

## 4.2 Simple Function Example

### No Local Variables, No Calls

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
# No prologue/epilogue needed (doesn't modify $s registers)
add_func:
        add  $v0, $a0, $a1     # $v0 = a + b
        jr   $ra               # return

# Main program
main:
        li   $a0, 3            # First argument
        li   $a1, 5            # Second argument
        jal  add_func          # Call function, $ra = return address
        move $s0, $v0          # x = result (8)
```

### Function with Multiple Arguments

**C Code:**
```c
int calc(int a, int b, int c, int d) {
    return (a + b) * (c + d);
}
```

**MIPS Assembly:**
```assembly
calc:
        add  $t0, $a0, $a1     # $t0 = a + b
        add  $t1, $a2, $a3     # $t1 = c + d
        mul  $v0, $t0, $t1     # $v0 = (a+b) * (c+d)
        jr   $ra
```

### Calling the Function

```assembly
        li   $a0, 2            # a = 2
        li   $a1, 3            # b = 3
        li   $a2, 4            # c = 4
        li   $a3, 5            # d = 5
        jal  calc              # Call function
        # $v0 = (2+3) * (4+5) = 45
```

---

## 4.3 Function with Local Variables

### Using Saved Registers

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
        addi $sp, $sp, -8      # Allocate 8 bytes
        sw   $s0, 4($sp)       # Save $s0
        sw   $ra, 0($sp)       # Save return address
        
        # Function body
        add  $s0, $a0, $a1     # temp = a + b (using $s0)
        add  $v0, $s0, $a2     # result = temp + c
        
        # Epilogue: Restore registers
        lw   $ra, 0($sp)       # Restore $ra
        lw   $s0, 4($sp)       # Restore $s0
        addi $sp, $sp, 8       # Deallocate stack
        
        jr   $ra               # return
```

**Why save $ra?**
- Even though this function doesn't call others
- Good practice for consistency
- Easy to add calls later

### Function with More Than 4 Arguments

**C Code:**
```c
int sum5(int a, int b, int c, int d, int e) {
    return a + b + c + d + e;
}
```

**MIPS Assembly:**
```assembly
# Caller must push 5th argument on stack before calling

main:
        li   $a0, 1            # a = 1
        li   $a1, 2            # b = 2
        li   $a2, 3            # c = 3
        li   $a3, 4            # d = 4
        
        # Push 5th argument
        li   $t0, 5            # e = 5
        addi $sp, $sp, -4      # Allocate space
        sw   $t0, 0($sp)       # Push e
        
        jal  sum5              # Call function
        
        addi $sp, $sp, 4       # Clean up stack
        # $v0 = 15

sum5:
        # Load 5th argument from stack
        lw   $t0, 0($sp)       # e from stack
        
        add  $v0, $a0, $a1     # sum = a + b
        add  $v0, $v0, $a2     # sum += c
        add  $v0, $v0, $a3     # sum += d
        add  $v0, $v0, $t0     # sum += e
        
        jr   $ra
```

---

## 4.4 Recursive Functions

### Understanding Recursion in Assembly

**Key Points:**
- Each recursive call creates new stack frame
- Must save $ra (return address)
- Must save arguments if needed after recursive call
- Base case terminates recursion

### Factorial Example

**C Code:**
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
        addi $sp, $sp, -8      # Allocate stack space
        sw   $ra, 4($sp)       # Save return address
        sw   $a0, 0($sp)       # Save argument n
        
        # Base case: if (n <= 1) return 1
        slti $t0, $a0, 2       # $t0 = (n < 2)
        beq  $t0, $zero, recur # if n >= 2, recurse
        
        # Base case: return 1
        li   $v0, 1            # return value = 1
        addi $sp, $sp, 8       # Deallocate stack
        jr   $ra               # return
        
recur:  # Recursive case
        addi $a0, $a0, -1      # n - 1
        jal  factorial         # factorial(n - 1)
        
        # After return: $v0 = factorial(n-1)
        lw   $a0, 0($sp)       # Restore n
        lw   $ra, 4($sp)       # Restore return address
        addi $sp, $sp, 8       # Deallocate stack
        
        mul  $v0, $a0, $v0     # n * factorial(n-1)
        jr   $ra               # return
```

**Stack Trace for factorial(3):**
```
Call factorial(3):
    Stack: [3, ra1]
    Call factorial(2):
        Stack: [2, ra2] [3, ra1]
        Call factorial(1):
            Stack: [1, ra3] [2, ra2] [3, ra1]
            Return 1
        Return 2 * 1 = 2
    Return 3 * 2 = 6
```

### Fibonacci Sequence (Recursive)

**C Code:**
```c
int fib(int n) {
    if (n <= 1)
        return n;
    return fib(n-1) + fib(n-2);
}
```

**MIPS Assembly:**
```assembly
fibonacci:
        # Base case: if (n <= 1) return n
        slti $t0, $a0, 2       # n < 2?
        beq  $t0, $zero, recur
        move $v0, $a0          # return n (0 or 1)
        jr   $ra
        
recur:  # Recursive case
        # Prologue
        addi $sp, $sp, -12     # Allocate stack
        sw   $ra, 8($sp)       # Save return address
        sw   $s0, 4($sp)       # Save n
        sw   $s1, 0($sp)       # Save fib(n-1) result
        
        move $s0, $a0          # Save n
        
        # Call fib(n-1)
        addi $a0, $s0, -1      # n - 1
        jal  fibonacci
        move $s1, $v0          # Save fib(n-1)
        
        # Call fib(n-2)
        addi $a0, $s0, -2      # n - 2
        jal  fibonacci
        
        # Combine results
        add  $v0, $s1, $v0     # fib(n-1) + fib(n-2)
        
        # Epilogue
        lw   $s1, 0($sp)       # Restore $s1
        lw   $s0, 4($sp)       # Restore $s0
        lw   $ra, 8($sp)       # Restore $ra
        addi $sp, $sp, 12      # Deallocate
        jr   $ra               # return
```

### GCD (Greatest Common Divisor) - Recursive

**C Code:**
```c
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
```

**MIPS Assembly:**
```assembly
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
        
        # Set up arguments: a=b, b=a%b
        move $a0, $a1          # First arg = b
        move $a1, $t0          # Second arg = a % b
        
        jal  gcd               # Recursive call
        
        # Result already in $v0
        lw   $ra, 0($sp)
        addi $sp, $sp, 4
        jr   $ra
```

---

## 4.5 Nested Function Calls

### Multiple Function Calls

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
        sw   $s1, 0($sp)       # Save $s1 (for temp result)
        
        move $s0, $a0          # Save x
        
        # First call: g(x + 1)
        addi $a0, $s0, 1       # argument = x + 1
        jal  g                 # call g
        move $s1, $v0          # save result in $s1
        
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

### Leaf vs. Non-Leaf Functions

**Leaf Function:**
- Does NOT call other functions
- May not need to save $ra
- Simpler prologue/epilogue

**Non-Leaf Function:**
- Calls other functions
- MUST save $ra
- More complex stack management

---

## 4.6 Arrays and Pointers

### Array Declaration and Access

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
A:      .space 40              # 10 integers × 4 bytes = 40 bytes

.text
        la   $t0, A            # $t0 = base address of A
        
        # A[0] = 5
        li   $t1, 5
        sw   $t1, 0($t0)       # Offset = 0 × 4 = 0
        
        # A[3] = 12
        li   $t1, 12
        sw   $t1, 12($t0)      # Offset = 3 × 4 = 12
        
        # x = A[3]
        lw   $s0, 12($t0)      # $s0 = A[3] = 12
```

### Array Traversal

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
        
        # Calculate value: i * 2
        sll  $t2, $t0, 1       # $t2 = i × 2
        
        # Calculate address: base + (i × 4)
        sll  $t3, $t0, 2       # $t3 = i × 4 (byte offset)
        add  $t4, $s1, $t3     # $t4 = address of A[i]
        
        # Store value
        sw   $t2, 0($t4)       # A[i] = i × 2
        
        addi $t0, $t0, 1       # i++
        j    loop
done:
```

### Pointer Arithmetic

**C Code:**
```c
int *p = A;
*p = 10;        // A[0] = 10
p++;            // p points to A[1]
*p = 20;        // A[1] = 20
```

**MIPS Assembly:**
```assembly
        la   $t0, A            # p = &A (base address)
        
        li   $t1, 10
        sw   $t1, 0($t0)       # *p = 10
        
        addi $t0, $t0, 4       # p++ (move to next int, +4 bytes)
        
        li   $t1, 20
        sw   $t1, 0($t0)       # *p = 20
```

### Passing Arrays to Functions

**C Code:**
```c
int sum_array(int *arr, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}
```

**MIPS Assembly:**
```assembly
# Function: sum_array
# Arguments: $a0 = array address, $a1 = size
# Return: $v0 = sum

sum_array:
        li   $v0, 0            # sum = 0
        li   $t0, 0            # i = 0
        
loop:   bge  $t0, $a1, done    # if i >= size, done
        
        sll  $t1, $t0, 2       # offset = i × 4
        add  $t2, $a0, $t1     # address = arr + offset
        lw   $t3, 0($t2)       # load arr[i]
        
        add  $v0, $v0, $t3     # sum += arr[i]
        addi $t0, $t0, 1       # i++
        j    loop
        
done:   jr   $ra

# Calling the function
main:
        la   $a0, myArray      # Pass array address
        li   $a1, 10           # Pass size
        jal  sum_array
        # $v0 contains sum
```

### Multi-Dimensional Arrays

**C Code:**
```c
int matrix[3][4];  // 3 rows, 4 columns
matrix[1][2] = 42;
```

**Layout in Memory:**
```
Row 0: [0][1][2][3]
Row 1: [0][1][2][3]
Row 2: [0][1][2][3]

Address calculation:
address = base + (row × numCols + col) × 4
```

**MIPS Assembly:**
```assembly
.data
matrix: .space 48              # 3 × 4 × 4 = 48 bytes

.text
        la   $t0, matrix       # Base address
        
        # matrix[1][2] = 42
        # offset = (1 × 4 + 2) × 4 = 6 × 4 = 24
        li   $t1, 42
        sw   $t1, 24($t0)
        
        # General formula:
        # row = 1, col = 2, numCols = 4
        li   $t2, 1            # row
        li   $t3, 2            # col
        li   $t4, 4            # numCols
        
        mul  $t5, $t2, $t4     # row × numCols
        add  $t5, $t5, $t3     # + col
        sll  $t5, $t5, 2       # × 4
        add  $t6, $t0, $t5     # base + offset
        
        li   $t1, 42
        sw   $t1, 0($t6)       # Store value
```

---

## 4.7 Structures in MIPS

### Simple Structure

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
p:      .space 8               # Structure size = 8 bytes (2 ints)

.text
        la   $t0, p            # $t0 = address of structure
        
        li   $t1, 10
        sw   $t1, 0($t0)       # p.x = 10 (offset 0)
        
        li   $t1, 20
        sw   $t1, 4($t0)       # p.y = 20 (offset 4)
```

### Structure with Mixed Types

**C Code:**
```c
struct Person {
    int age;        // offset 0 (4 bytes)
    char initial;   // offset 4 (1 byte)
    // padding 3 bytes
    int id;         // offset 8 (4 bytes)
};
```

**MIPS Assembly:**
```assembly
.data
person: .space 12              # Total: 12 bytes (with padding)

.text
        la   $t0, person
        
        # person.age = 25
        li   $t1, 25
        sw   $t1, 0($t0)       # Store int at offset 0
        
        # person.initial = 'J' (74 in ASCII)
        li   $t1, 74
        sb   $t1, 4($t0)       # Store byte at offset 4
        
        # person.id = 12345
        li   $t1, 12345
        sw   $t1, 8($t0)       # Store int at offset 8
```

### Array of Structures

**C Code:**
```c
struct Point points[3];
points[1].x = 5;
points[1].y = 10;
```

**MIPS Assembly:**
```assembly
.data
points: .space 24              # 3 structures × 8 bytes

.text
        la   $t0, points       # Base address
        
        # Access points[1]: base + (1 × 8)
        addi $t0, $t0, 8       # Address of points[1]
        
        # points[1].x = 5
        li   $t1, 5
        sw   $t1, 0($t0)       # x at offset 0
        
        # points[1].y = 10
        li   $t1, 10
        sw   $t1, 4($t0)       # y at offset 4
```

---

## 4.8 Practice Problems - Chapter 4

### Problem 1: Maximum of Two Numbers

**Task:** Write a function `max(a, b)` that returns the larger value.

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

### Problem 2: Power Function (Recursive)

**C Code:**
```c
int power(int base, int exp) {
    if (exp == 0) return 1;
    return base * power(base, exp - 1);
}
```

**Solution:**
```assembly
power:
        # Prologue
        addi $sp, $sp, -8
        sw   $ra, 4($sp)
        sw   $a0, 0($sp)       # Save base
        
        # Base case: exp == 0
        bne  $a1, $zero, recur
        li   $v0, 1            # return 1
        addi $sp, $sp, 8
        jr   $ra
        
recur:  # Recursive case
        addi $a1, $a1, -1      # exp - 1
        jal  power             # power(base, exp-1)
        
        lw   $a0, 0($sp)       # Restore base
        lw   $ra, 4($sp)
        addi $sp, $sp, 8
        
        mul  $v0, $a0, $v0     # base * power(base, exp-1)
        jr   $ra
```

### Problem 3: Array Reverse

**C Code:**
```c
void reverse(int *arr, int size) {
    for (int i = 0; i < size/2; i++) {
        int temp = arr[i];
        arr[i] = arr[size-1-i];
        arr[size-1-i] = temp;
    }
}
```

**Solution:**
```assembly
reverse:
        # $a0 = array address, $a1 = size
        
        li   $t0, 0            # i = 0
        srl  $t1, $a1, 1       # limit = size / 2
        
loop:   bge  $t0, $t1, done
        
        # Calculate addresses
        sll  $t2, $t0, 2       # i × 4
        add  $t3, $a0, $t2     # address of arr[i]
        
        sub  $t4, $a1, $t0     # size - i
        addi $t4, $t4, -1      # size - i - 1
        sll  $t4, $t4, 2       # × 4
        add  $t5, $a0, $t4     # address of arr[size-1-i]
        
        # Swap
        lw   $t6, 0($t3)       # temp = arr[i]
        lw   $t7, 0($t5)       # arr[size-1-i]
        sw   $t7, 0($t3)       # arr[i] = arr[size-1-i]
        sw   $t6, 0($t5)       # arr[size-1-i] = temp
        
        addi $t0, $t0, 1       # i++
        j    loop
done:   jr   $ra
```

### Problem 4: Iterative Fibonacci

**C Code:**
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
fib_iterative:
        # Base case
        slti $t0, $a0, 2       # n < 2?
        beq  $t0, $zero, loop_init
        move $v0, $a0          # return n
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

## KEY TAKEAWAYS

1. **MIPS calling convention** uses `$a0-$a3` for arguments, `$v0-$v1` for returns

2. **Stack grows downward**, always keep it word-aligned

3. **Must save:**
   - `$ra` if function calls others
   - `$s0-$s7` if function modifies them

4. **Recursion** requires careful stack management to save state

5. **Arrays** accessed with base address + offset calculation

6. **Structures** laid out in memory with field offsets

---

## NEXT CHAPTER

**[Chapter 5: Instruction Set Design (Part 4)](Chapter5_Instruction_Set_Design_Part4.md)**
- System Calls in MARS
- Input/Output Operations
- String Processing
- Floating-Point Operations
- Advanced Topics

---

*This material is part of CCIT4026: Introduction to Computer Organization*  
*HKU SPACE Community College*  
*Chapter 4 of 5*
