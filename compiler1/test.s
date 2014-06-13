.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
josef:
addi $sp, $sp, -2048
lw $t1, 8($fp)
sw $t1, -4($fp)
li $t1, 0
sw $t1, -92($fp)
li $t1, 0
sw $t1, -96($fp)
label1:
lw $t1, -92($fp)
li $t2, 21
blt $t1, $t2, label2
j label3
label2:
li $t2, 4
lw $t1, -92($fp)
mul $t3, $t1, $t2
sw $t3, -100($fp)
li $t1, -88
lw $t2, -100($fp)
add $t3, $t1, $t2
sw $t3, -104($fp)
li $t2, 1
lw $t1, -92($fp)
add $t3, $t1, $t2
sw $t3, -108($fp)
lw $t1, -108($fp)
lw $t2, -104($fp)
add $t3, $t2, $fp
sw $t1, 0($t3)
li $t2, 1
lw $t1, -92($fp)
add $t3, $t1, $t2
sw $t3, -92($fp)
j label1
label3:
li $t1, 0
sw $t1, -92($fp)
label4:
lw $t1, -92($fp)
li $t2, 21
blt $t1, $t2, label5
j label6
label5:
li $t1, 1
sw $t1, -112($fp)
label7:
lw $t1, -112($fp)
lw $t2, -4($fp)
blt $t1, $t2, label8
j label9
label8:
label10:
li $t2, 4
lw $t1, -96($fp)
mul $t3, $t1, $t2
sw $t3, -116($fp)
li $t1, -88
lw $t2, -116($fp)
add $t3, $t1, $t2
sw $t3, -120($fp)
lw $t3, -120($fp)
add $t4, $t3, $fp
lw $t1, 0($t4)
li $t2, 0
beq $t1, $t2, label11
j label12
label11:
li $t2, 1
lw $t1, -96($fp)
add $t3, $t1, $t2
sw $t3, -124($fp)
li $t2, 1
lw $t1, -96($fp)
add $t3, $t1, $t2
sw $t3, -128($fp)
li $t2, 21
lw $t1, -128($fp)
div $t1, $t2
mflo $t3
sw $t3, -132($fp)
li $t2, 21
lw $t1, -132($fp)
mul $t3, $t1, $t2
sw $t3, -136($fp)
lw $t1, -124($fp)
lw $t2, -136($fp)
sub $t3, $t1, $t2
sw $t3, -96($fp)
j label10
label12:
li $t2, 1
lw $t1, -112($fp)
add $t3, $t1, $t2
sw $t3, -112($fp)
li $t2, 1
lw $t1, -96($fp)
add $t3, $t1, $t2
sw $t3, -140($fp)
li $t2, 1
lw $t1, -96($fp)
add $t3, $t1, $t2
sw $t3, -144($fp)
li $t2, 21
lw $t1, -144($fp)
div $t1, $t2
mflo $t3
sw $t3, -148($fp)
li $t2, 21
lw $t1, -148($fp)
mul $t3, $t1, $t2
sw $t3, -152($fp)
lw $t1, -140($fp)
lw $t2, -152($fp)
sub $t3, $t1, $t2
sw $t3, -96($fp)
j label7
label9:
label13:
li $t2, 4
lw $t1, -96($fp)
mul $t3, $t1, $t2
sw $t3, -156($fp)
li $t1, -88
lw $t2, -156($fp)
add $t3, $t1, $t2
sw $t3, -160($fp)
lw $t3, -160($fp)
add $t4, $t3, $fp
lw $t1, 0($t4)
li $t2, 0
beq $t1, $t2, label14
j label15
label14:
li $t2, 1
lw $t1, -96($fp)
add $t3, $t1, $t2
sw $t3, -164($fp)
li $t2, 1
lw $t1, -96($fp)
add $t3, $t1, $t2
sw $t3, -168($fp)
li $t2, 21
lw $t1, -168($fp)
div $t1, $t2
mflo $t3
sw $t3, -172($fp)
li $t2, 21
lw $t1, -172($fp)
mul $t3, $t1, $t2
sw $t3, -176($fp)
lw $t1, -164($fp)
lw $t2, -176($fp)
sub $t3, $t1, $t2
sw $t3, -96($fp)
j label13
label15:
li $t2, 4
lw $t1, -96($fp)
mul $t3, $t1, $t2
sw $t3, -180($fp)
li $t1, -88
lw $t2, -180($fp)
add $t3, $t1, $t2
sw $t3, -184($fp)
lw $t1, -184($fp)
add $t2, $t1, $fp
lw $a0, 0($t2)
li $v0, 1
syscall
li $v0, 4
la $a0, _ret
syscall
li $t2, 4
lw $t1, -96($fp)
mul $t3, $t1, $t2
sw $t3, -188($fp)
li $t1, -88
lw $t2, -188($fp)
add $t3, $t1, $t2
sw $t3, -192($fp)
li $t1, 0
lw $t2, -192($fp)
add $t3, $t2, $fp
sw $t1, 0($t3)
li $t2, 1
lw $t1, -92($fp)
add $t3, $t1, $t2
sw $t3, -92($fp)
j label4
label6:
addi $sp, $sp, 2048
li $t1 0
move $v0, $t1
jr $ra
main:
move $fp, $sp
addi $sp, $sp, -2048
li $t1, 5
sw $t1, -4($fp)
sw $fp, -8($fp)
sw $ra, -12($fp)
addi $fp, $fp, -12
jal josef
lw $ra, 0($fp)
lw $fp, 4($fp)
move $t1, $v0
sw $t1, -16($fp)
addi $sp, $sp, 2048
li $t1 0
move $v0, $t1
jr $ra
