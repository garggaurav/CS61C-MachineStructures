.text

# Decodes a quadtree to the original matrix
#
# Arguments:
#     quadtree (qNode*)
#     matrix (void*)
#     matrix_width (int)
#
# Recall that quadtree representation uses the following format:
#     struct qNode {
#         int leaf;
#         int size;
#         int x;
#         int y;
#         int gray_value;
#         qNode *child_NW, *child_NE, *child_SE, *child_SW;
#     }
	
quad2matrix:
	# $a0 quadtree root
	# $a1 NxN matrix
	# $a2 Width
	# $t0 isLeaf
	# t2 address of sub box
	
	# Making a global variable out of image size
	addi $t8, $a2, 0 # Store the image size for this function call
begin:
	# Loading whether root node is a leaf
	lw $t0, 0($a0) # isLeaf = root->leaf
	bne $t0, $0, fill_matrix
	
	# If not leaf then prepare to go to the 4 sub boxes
	addi $sp, $sp, -8 # move stack pointer down by 4
	sw $ra, 0($sp) # saving return address on stack pointer
	sw $a0, 4($sp) # saving the root node
	sra $a2, $a2, 1 # width = width / 2
		
	# Loading NW
	lw $a0, 20($a0) # root = root->child_NW
	jal begin # recursive call
	
	# Loading NE
	lw $a0, 4($sp) # Restore $a0
	lw $a0, 24($a0) # root = root->child_NE
	jal begin # recursive call
	
	# Loading SE
	lw $a0, 4($sp) # Restore $a0
	lw $a0, 28($a0) # root = root->child_NE
	jal begin # recursive call
	
	# Loading SW
	lw $a0, 4($sp) # Restore $a0
	lw $a0, 32($a0) # root = root->child_NE
	jal begin # recursive call
	
	# Restoring args
	lw $ra, 0($sp) # Load $ra from the stack
	addi, $sp, $sp, 8 # Clearing stack
	sll $a2, $a2, 1
	j return
	
fill_matrix:
	# $t1 i
	# $t2, j
	# $t3 limit_x
	# $t4 limit_y
	
	# Saving variables
	addi $sp, $sp, -8 # 8 bytes of space
	sw $s0, 0($sp)
	sw $s1, 4($sp)
	
	# Iteration variables
	lw $t1, 8($a0) # i = root->x
	lw $s1 12($a0) # j = root->y

	# Iteration limits
	add $t3, $t1, $a2 # limit_x = i + N
	add $t4, $s1, $a2 # limit_y = j + N

	# Filling pixels
	lbu $s0, 16($a0) # The pixel value
	
outer_loop:	
	slt $t5, $t1, $t3 # i < limit_x
	beq $t5, $0, outer_loop_end # if !(i < limit_x), return
	addi $t2, $s1, 0 # Resetting t
	
inner_loop:
	slt $t6, $t2, $t4 # j < limit_y
	beq $t6, $0, inner_loop_end # if !(j < limit_y), inner_loop_end
	
	mul $t7, $t2, $t8 # idx = j * N
	add $t7, $t7, $t1 # idx = idx + i
	add $t0, $t7, $a1 # addr = matrix + idxs
	sb $s0, 0($t0) # *(addr) = pixel
	
	addi $t2, $t2, 1 # j = j + 1
	j inner_loop # Go back to top
	
inner_loop_end: 
	addi $t1, $t1, 1 # i = i + 1
	j outer_loop
	
outer_loop_end:
	# Restoring variables from stack
	lw $s0, 0($sp)
	lw $s1, 4($sp)
	addi $sp, $sp, 8
	
return:	
        jr $ra
