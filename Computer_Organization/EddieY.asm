# NAME: Yuen Chuek Hang
# Student ID: 20285660 
# CCIT4026 Computer Organization
# CCIT4026-CL08
# Lab2
#
# Input and Output*/
#-----Data Segment-----------------
    .data
msg0: .asciiz "Please enter your last name: "
msg1: .asciiz "Please enter your first name: "
msg2: .asciiz "Your last name is "
msg3: .asciiz "Your first name is "
msg4: .asciiz "What is you weight (in kg)? "
msg5: .asciiz "Your weight is kg. "
#-----Text Segment-----------------
    .text
    .globl __start
__start:
# ----------------------
# Write your code here
    #Print "Please enter your last name: "
    la $a0, msg0
    li $v0, 4
    syscall

    #Get the value for last name
    la $v0, 5
    syscall

    # Move the value of $v0 to $t0
    add $t0, $v0, $zero

    # Print "Please enter your first name: "
    la $a0, msg1
    li $v0, 4
    syscall

    # Get the value for first name
    la $v0, 5
    syscall

    # Move the value of $v0 to $t1
    add $t1, $v0, $zero

    # Print "Your last name is "
    la $a0, msg2
    li $v0, 4
    syscall

    # Print the last name value
    li $t0, 4
    syscall

    # Print "Your first name is "
    la $a0, msg3
    li $v0, 4
    syscall

    # Print the first name value
    li $t1, 4
    syscall

# ----------------------
    
    li $v0, 10
    syscall
# Terminate the program