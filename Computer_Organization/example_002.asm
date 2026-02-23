.text
.globl main
main:
    li $t0, 10  # load the value 10 into register $t0
    li $s1, -5  # load the value -5 into register $s1

.data
msg: .asciiz "Hello\n\0"

.text
.globl main
main:
    li $v0, 4  # load the value 4 into register $v0
    la $a0, msg  # load the address of the string into register $a0
    syscall  # call the system call to print the string

.data
temperature_c: .word 32
temperature_f: .word 0

integer temperature_c = 32
integer temperature_f;
temperature_f = (temperature_c * 9/5) + 32;

.text
.globl main
main:
    lw $t0, temperature_c  # load the value 100 into register $t0
    // multiply the value of temperature_c by 9/5 + 32
    li $t1, 9
    li $t2, 5
    div $t0, $t1, $t2
    add $t0, $t0, $t0
    add $t0, $t0, $t0
    add $t0, $t0, 32
    // store the value of temperature_f into register $t0
    sw $t0, temperature_f  # store the value of temperature_f into register $t0

int x[3] = {1, 2, 3};

int *p = x;