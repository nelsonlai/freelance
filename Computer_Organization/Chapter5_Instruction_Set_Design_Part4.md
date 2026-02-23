# CHAPTER 5: INSTRUCTION SET DESIGN (PART 4)
## Introduction to Computer Organization (CCIT4026)
### HKU SPACE Community College

---

## TABLE OF CONTENTS

1. [System Calls in MARS](#51-system-calls-in-mars)
2. [Input/Output Examples](#52-inputoutput-examples)
3. [Complete Program Example](#53-complete-program-example)
4. [String Processing](#54-string-processing)
5. [Floating-Point Operations](#55-floating-point-operations)
6. [Memory-Mapped I/O](#56-memory-mapped-io)
7. [Advanced Topics](#57-advanced-topics)
8. [Debugging Techniques](#58-debugging-techniques)
9. [Practice Problems](#59-practice-problems---chapter-5)

---

## 5.1 System Calls in MARS

**System calls (syscalls)** provide an interface to operating system services:
- Input/Output operations
- Memory allocation
- Program termination
- File operations

### System Call Mechanism

```assembly
li   $v0, service_code     # Load service code into $v0
# Set up arguments in $a0, $a1, etc.
syscall                    # Execute system call
# Result (if any) returned in $v0 or $f0
```

### Common System Call Codes

| Service | Code | Arguments | Returns | Description |
|---------|------|-----------|---------|-------------|
| print_int | 1 | `$a0` = integer | - | Print 32-bit integer |
| print_float | 2 | `$f12` = float | - | Print float |
| print_double | 3 | `$f12` = double | - | Print double |
| print_string | 4 | `$a0` = address | - | Print null-terminated string |
| read_int | 5 | - | `$v0` = integer | Read integer from user |
| read_float | 6 | - | `$f0` = float | Read float from user |
| read_double | 7 | - | `$f0` = double | Read double from user |
| read_string | 8 | `$a0` = buffer, `$a1` = max length | - | Read string from user |
| sbrk (allocate heap) | 9 | `$a0` = bytes | `$v0` = address | Allocate heap memory |
| exit | 10 | - | - | Terminate program |
| print_character | 11 | `$a0` = char | - | Print ASCII character |
| read_character | 12 | - | `$v0` = char | Read single character |
| open | 13 | `$a0` = filename, `$a1` = flags | `$v0` = fd | Open file |
| read | 14 | `$a0` = fd, `$a1` = buffer, `$a2` = length | `$v0` = bytes read | Read from file |
| write | 15 | `$a0` = fd, `$a1` = buffer, `$a2` = length | `$v0` = bytes written | Write to file |
| close | 16 | `$a0` = fd | - | Close file |
| exit2 | 17 | `$a0` = return code | - | Exit with return code |

---

## 5.2 Input/Output Examples

### Print Integer

```assembly
# Print the value 42
li   $v0, 1                # Service 1: print_int
li   $a0, 42               # Integer to print
syscall                    # Execute system call
# Output: 42
```

### Read Integer

```assembly
# Read an integer from user
li   $v0, 5                # Service 5: read_int
syscall                    # Wait for user input
move $t0, $v0              # Store result in $t0
```

**Interactive Example:**
```assembly
.data
prompt: .asciiz "Enter a number: "

.text
        # Print prompt
        li   $v0, 4
        la   $a0, prompt
        syscall
        
        # Read number
        li   $v0, 5
        syscall
        # User enters 123
        # $v0 now contains 123
```

### Print String

```assembly
.data
msg:    .asciiz "Hello, World!\n"

.text
        li   $v0, 4            # Service 4: print_string
        la   $a0, msg          # Address of string
        syscall                # Print string
# Output: Hello, World!
```

**Multiple Strings:**
```assembly
.data
str1:   .asciiz "First line\n"
str2:   .asciiz "Second line\n"

.text
        li   $v0, 4
        la   $a0, str1
        syscall
        
        li   $v0, 4
        la   $a0, str2
        syscall
# Output:
# First line
# Second line
```

### Read String

```assembly
.data
buffer: .space 100         # Allocate 100 bytes for string

.text
        li   $v0, 8            # Service 8: read_string
        la   $a0, buffer       # Buffer address
        li   $a1, 100          # Maximum length (including null)
        syscall                # Read string from user
        # String stored in buffer (null-terminated)
```

**Important Notes:**
- Reads at most `length - 1` characters
- Automatically null-terminates the string
- Includes newline character if user presses Enter

### Print Character

```assembly
# Print newline character
li   $v0, 11               # Service 11: print_character
li   $a0, 10               # ASCII code for '\n'
syscall

# Print 'A'
li   $v0, 11
li   $a0, 65               # ASCII code for 'A'
syscall
```

### Read Character

```assembly
li   $v0, 12               # Service 12: read_character
syscall                    # Read one character
move $t0, $v0              # Store in $t0
# $t0 now contains ASCII value of character
```

---

## 5.3 Complete Program Example

### Lab 2: User Input and Output

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

### Calculator Program

```assembly
.data
prompt1:    .asciiz "Enter first number: "
prompt2:    .asciiz "Enter second number: "
result_msg: .asciiz "Sum: "
newline:    .asciiz "\n"

.text
main:
        # Read first number
        li   $v0, 4
        la   $a0, prompt1
        syscall
        li   $v0, 5
        syscall
        move $t0, $v0          # $t0 = first number
        
        # Read second number
        li   $v0, 4
        la   $a0, prompt2
        syscall
        li   $v0, 5
        syscall
        move $t1, $v0          # $t1 = second number
        
        # Calculate sum
        add  $t2, $t0, $t1     # $t2 = sum
        
        # Print result
        li   $v0, 4
        la   $a0, result_msg
        syscall
        li   $v0, 1
        move $a0, $t2
        syscall
        
        # Print newline
        li   $v0, 4
        la   $a0, newline
        syscall
        
        # Exit
        li   $v0, 10
        syscall
```

---

## 5.4 String Processing

### String Length

**Function:** Calculate length of null-terminated string

```assembly
# strlen: Calculate string length
# Input: $a0 = address of string
# Output: $v0 = length (excluding null)

strlen:
        move $v0, $zero            # length = 0
        move $t0, $a0              # $t0 = current position
loop:   lb   $t1, 0($t0)           # Load byte
        beq  $t1, $zero, done      # If null terminator, done
        addi $v0, $v0, 1           # length++
        addi $t0, $t0, 1           # Next character
        j    loop
done:   jr   $ra
```

**Usage Example:**
```assembly
.data
str: .asciiz "Hello"

.text
        la   $a0, str
        jal  strlen
        # $v0 = 5
```

### String Copy

**Function:** Copy string from source to destination

```assembly
# strcpy: Copy string
# Input: $a0 = destination address
#        $a1 = source address

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

**Usage Example:**
```assembly
.data
source: .asciiz "Hello"
dest:   .space 20

.text
        la   $a0, dest
        la   $a1, source
        jal  strcpy
        # dest now contains "Hello"
```

### String Comparison

**Function:** Compare two strings lexicographically

```assembly
# strcmp: Compare two strings
# Input: $a0 = first string address
#        $a1 = second string address
# Output: $v0 = 0 if equal
#              < 0 if first < second
#              > 0 if first > second

strcmp:
        move $t0, $a0              # First string pointer
        move $t1, $a1              # Second string pointer
loop:   lb   $t2, 0($t0)           # Load byte from first
        lb   $t3, 0($t1)           # Load byte from second
        bne  $t2, $t3, noteq       # If different, not equal
        beq  $t2, $zero, equal     # If both null, equal
        addi $t0, $t0, 1           # Next character in first
        addi $t1, $t1, 1           # Next character in second
        j    loop
equal:  li   $v0, 0                # Strings are equal
        jr   $ra
noteq:  sub  $v0, $t2, $t3         # Return difference
        jr   $ra
```

### String Concatenation

**Function:** Append source string to destination

```assembly
# strcat: Concatenate strings
# Input: $a0 = destination address
#        $a1 = source address

strcat:
        move $t0, $a0              # Destination pointer
        
        # Find end of destination
find_end:
        lb   $t2, 0($t0)
        beq  $t2, $zero, copy      # Found null terminator
        addi $t0, $t0, 1
        j    find_end
        
        # Copy source to end
copy:   move $t1, $a1              # Source pointer
copy_loop:
        lb   $t2, 0($t1)           # Load from source
        sb   $t2, 0($t0)           # Store to destination
        beq  $t2, $zero, done
        addi $t0, $t0, 1
        addi $t1, $t1, 1
        j    copy_loop
done:   jr   $ra
```

### Character Operations

**Convert to Uppercase:**
```assembly
# toupper: Convert lowercase letter to uppercase
# Input: $a0 = character
# Output: $v0 = uppercase character

toupper:
        move $v0, $a0              # Copy input
        
        # Check if lowercase (a-z is 97-122)
        slti $t0, $a0, 97          # < 'a'?
        bne  $t0, $zero, done      # Not lowercase
        slti $t0, $a0, 123         # <= 'z'?
        beq  $t0, $zero, done      # Not lowercase
        
        # Convert: subtract 32
        addi $v0, $a0, -32         # 'a'-32 = 'A'
done:   jr   $ra
```

**Count Vowels:**
```assembly
# count_vowels: Count vowels in string
# Input: $a0 = string address
# Output: $v0 = vowel count

count_vowels:
        move $t0, $a0              # String pointer
        li   $v0, 0                # Count = 0
        
loop:   lb   $t1, 0($t0)           # Load character
        beq  $t1, $zero, done      # If null, done
        
        # Check each vowel
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
        
        # Check uppercase vowels
        li   $t2, 'A'
        beq  $t1, $t2, is_vowel
        li   $t2, 'E'
        beq  $t1, $t2, is_vowel
        li   $t2, 'I'
        beq  $t1, $t2, is_vowel
        li   $t2, 'O'
        beq  $t1, $t2, is_vowel
        li   $t2, 'U'
        beq  $t1, $t2, is_vowel
        
        j    next
is_vowel:
        addi $v0, $v0, 1           # Increment count
next:   addi $t0, $t0, 1           # Next character
        j    loop
done:   jr   $ra
```

---

## 5.5 Floating-Point Operations

MIPS has **32 floating-point registers**: `$f0-$f31`
- Even-numbered registers for single precision (32-bit)
- Pairs of registers for double precision (64-bit)

### Basic Floating-Point Instructions

#### Load/Store

```assembly
lwc1 $f0, addr($t0)        # Load word to coprocessor 1 (FPU)
swc1 $f0, addr($t0)        # Store word from coprocessor 1
ldc1 $f0, addr($t0)        # Load double (uses $f0-$f1)
sdc1 $f0, addr($t0)        # Store double
```

#### Arithmetic Operations

**Single Precision:**
```assembly
add.s $f0, $f1, $f2        # $f0 = $f1 + $f2
sub.s $f0, $f1, $f2        # $f0 = $f1 - $f2
mul.s $f0, $f1, $f2        # $f0 = $f1 × $f2
div.s $f0, $f1, $f2        # $f0 = $f1 ÷ $f2
```

**Double Precision:**
```assembly
add.d $f0, $f2, $f4        # $f0 = $f2 + $f4 (doubles)
sub.d $f0, $f2, $f4
mul.d $f0, $f2, $f4
div.d $f0, $f2, $f4
```

#### Conversion Instructions

```assembly
cvt.s.w $f0, $f1           # Convert integer to float
cvt.w.s $f0, $f1           # Convert float to integer
cvt.d.w $f0, $f1           # Convert integer to double
cvt.s.d $f0, $f1           # Convert double to float
```

#### Move Between Integer and FP Registers

```assembly
mtc1 $t0, $f0              # Move to coprocessor 1
mfc1 $t0, $f0              # Move from coprocessor 1
```

### Floating-Point Example

**Calculate Average:**
```assembly
.data
values: .float 10.5, 20.3, 15.7
result: .float 0.0

.text
        # Load values
        lwc1 $f0, values       # Load 10.5
        lwc1 $f1, values+4     # Load 20.3
        lwc1 $f2, values+8     # Load 15.7
        
        # Sum values
        add.s $f3, $f0, $f1    # Sum first two
        add.s $f3, $f3, $f2    # Add third: 46.5
        
        # Load divisor (3.0)
        li   $t0, 3
        mtc1 $t0, $f4          # Move to FP register
        cvt.s.w $f4, $f4       # Convert int to float
        
        # Calculate average
        div.s $f3, $f3, $f4    # 46.5 / 3.0 = 15.5
        
        # Store result
        swc1 $f3, result       # Store 15.5
```

### Floating-Point Comparison

```assembly
# Compare floats
c.eq.s $f0, $f1            # Set FP condition if equal
bc1t label                 # Branch if true

c.lt.s $f0, $f1            # Set FP condition if less than
bc1t label                 # Branch if true

c.le.s $f0, $f1            # Set FP condition if less or equal
bc1t label                 # Branch if true
```

**Example:**
```assembly
.data
x: .float 5.5
y: .float 10.3

.text
        lwc1 $f0, x
        lwc1 $f1, y
        
        c.lt.s $f0, $f1        # Compare x < y
        bc1t x_less            # Branch if true
        # Code if x >= y
        j    done
x_less: # Code if x < y
done:
```

---

## 5.6 Memory-Mapped I/O

**Memory-mapped I/O** uses special memory addresses to communicate with I/O devices.

### MARS Memory-Mapped Addresses

**Keyboard:**
- Control: `0xFFFF0000`
  - Bit 0 = 1: Character ready
- Data: `0xFFFF0004`
  - Contains ASCII code of character

**Display:**
- Control: `0xFFFF0008`
  - Bit 0 = 1: Ready to receive character
- Data: `0xFFFF000C`
  - Character to display

### Polling for Keyboard Input

```assembly
# Poll for keyboard input
        lui  $t0, 0xFFFF           # Upper 16 bits of address
poll:   lw   $t1, 0($t0)           # Read keyboard control
        andi $t1, $t1, 1           # Check ready bit
        beq  $t1, $zero, poll      # If not ready, poll again
        
        lw   $a0, 4($t0)           # Read character data
        # Process character in $a0
```

### Writing to Display

```assembly
# Write character to display
        lui  $t0, 0xFFFF           # Base address
        
wait:   lw   $t1, 8($t0)           # Read display control
        andi $t1, $t1, 1           # Check ready bit
        beq  $t1, $zero, wait      # Wait until ready
        
        li   $t2, 'A'              # Character to display
        sw   $t2, 12($t0)          # Write to display data
```

---

## 5.7 Advanced Topics

### Bitwise Operations Applications

**Check if Number is Even:**
```assembly
andi $t0, $t1, 1           # AND with 1 (check LSB)
beq  $t0, $zero, even      # If bit 0 is 0, even
# odd
j    continue
even:
# even
continue:
```

**Extract Specific Bits:**
```assembly
# Extract bits 8-15 from $t1
srl  $t0, $t1, 8           # Shift right 8 positions
andi $t0, $t0, 0xFF        # Mask to get 8 bits
```

**Set Specific Bit:**
```assembly
# Set bit 5 in $t1
ori  $t0, $t1, 0x20        # OR with 0b100000
```

**Clear Specific Bit:**
```assembly
# Clear bit 3 in $t1
andi $t0, $t1, 0xFFFFFFF7  # AND with ~(0b1000)
```

**Toggle Specific Bit:**
```assembly
# Toggle bit 4 in $t1
xori $t0, $t1, 0x10        # XOR with 0b10000
```

### Dynamic Memory Allocation

**Using sbrk Syscall:**
```assembly
# Allocate array of 100 integers on heap
li   $v0, 9                # sbrk service
li   $a0, 400              # 100 integers × 4 bytes
syscall                    # $v0 = address of allocated memory
move $s0, $v0              # Save address

# Use the allocated memory
li   $t0, 42
sw   $t0, 0($s0)           # Store value at beginning
sw   $t0, 4($s0)           # Store at next location
```

**Dynamic Array Example:**
```assembly
.data
size_prompt: .asciiz "Enter array size: "
val_prompt:  .asciiz "Enter value: "

.text
        # Ask for size
        li   $v0, 4
        la   $a0, size_prompt
        syscall
        li   $v0, 5
        syscall
        move $s0, $v0          # $s0 = size
        
        # Allocate memory
        sll  $a0, $s0, 2       # size × 4
        li   $v0, 9
        syscall
        move $s1, $v0          # $s1 = array address
        
        # Fill array
        li   $t0, 0            # index
fill:   bge  $t0, $s0, done
        
        li   $v0, 4
        la   $a0, val_prompt
        syscall
        li   $v0, 5
        syscall                # Read value
        
        sll  $t1, $t0, 2       # offset
        add  $t2, $s1, $t1     # address
        sw   $v0, 0($t2)       # Store value
        
        addi $t0, $t0, 1
        j    fill
done:
```

### Bit Packing/Unpacking

**Pack Two 16-bit Values into One 32-bit Word:**
```assembly
# $t0 = first 16-bit value
# $t1 = second 16-bit value
sll  $t2, $t0, 16          # Shift first to upper 16 bits
andi $t1, $t1, 0xFFFF      # Mask second to 16 bits
or   $t2, $t2, $t1         # Combine
# $t2 now contains both values packed
```

**Unpack:**
```assembly
# $t2 contains packed value
srl  $t0, $t2, 16          # Extract upper 16 bits
andi $t1, $t2, 0xFFFF      # Extract lower 16 bits
```

---

## 5.8 Debugging Techniques

### Using MARS Debugger

**Workflow:**
1. **Set Breakpoints**: Click line number in editor
2. **Assemble**: Press F3
3. **Run**: Press F5 (stops at breakpoint)
4. **Step Through**: Press F7 (step into) or F8 (step over)
5. **Inspect**: Watch registers and memory windows
6. **Continue**: Press F5 again

### Debug Print Statements

**Print Register Value:**
```assembly
# Debug: Print value in $t0
li   $v0, 1
move $a0, $t0
syscall

# Print newline
li   $v0, 11
li   $a0, 10               # ASCII newline
syscall
```

**Print Label:**
```assembly
.data
debug_msg: .asciiz "DEBUG: Value = "

.text
        li   $v0, 4
        la   $a0, debug_msg
        syscall
        
        li   $v0, 1
        move $a0, $t0
        syscall
        
        li   $v0, 11
        li   $a0, 10
        syscall
```

### Assertion Checks

**Check Array Bounds:**
```assembly
# Verify 0 <= index < length
blt  $t0, $zero, error     # index < 0?
bge  $t0, $s1, error       # index >= length?
# Proceed with array access
j    ok
error:
        li   $v0, 4
        la   $a0, error_msg
        syscall
        li   $v0, 10
        syscall                # Exit
ok:
```

### Common Debugging Strategies

1. **Single-step through code**
2. **Print intermediate values**
3. **Check assumptions** (bounds, null pointers)
4. **Verify register preservation**
5. **Check stack alignment**
6. **Trace function calls**

---

## 5.9 Practice Problems - Chapter 5

### Problem 1: Sum and Average

**Task:** Read N integers, compute sum and average

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

### Problem 2: Palindrome Checker

**Task:** Check if a string is a palindrome

**Solution:**
```assembly
.data
prompt:     .asciiz "Enter string: "
yes_msg:    .asciiz "Is a palindrome!\n"
no_msg:     .asciiz "Not a palindrome.\n"
buffer:     .space 100

.text
        # Read string
        li   $v0, 4
        la   $a0, prompt
        syscall
        li   $v0, 8
        la   $a0, buffer
        li   $a1, 100
        syscall
        
        # Remove newline
        la   $t0, buffer
remove:  lb   $t1, 0($t0)
        beq  $t1, 10, found_nl
        beq  $t1, $zero, check
        addi $t0, $t0, 1
        j    remove
found_nl:
        sb   $zero, 0($t0)
        
        # Check palindrome
check:  la   $t0, buffer           # Left pointer
        la   $t1, buffer           # Right pointer
        
        # Find end
find_end:
        lb   $t2, 0($t1)
        beq  $t2, $zero, found
        addi $t1, $t1, 1
        j    find_end
found:  addi $t1, $t1, -1          # Back to last char
        
        # Compare
compare:
        bge  $t0, $t1, is_pal      # Pointers met
        lb   $t2, 0($t0)           # Left char
        lb   $t3, 0($t1)           # Right char
        bne  $t2, $t3, not_pal     # Different
        addi $t0, $t0, 1           # Move left right
        addi $t1, $t1, -1          # Move right left
        j    compare
        
is_pal: li   $v0, 4
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

## KEY TAKEAWAYS

1. **System calls** provide OS services: I/O, memory, file operations

2. **String processing** requires byte-level operations with null termination

3. **Floating-point** uses separate registers and instructions

4. **Memory-mapped I/O** allows direct hardware communication

5. **Debugging** is essential: use breakpoints, print statements, assertions

---

## COURSE COMPLETION

Congratulations! You have completed all 5 chapters of Computer Organization:

**[Chapter 1](Chapter1_Introduction.md)**: Computer fundamentals, number systems  
**[Chapter 2](Chapter2_Instruction_Set_Design_Part1.md)**: MIPS basics, registers, instructions  
**[Chapter 3](Chapter3_Instruction_Set_Design_Part2.md)**: Control flow, loops  
**[Chapter 4](Chapter4_Instruction_Set_Design_Part3.md)**: Functions, recursion, arrays  
**[Chapter 5](Chapter5_Instruction_Set_Design_Part4.md)**: I/O, strings, advanced topics  

---

*This material is part of CCIT4026: Introduction to Computer Organization*  
*HKU SPACE Community College*  
*Chapter 5 of 5*
