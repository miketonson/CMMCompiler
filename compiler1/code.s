.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
main:
move $fp $sp
addi $sp, $sp, -2048
li $t2 1
lw $t1 -8($fp)
add $t3, $t1, $t2
sw $t3 -4($fp)
