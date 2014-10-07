.data

lfsr:
        .align 4
        .half
        0x1, 0x0

.text

# Implements a 16-bit lfsr
#
# Arguments: None
lfsr_random:

        la $t0 lfsr
        lhu $v0 0($t0)	#v0 = reg
        lhu $v1 2($t0) #v1 = highest
      	
      	addu $t1 $0 $0 # $t1 = i  
 loop:
	beq $t1 16 return 
	srl $t2 $v0 0
	srl $t3 $v0 2
	srl $t4 $v0 3
	srl $t5 $v0 5
	xor $t2 $t2 $t3
	xor $t2 $t2 $t4
	xor $t2 $t2 $t5
	addu $v1 $t2 $0
	srl $t3 $v0 1
	sll $t4 $v1 15
	or $t5 $t3 $t4
	add $v0 $t5 0 #  reg = (reg >> 1) | (highest << 15);
	andi $v0 $v0 65535 # mask first 16 bits
	addi $t1 $t1 1
	j loop
	
return:
        la $t0 lfsr
        sh $v0 0($t0)
        jr $ra
        