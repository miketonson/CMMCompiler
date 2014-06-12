.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
main:
move $fp, $sp
addi $sp, $sp, -2048
li $t1, 5
sw $t1, -4($fp)
li $v0, 4
la $a0, _prompt
syscall
li $v0, 5
syscall
move $t1, $v0
sw $t1, -8($fp)
label1:
lw $t1, -8($fp)
li $t2, 15
blt $t1, $t2, label2
j label3
label2:
li $t2, 1
lw $t1, -8($fp)
add $t3, $t1, $t2
sw $t3, -8($fp)
lw $a0, -8($fp)
li $v0, 1
syscall
li $v0, 4
la $a0, _ret
syscall
j label1
label3:
lw $t1, -4($fp)
lw $t2, -8($fp)
div $t1, $t2
mflo $t3
sw $t3, -8($fp)
lw $a0, -8($fp)
li $v0, 1
syscall
li $v0, 4
la $a0, _ret
syscall
addi $sp, $sp, 2048
li $t1 0
move $v0, $t1
jr $ra
