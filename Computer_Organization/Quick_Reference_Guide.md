# MIPS ASSEMBLY QUICK REFERENCE GUIDE
## Introduction to Computer Organization (CCIT4026)

---

## REGISTER QUICK REFERENCE

| Name | Number | Usage | Preserved? |
|------|--------|-------|------------|
| `$zero` | 0 | Constant 0 | N/A |
| `$at` | 1 | Assembler temporary | No |
| `$v0-$v1` | 2-3 | Return values | No |
| `$a0-$a3` | 4-7 | Function arguments | No |
| `$t0-$t7` | 8-15 | Temporaries | No |
| `$s0-$s7` | 16-23 | Saved variables | **Yes** |
| `$t8-$t9` | 24-25 | More temporaries | No |
| `$k0-$k1` | 26-27 | Kernel reserved | N/A |
| `$gp` | 28 | Global pointer | Yes |
| `$sp` | 29 | Stack pointer | **Yes** |
| `$fp` | 30 | Frame pointer | Yes |
| `$ra` | 31 | Return address | **Yes** |

---

## INSTRUCTION REFERENCE

### Arithmetic
```assembly
add  $d, $s, $t      # $d = $s + $t
addi $t, $s, imm     # $t = $s + imm
addu $d, $s, $t      # Unsigned add (no overflow)
sub  $d, $s, $t      # $d = $s - $t
subu $d, $s, $t      # Unsigned subtract
mult $s, $t          # HI:LO = $s × $t
multu $s, $t         # Unsigned multiply
div  $s, $t          # LO = $s / $t, HI = $s % $t
divu $s, $t          # Unsigned divide
mfhi $d              # $d = HI
mflo $d              # $d = LO
```

### Logical
```assembly
and  $d, $s, $t      # $d = $s & $t
andi $t, $s, imm     # $t = $s & imm
or   $d, $s, $t      # $d = $s | $t
ori  $t, $s, imm     # $t = $s | imm
xor  $d, $s, $t      # $d = $s ^ $t
xori $t, $s, imm     # $t = $s ^ imm
nor  $d, $s, $t      # $d = ~($s | $t)
sll  $d, $t, amt     # $d = $t << amt
srl  $d, $t, amt     # $d = $t >> amt (logical)
sra  $d, $t, amt     # $d = $t >> amt (arithmetic)
```

### Data Transfer
```assembly
lw   $t, offset($s)  # $t = Memory[$s + offset]
lh   $t, offset($s)  # Load halfword (16 bits, sign-extended)
lhu  $t, offset($s)  # Load halfword (zero-extended)
lb   $t, offset($s)  # Load byte (8 bits, sign-extended)
lbu  $t, offset($s)  # Load byte (zero-extended)
sw   $t, offset($s)  # Memory[$s + offset] = $t
sh   $t, offset($s)  # Store halfword
sb   $t, offset($s)  # Store byte
lui  $t, imm         # $t = imm << 16
```

### Control Flow
```assembly
beq  $s, $t, label   # if ($s == $t) goto label
bne  $s, $t, label   # if ($s != $t) goto label
slt  $d, $s, $t      # $d = ($s < $t) ? 1 : 0
slti $t, $s, imm     # $t = ($s < imm) ? 1 : 0
sltu $d, $s, $t      # Unsigned slt
sltiu $t, $s, imm    # Unsigned slti
j    label           # Jump to label
jal  label           # Jump and link (save return address)
jr   $s              # Jump to address in $s
```

### Pseudo-Instructions
```assembly
li   $t, imm         # Load immediate
la   $t, label       # Load address
move $d, $s          # $d = $s
blt  $s, $t, label   # Branch if less than
bgt  $s, $t, label   # Branch if greater than
ble  $s, $t, label   # Branch if less than or equal
bge  $s, $t, label   # Branch if greater than or equal
mul  $d, $s, $t      # $d = $s × $t (simplified)
```

---

## SYSCALL SERVICES

