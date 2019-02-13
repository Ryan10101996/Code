.data
myArray: .space 184
s1:    .asciiz    "Enter a number greater than 0 but less than 47:   "
s2:    .asciiz    "Wrong. Try again. \n"
newline:   .asciiz    "\n"


.text
.globl    main
main:
    li $t0, 1
    li $t1, 46
    li $v0,4
    la $a0, s1
    syscall
    li $v0,5
    syscall
    move $t3,$v0
    
    
    li $t9, 0
    add $t9,$t9,$t3
 
 
    

    slt $s0, $t3, $t0
    slt $s1, $t1, $t3
    bne $s0, $zero, outOfBounds
    bne $s1, $zero, outOfBounds
    

    addi $t4, $zero, 1
    addi $t5, $zero, 0
    addi $t6, $zero, 1

    sw $zero, myArray($t5)
        addi $t5, $t5, 4
    sw $t6, myArray($t5)
        addi $t5, $t5, 4
        addi $t7, $zero, 0
        addi $t8, $zero, 4

    start:
    beq $t4, $t9, exit
    lw $t0, myArray($t7)
   
     lw $t1, myArray($t8)
    add $t6, $t0, $t1
    sw $t6, myArray($t5)
        addi $t5, $t5, 4
        addi $t7, $t7, 4
        addi $t8, $t8, 4
        addi $t4, $t4, 1
    j start
    exit:


    addi $t4, $zero, -1
    addi $t5, $zero, 0

    while:
    beq $t4, $t9, end
    lw $t6, myArray($t5)
        addi $t5, $t5, 4
    li $v0, 1
    move $a0, $t6
    syscall
    li $v0,4
    la $a0, newline
    syscall
    addi $t4, $t4, 1
    j while
    end:

    li $v0,10
    syscall

outOfBounds:
    li $v0,4
    la $a0, s2
    syscall
    li $v0,4
    la $a0, newline
    syscall
    j main

