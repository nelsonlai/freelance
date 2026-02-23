.data
prompt_lat_name: .asciiz "Enter your last name: "
prompt_first_name: .asciiz "Enter your first name: "
prompt_weight: .asciiz "Enter your weight: "
msg_last_name: .asciiz "Your last name is "
msg_first_name: .asciiz "Your first name is "
msg_weight: .asciiz "Your weight is "
buffer_last_name: .space 100
buffer_first_name: .space 100
buffer_weight: .space 100


.text
.globl main

main:
    # Print the prompt
    li $v0, 4   # syscall 4 = print string
    la $a0, prompt_lat_name
    syscall

    # Input the string
    li $v0, 8   # syscall 8 = input string
    la $a0, buffer_last_name
    li $a1, 100
    syscall

    # Output the string
    li $v0, 4   # syscall 4 = print string
    la $a0, msg_last_name
    syscall

    # Output the name
    li $v0, 4   # syscall 4 = print string
    la $a0, buffer_last_name
    syscall

    # Exit the program
    li $v0, 10  # syscall 10 = exit
    syscall



