.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
main:
move $fp $sp
addi $sp, $sp, -2048
li $t1 0
sw $t1 -4($fp)
lw $t1 -4($fp)
sw $t1 -8($fp)
