	.data
number: .asciiz "Enter a value greater than 0 and less than 47: "
array: .space 50
	
	
	.text
main:
loop:
li $v0, 4
la $a0, number
syscall
loop_end:

li $v0,5  
syscall

bge $v0,47,loop
ble $v0,0,loop

move $t1,$v0
li $t2,0
addi $t3,$zero,0

while:
beq $t1,$t2,done
sw $t2, array($t3)
addi $t3, $t3, 4
add $t2,$t2,1
done:




