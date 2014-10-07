.text

# Generates an autostereogram inside of buffer
#
# Arguments:
#     autostereogram (unsigned char*)
#     depth_map (unsigned char*)
#     width M
#     height N
#     strip_size
calc_autostereogram:

        # Allocate 5 spaces for $s0-$s5
        # (add more if necessary)
        addiu $sp $sp -36
        sw $s0 0($sp)
        sw $s1 4($sp)
        sw $s2 8($sp)
        sw $s3 12($sp)
        sw $s4 16($sp)
        sw $s5 20($sp)
        sw $s6 24($sp)
        sw $s7 28($sp)
        sw $ra 32($sp)
        # autostereogram
        lw $s0 36($sp)
        # depth_map
        lw $s1 40($sp)
        # width
        lw $s2 44($sp)
        # height
        lw $s3 48($sp)
        # strip_size
        lw $s4 52($sp)
        
	addu $t0 $0 $0 # $t0 = i = 0
outer:
	beq $t0 $s2 outbreak

	addu $t1 $0 $0 # $t1 = j = 0
inner:
	beq $t1 $s3 inbreak
	
	blt  $t0 $s4 if
else:	
	mul $t2 $t1 $s2
	addu $t2 $t2 $t0

	addu $t3, $t2, $s1
	lbu $t3, 0($t3) # depth(i,j)
	addu $t3 $t3 $t0
	sub $t3 $t3 $s4
	
	mul $t4 $t1 $s2
	addu $t3 $t3 $t4

	addu $t3, $t3, $s0
	lb $t3, 0($t3) # $t3 = I((i + depth(i,j) - S), j)
	
	addu $t4, $t2, $s0 # I(i,j)
	sb $t3, 0($t4)
	j incrementj
	
if:				
	mul $t2 $s2 $t1
	addu $t2 $t2 $t0
	move $s5 $t2
	move $s6 $t1
	move $s7 $t0
	
	jal lfsr_random
	and $v0 $v0 0xff

	move $t2 $s5
	move $t1 $s6
	move $t0 $s7
	
	addu $t2, $t2, $s0
	sb $v0, 0($t2)
	
	add $t1 $t1 $0
	
incrementj:
	addi $t1 $t1 1
	j inner
	
inbreak:		
	addi $t0 $t0 1
	j outer
	
outbreak:
        lw $s0 0($sp)
        lw $s1 4($sp)
        lw $s2 8($sp)
        lw $s3 12($sp)
        lw $s4 16($sp)
        lw $s5 20($sp)
        lw $s6 24($sp)
        lw $s7 28($sp)
        lw $ra 32($sp)
        addiu $sp $sp 36
        jr $ra
