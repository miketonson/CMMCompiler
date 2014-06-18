.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
power:
addi $sp, $sp, -2048
lw $t1, 8($fp)
sw $t1, -4($fp)
lw $t1, 12($fp)
sw $t1, -8($fp)
li $t1, 1
sw $t1, -12($fp)
label1:
lw $t1, -8($fp)
li $t2, 0
bgt $t1, $t2, label2
j label3
label2:
lw $t1, -12($fp)
lw $t2, -4($fp)
mul $t3, $t1, $t2
sw $t3, -12($fp)
li $t2, 1
lw $t1, -8($fp)
sub $t3, $t1, $t2
sw $t3, -8($fp)
j label1
label3:
addi $sp, $sp, 2048
lw $t1 -12($fp)
move $v0, $t1
jr $ra
mod:
addi $sp, $sp, -2048
lw $t1, 8($fp)
sw $t1, -4($fp)
lw $t1, 12($fp)
sw $t1, -8($fp)
lw $t1, -4($fp)
lw $t2, -8($fp)
div $t1, $t2
mflo $t3
sw $t3, -12($fp)
lw $t1, -12($fp)
lw $t2, -8($fp)
mul $t3, $t1, $t2
sw $t3, -16($fp)
lw $t1, -4($fp)
lw $t2, -16($fp)
sub $t3, $t1, $t2
sw $t3, -20($fp)
addi $sp, $sp, 2048
lw $t1 -20($fp)
move $v0, $t1
jr $ra
getNumDigits:
addi $sp, $sp, -2048
lw $t1, 8($fp)
sw $t1, -4($fp)
li $t1, 0
sw $t1, -8($fp)
lw $t1, -4($fp)
li $t2, 0
blt $t1, $t2, label4
j label5
label4:
addi $sp, $sp, 2048
li $t1 -1
move $v0, $t1
jr $ra
label5:
label6:
lw $t1, -4($fp)
li $t2, 0
bgt $t1, $t2, label7
j label8
label7:
li $t2, 10
lw $t1, -4($fp)
div $t1, $t2
mflo $t3
sw $t3, -4($fp)
li $t2, 1
lw $t1, -8($fp)
add $t3, $t1, $t2
sw $t3, -8($fp)
j label6
label8:
addi $sp, $sp, 2048
lw $t1 -8($fp)
move $v0, $t1
jr $ra
isNarcissistic:
addi $sp, $sp, -2048
lw $t1, 8($fp)
sw $t1, -4($fp)
lw $t1, -4($fp)
sw $t1, -8($fp)
sw $fp, -12($fp)
sw $ra, -16($fp)
addi $fp, $fp, -16
jal getNumDigits
lw $ra, 0($fp)
lw $fp, 4($fp)
move $t1, $v0
sw $t1, -20($fp)
li $t1, 0
sw $t1, -24($fp)
lw $t1, -4($fp)
sw $t1, -28($fp)
label9:
lw $t1, -28($fp)
li $t2, 0
bgt $t1, $t2, label10
j label11
label10:
li $t1, 10
sw $t1, -32($fp)
lw $t1, -28($fp)
sw $t1, -36($fp)
sw $fp, -40($fp)
sw $ra, -44($fp)
addi $fp, $fp, -44
jal mod
lw $ra, 0($fp)
lw $fp, 4($fp)
move $t1, $v0
sw $t1, -48($fp)
lw $t1, -28($fp)
lw $t2, -48($fp)
sub $t3, $t1, $t2
sw $t3, -52($fp)
li $t2, 10
lw $t1, -52($fp)
div $t1, $t2
mflo $t3
sw $t3, -28($fp)
lw $t1, -20($fp)
sw $t1, -56($fp)
lw $t1, -48($fp)
sw $t1, -60($fp)
sw $fp, -64($fp)
sw $ra, -68($fp)
addi $fp, $fp, -68
jal power
lw $ra, 0($fp)
lw $fp, 4($fp)
move $t1, $v0
sw $t1, -72($fp)
lw $t1, -24($fp)
lw $t2, -72($fp)
add $t3, $t1, $t2
sw $t3, -24($fp)
j label9
label11:
lw $t1, -24($fp)
lw $t2, -4($fp)
beq $t1, $t2, label12
j label13
label12:
addi $sp, $sp, 2048
li $t1 1
move $v0, $t1
jr $ra
j label14
label13:
addi $sp, $sp, 2048
li $t1 0
move $v0, $t1
jr $ra
label14:
printHexDigit:
addi $sp, $sp, -2048
lw $t1, 8($fp)
sw $t1, -4($fp)
lw $t1, -4($fp)
li $t2, 10
blt $t1, $t2, label15
j label16
label15:
lw $a0, -4($fp)
li $v0, 1
syscall
li $v0, 4
la $a0, _ret
syscall
j label17
label16:
li $t1, 0
lw $t2, -4($fp)
sub $t3, $t1, $t2
sw $t3, -8($fp)
lw $a0, -8($fp)
li $v0, 1
syscall
li $v0, 4
la $a0, _ret
syscall
label17:
addi $sp, $sp, 2048
li $t1 0
move $v0, $t1
jr $ra
printHex:
addi $sp, $sp, -2048
lw $t1, 8($fp)
sw $t1, -4($fp)
li $t1, 0
sw $t1, -24($fp)
label18:
lw $t1, -24($fp)
li $t2, 4
blt $t1, $t2, label19
j label20
label19:
li $t2, 4
lw $t1, -24($fp)
mul $t3, $t1, $t2
sw $t3, -28($fp)
li $t1, -20
lw $t2, -28($fp)
add $t3, $t1, $t2
sw $t3, -32($fp)
li $t1, 16
sw $t1, -36($fp)
lw $t1, -4($fp)
sw $t1, -40($fp)
sw $fp, -44($fp)
sw $ra, -48($fp)
addi $fp, $fp, -48
jal mod
lw $ra, 0($fp)
lw $fp, 4($fp)
move $t1, $v0
sw $t1, -52($fp)
lw $t1, -52($fp)
lw $t2, -32($fp)
add $t3, $t2, $fp
sw $t1, 0($t3)
li $t2, 16
lw $t1, -4($fp)
div $t1, $t2
mflo $t3
sw $t3, -4($fp)
li $t2, 1
lw $t1, -24($fp)
add $t3, $t1, $t2
sw $t3, -24($fp)
j label18
label20:
li $t1, 3
sw $t1, -24($fp)
label21:
lw $t1, -24($fp)
li $t2, 0
bge $t1, $t2, label22
j label23
label22:
li $t2, 4
lw $t1, -24($fp)
mul $t3, $t1, $t2
sw $t3, -56($fp)
li $t1, -20
lw $t2, -56($fp)
add $t3, $t1, $t2
sw $t3, -60($fp)
lw $t2, -60($fp)
add $t3, $t2, $fp
lw $t1, 0($t3)
sw $t1, -64($fp)
sw $fp, -68($fp)
sw $ra, -72($fp)
addi $fp, $fp, -72
jal printHexDigit
lw $ra, 0($fp)
lw $fp, 4($fp)
move $t1, $v0
sw $t1, -76($fp)
li $t2, 1
lw $t1, -24($fp)
sub $t3, $t1, $t2
sw $t3, -24($fp)
j label21
label23:
addi $sp, $sp, 2048
li $t1 0
move $v0, $t1
jr $ra
main:
move $fp, $sp
addi $sp, $sp, -2048
li $t1, 0
sw $t1, -4($fp)
li $t1, 9474
sw $t1, -8($fp)
label24:
lw $t1, -8($fp)
li $t2, 9475
blt $t1, $t2, label25
j label26
label25:
lw $t1, -8($fp)
sw $t1, -12($fp)
sw $fp, -16($fp)
sw $ra, -20($fp)
addi $fp, $fp, -20
jal isNarcissistic
lw $ra, 0($fp)
lw $fp, 4($fp)
move $t1, $v0
sw $t1, -24($fp)
lw $t1, -24($fp)
li $t2, 1
beq $t1, $t2, label27
j label28
label27:
lw $t1, -8($fp)
sw $t1, -28($fp)
sw $fp, -32($fp)
sw $ra, -36($fp)
addi $fp, $fp, -36
jal printHex
lw $ra, 0($fp)
lw $fp, 4($fp)
move $t1, $v0
sw $t1, -40($fp)
li $t2, 1
lw $t1, -4($fp)
add $t3, $t1, $t2
sw $t3, -4($fp)
label28:
li $t2, 1
lw $t1, -8($fp)
add $t3, $t1, $t2
sw $t3, -8($fp)
j label24
label26:
addi $sp, $sp, 2048
lw $t1 -4($fp)
move $v0, $t1
jr $ra