```assembly
li   $v0, code       # Load service code
# Set arguments (if needed)
syscall              # Execute service
# Check return value (if any)
```

| Service | Code | Arguments | Returns |
|---------|------|-----------|---------|
| print_int | 1 | `$a0` = integer | - |
| print_string | 4 | `$a0` = address | - |
| read_int | 5 | - | `$v0` = integer |
| read_string | 8 | `$a0` = buffer, `$a1` = length | - |
| sbrk (allocate) | 9 | `$a0` = bytes | `$v0` = address |
| exit | 10 | - | - |
| print_char | 11 | `$a0` = character | - |
| read_char | 12 | - | `$v0` = character |

---

## PROGRAM TEMPLATE

```assembly
# NAME: [Your Name]
# Student ID: [Your ID]
# CCIT4026 Computer Organization
# [Assignment Name]

#----- Data Segment -----------------
.data
msg:        .asciiz "Hello, World!\n"
number:     .word 42
array:      .word 1, 2, 3, 4, 5
buffer:     .space 100

#----- Text Segment -----------------
.text
.globl __start

__start:
        # Main program code here
        
        # Exit program
        li   $v0, 10
        syscall

# Functions below main
function_name:
        # Prologue
        addi $sp, $sp, -8
        sw   $ra, 4($sp)
        sw   $s0, 0($sp)
        
        # Function body
        # ...
        
        # Epilogue
        lw   $s0, 0($sp)
        lw   $ra, 4($sp)
        addi $sp, $sp, 8
        jr   $ra
```

---

## COMMON PATTERNS

### If-Then-Else
```assembly
        bne  $s0, $s1, else    # if (a != b) goto else
        # then block
        j    endif
else:   # else block
endif:
```

### While Loop
```assembly
while:  slt  $t0, $s0, $s1     # i < n?
        beq  $t0, $zero, endw  # exit if false
        # loop body
        j    while
endw:
```

### For Loop
```assembly
        li   $t0, 0            # i = 0
for:    bge  $t0, $s0, endf    # i >= n?
        # loop body
        addi $t0, $t0, 1       # i++
        j    for
endf:
```

### Function Call
```assembly
        # Prepare arguments
        move $a0, $s0
        move $a1, $s1
        # Call function
        jal  function_name
        # Use return value
        move $s2, $v0
```

### Stack Operations
```assembly
# Push register
addi $sp, $sp, -4
sw   $t0, 0($sp)

# Pop register
lw   $t0, 0($sp)
addi $sp, $sp, 4
```

### Array Access
```assembly
# A[i] where each element is 4 bytes
sll  $t0, $s0, 2       # $t0 = i × 4
add  $t0, $t0, $s1     # $t0 = address of A[i]
lw   $t1, 0($t0)       # $t1 = A[i]
```

---

## MEMORY MAP

```
0xFFFFFFFF  ┌─────────────────┐
            │   Kernel Space  │
0x80000000  ├─────────────────┤
            │   Stack         │ ← $sp (grows down ↓)
            │                 │
            ├─────────────────┤
            │   Heap          │ (grows up ↑)
0x10010000  ├─────────────────┤
            │   Static Data   │ ← .data
0x10000000  ├─────────────────┤
            │   Text (Code)   │ ← .text
0x00400000  ├─────────────────┤
            │   Reserved      │
0x00000000  └─────────────────┘
```

---

## DATA DECLARATIONS

```assembly
.data
# Strings
str1:       .asciiz "Hello"      # Null-terminated
str2:       .ascii "World"       # No null terminator

# Integers
num1:       .word 42             # 32-bit integer
nums:       .word 1, 2, 3, 4     # Array of integers

# Other types
half:       .half 100            # 16-bit
byte:       .byte 10             # 8-bit
flt:        .float 3.14          # 32-bit float
dbl:        .double 3.14159      # 64-bit double

# Allocate space
buffer:     .space 100           # 100 bytes
array:      .space 40            # 10 integers (10 × 4)
```

---

## INSTRUCTION FORMATS

### R-Type (Register)
```
| opcode | rs    | rt    | rd    | shamt | funct |
| 6 bits | 5 bits| 5 bits| 5 bits| 5 bits| 6 bits|

Example: add $t0, $t1, $t2
```

### I-Type (Immediate)
```
| opcode | rs    | rt    | immediate      |
| 6 bits | 5 bits| 5 bits| 16 bits        |

Example: addi $t0, $t1, 100
```

### J-Type (Jump)
```
| opcode | address                        |
| 6 bits | 26 bits                        |

Example: j label
```

---

## COMMON CONVERSIONS

### C to MIPS Examples

**Variable assignment:**
```c
int a = b + c;
```
```assembly
add  $s0, $s1, $s2    # $s0=a, $s1=b, $s2=c
```

**Array access:**
```c
A[3] = 42;
```
```assembly
la   $t0, A           # Base address
li   $t1, 42
sw   $t1, 12($t0)     # Offset = 3 × 4 = 12
```

**If statement:**
```c
if (a == b)
    c = 1;
```
```assembly
bne  $s0, $s1, endif
li   $s2, 1
endif:
```

**Function:**
```c
int add(int x, int y) {
    return x + y;
}
```
```assembly
add_func:
    add  $v0, $a0, $a1
    jr   $ra
```

---

## DEBUGGING CHECKLIST

- [ ] All branches have labels?
- [ ] All labels are unique?
- [ ] Array offsets calculated correctly (× 4 for words)?
- [ ] Registers saved/restored properly in functions?
- [ ] Stack pointer adjusted correctly (multiples of 4)?
- [ ] Return address ($ra) saved in functions that call others?
- [ ] Program ends with exit syscall?
- [ ] Strings are null-terminated (.asciiz)?
- [ ] Comments explain logic?
- [ ] Indentation is consistent?

---

## COMMON ERRORS

| Error | Likely Cause | Solution |
|-------|--------------|----------|
| Branch out of range | Target too far | Use jump (j) instead |
| Runtime exception | Invalid memory access | Check array bounds |
| Infinite loop | Loop condition never false | Verify counter updates |
| Wrong result | Register overwrite | Save/restore registers |
| Crash after function call | $ra not saved | Save $ra on stack |

---

## USEFUL CALCULATIONS

**Powers of 2:**
```
2^0 = 1         2^8  = 256
2^1 = 2         2^10 = 1024 (1K)
2^2 = 4         2^16 = 65536 (64K)
2^3 = 8         2^20 = 1048576 (1M)
2^4 = 16        2^30 = 1073741824 (1G)
```

**Multiply/Divide by powers of 2:**
```assembly
# Multiply by 4: shift left 2
sll  $t0, $t1, 2

# Divide by 8: shift right 3
srl  $t0, $t1, 3
```

**ASCII Values:**
```
'0' = 48 (0x30)
'A' = 65 (0x41)
'a' = 97 (0x61)
' ' = 32 (0x20)
'\n'= 10 (0x0A)
'\0'= 0  (0x00)
```

---

## MARS SIMULATOR SHORTCUTS

| Key | Action |
|-----|--------|
| F3 | Assemble |
| F5 | Run (Go) |
| F7 | Step Into |
| F8 | Step Over |
| F9 | Toggle Breakpoint |
| F10 | Reset |
| Ctrl+S | Save |
| Ctrl+O | Open |

---

## TIPS

1. **Comment your code** - Future you will thank present you
2. **Plan before coding** - Draw flowcharts for complex logic
3. **Test incrementally** - Don't write everything at once
4. **Use meaningful labels** - `loop_start` not `L1`
5. **Save $s registers** - If you modify them in functions
6. **Check bounds** - Before accessing arrays
7. **Initialize variables** - Don't assume registers are 0
8. **Use debugger** - Step through to understand behavior

---

*This quick reference covers the most commonly used MIPS instructions and patterns for CCIT4026.*

*For detailed explanations, see the Comprehensive Teaching Material document.*
